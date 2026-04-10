#include "calc.h"
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_STACK 100

// Estructuras para tokens y pilas
typedef struct {
    char type;  // 'n' para número, 'o' para operador
    double value;
    char op;
} Token;

typedef struct {
    double items[MAX_STACK];
    int top;
} Stack;

typedef struct {
    char items[MAX_STACK];
    int top;
} CharStack;

// Funciones de pila
void stackPush(Stack* s, double val) {
    if (s->top < MAX_STACK - 1) {
        s->items[s->top++] = val;
    }
}

double stackPop(Stack* s) {
    if (s->top > 0) {
        return s->items[--s->top];
    }
    return 0;
}

double stackPeek(Stack* s) {
    if (s->top > 0) {
        return s->items[s->top - 1];
    }
    return 0;
}

// Funciones para pila de caracteres
void charStackPush(CharStack* s, char val) {
    if (s->top < MAX_STACK - 1) {
        s->items[s->top++] = val;
    }
}

char charStackPop(CharStack* s) {
    if (s->top > 0) {
        return s->items[--s->top];
    }
    return '\0';
}

char charStackPeek(CharStack* s) {
    if (s->top > 0) {
        return s->items[s->top - 1];
    }
    return '\0';
}

// Obtener precedencia del operador
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == 's' || op == 'c' || op == 't') return 3;
    return 0;
}

// Parsear expresión en tokens
int tokenize(char* exp, Token* tokens) {
    printf("debug - tokenizing");
    int count = 0;
    int i = 0;
    
    while (exp[i] && count < MAX_TOKENS) {
        // Saltar espacios
        while (exp[i] == ' ') i++;
        if (!exp[i]) break;
        
        // Números
        if (isdigit(exp[i]) || exp[i] == '.') {
            char numStr[50];
            int j = 0;
            while ((isdigit(exp[i]) || exp[i] == '.') && j < 49) {
                numStr[j++] = exp[i++];
            }
            numStr[j] = '\0';
            tokens[count].type = 'n';
            tokens[count].value = atof(numStr);
            count++;
        }
        // Operadores
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || 
                 exp[i] == '/' || exp[i] == '%') {
            tokens[count].type = 'o';
            tokens[count].op = exp[i++];
            count++;
        }
        // Funciones trigonométricas
        else if (exp[i] == 's' || exp[i] == 'c' || exp[i] == 't') {
            tokens[count].type = 'o';
            tokens[count].op = exp[i++];
            count++;
        }
        // Paréntesis
        else if (exp[i] == '(' || exp[i] == ')') {
            tokens[count].type = exp[i];
            tokens[count].op = exp[i++];
            count++;
        }
        else {
            i++;  // Ignorar caracteres inválidos
        }
    }
    printf("debug - tokenized");
    return count;
}

// Realizar operación aritmética
double performOperation(double num1, double num2, char op, calcData data) {
    printf("debug - calculating");
    switch(op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': 
            return (num2 != 0) ? num1 / num2 : NAN;
        case '%': 
            return ((int)num2 != 0) ? (int)num1 % (int)num2 : NAN;
        case 's':
            num1 = num1 * (M_PI / 180.0);
            return (data.mode == 'd') ? sin(num1) * (180.0/M_PI) : sin(num1);
        case 'c':
            num1 = num1 * (M_PI / 180.0);
            return (data.mode == 'd') ? cos(num1) * (180.0/M_PI) : cos(num1);
        case 't':
            num1 = num1 * (M_PI / 180.0);
            return (data.mode == 'd') ? tan(num1) * (180.0/M_PI) : tan(num1);
        default: return 0;
    }
    printf("debug - calculated");
}

// Evaluar expresión tokenizada
double evaluateTokens(Token* tokens, int count, calcData data) {
    printf("debug - evaluating");
    Stack output;
    CharStack operators;
    output.top = 0;
    operators.top = 0;
    
    for (int i = 0; i < count; i++) {
        if (tokens[i].type == 'n') {
            stackPush(&output, tokens[i].value);
        }
        else if (tokens[i].type == 'o') {
            while (operators.top > 0 && 
                   getPrecedence(charStackPeek(&operators)) >= 
                   getPrecedence(tokens[i].op)) {
                double num2 = stackPop(&output);
                double num1 = stackPop(&output);
                char op = charStackPop(&operators);
                stackPush(&output, performOperation(num1, num2, op, data));
            }
            charStackPush(&operators, tokens[i].op);
        }
    }
    
    while (operators.top > 0) {
        double num2 = stackPop(&output);
        double num1 = stackPop(&output);
        char op = charStackPop(&operators);
        stackPush(&output, performOperation(num1, num2, op, data));
    }
    printf("debug - evualted");
    return stackPeek(&output);
}


calcData initialize() {
    printf("debug - initializing");
    calcData data;
    data.mode = 'd';  // Default to degrees
    FILE* fp = lookInRoot("configs/calc.config", "r");
    printf("debug - file");
    if(!fp) {
        printf("Error: Could not open configuration file. Defaulting to degrees mode.\n");
        return data;
    }
    size_t configLines = 0;
    char** config = ParseFile(fp, &configLines);
    printf("debug - filed");

    if(config){
        for(size_t i = 0; i < configLines; i++){
            if(config[i]){
                if(strcmp(config[i], "MODE = r") == 0) data.mode = 'r';
                if(strcmp(config[i], "MODE = d") == 0) data.mode = 'd';
                free(config[i]);
            }
        }
        free(config);
    }
    printf("debug - whiled");
    fclose(fp);
    printf("debug - initialized");
    return data;
}

void calc(char* exp) {
    printf("debug - calc");
    calcData data = initialize();
    if (exp == NULL) {
        printf("Error: No expression provided\n");
        printf("Usage: calc \"3 + 4\" or calc 3+4\n");
        return;
    }
    
    Token tokens[MAX_TOKENS];
    int tokenCount = tokenize(exp, tokens);
    
    if (tokenCount == 0) {
        printf("Error: Invalid expression\n");
        return;
    }
    
    double result = evaluateTokens(tokens, tokenCount, data);
    
    if(!isnan(result)) {
        if(result == (int)result) {
            printf("Result: %d\n", (int)result);
        } else {
            printf("Result: %f\n", result);
        }
    } else {
        printf("Error: Invalid operation\n");
    }
    printf("debug - calcd");
}