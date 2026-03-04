#include "calc.h"

static char* xstrndup(const char *s, size_t n) {
    char *d = malloc(n + 1);
    if (!d) return NULL;
    memcpy(d, s, n);
    d[n] = '\0';
    return d;
}

int isNumber(char c) {
    return (c >= '0' && c <= '9') || c == '.';
}

int isOperand(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

void calc(char* exp) {
   // printf("Debug - calc received: '%s'\n", exp ? exp : "NULL");
    
    if (exp == NULL) {
        printf("Error: No expression provided\n");
        printf("Usage: calc \"3 + 4\" or calc 3+4\n");
        return;
    }
    
    char* tokens[100];  // Store tokens (numbers and operators)
    int tokenCount = 0;
    
    // Copy exp to avoid modifying original
    char* expCopy = strdup(exp);
    if (!expCopy) {
        printf("Error: Memory allocation failed\n");
        return;
    }
    
    trimWhitespace(expCopy);
    // printf("Debug - After trim: '%s'\n", expCopy);
    
    // Check if the expression has no spaces (like "651+34")
    int hasSpaces = 0;
    for (int i = 0; expCopy[i]; i++) {
        if (expCopy[i] == ' ') {
            hasSpaces = 1;
            break;
        }
    }
    
    if (!hasSpaces) {
        // Parse expression without spaces
        char* numBuffer = malloc(strlen(expCopy) + 1);
        if (!numBuffer) {
            printf("Error: Memory allocation failed\n");
            free(expCopy);
            return;
        }
        int numIndex = 0;
        
        for (int i = 0; expCopy[i]; i++) {
            if (isNumber(expCopy[i])) {
                numBuffer[numIndex++] = expCopy[i];
            } else if (isOperand(expCopy[i])) {
                numBuffer[numIndex] = '\0';
                tokens[tokenCount++] = strdup(numBuffer);
                tokens[tokenCount++] = xstrndup(&expCopy[i], 1);
                numIndex = 0;
            } else {
                printf("Error: Invalid character '%c' in expression\n", expCopy[i]);
                free(numBuffer);
                goto cleanup;
            }
        }
        if (numIndex > 0) {
            numBuffer[numIndex] = '\0';
            tokens[tokenCount++] = strdup(numBuffer);
        }
        free(numBuffer);
    } else {
        // Parse expression with spaces using strtok
        char* token = strtok(expCopy, " ");
        while (token != NULL && tokenCount < 100) {
            tokens[tokenCount++] = strdup(token);
            // printf("Debug - Token %d: '%s'\n", tokenCount-1, token);
            token = strtok(NULL, " ");
        }
    }
    
    //printf("Debug - Token count: %d\n", tokenCount);

    // Calculate result based on tokens
    double num1 = 0;
    double num2 = 0;
    char* ope = 0;
    double result = 0;
    for(int i = 0; i < tokenCount; i++) {
        if(i+1 >= tokenCount) {
            if(isNumber(tokens[i][0]) == 1){
                num1 = atof(tokens[i]);
                ope = tokens[i-1];
                if(*ope == '-') {
                    if(tokens[i-1][0] == '-') num1 = -num1;
                }
                if(*ope == '*')result = result * num1;
                if(*ope == '/') {
                    if(num1 != 0) result = result / num1;
                    else {
                        printf("Error: Division by zero\n");
                        result = NAN;
                    }
                }
                goto cleanup;
            }
            if(isOperand(tokens[i][0]) == 1) {
                printf("Math error: Expression cannot end with an operator\n");
                goto cleanup;
            }
        }
        if(isOperand(tokens[i][0]) == 1){
            ope = tokens[i];
            num2 = atof(tokens[i+1]);
            num1 = 0;
            i += 1;
        }
        else if(isNumber(tokens[i][0]) == 1){
            num1 = atof(tokens[i]);
            if(isOperand(tokens[i+1][0]) == 1)ope = tokens[i+1];
            else {
                printf ("Error: Invalid operator, this could be by an invalid expression format, or by an invalid operator. Use: number operator number (e.g., \"3 + 4\" or 3+4)\n");
                goto cleanup;
            }
            if(isNumber(tokens[i+2][0]) == 1) num2 = atof(tokens[i+2]);
            else {
                printf ("Error: Invalid number, this could be by an invalid expression format, or by an invalid number. Use: number operator number (e.g., \"3 + 4\" or 3+4) \n");
                goto cleanup;
            }
            i += 2;
        }
        else {
            printf ("Error: Invalid number, this could be by an invalid expression format, or by an invalid number. Use: number operator number (e.g., \"3 + 4\" or 3+4)\n");
            goto cleanup;
        }
        switch(*ope){
            case '+': result = result + (num1 + num2); break;
            case '-': result = result + (num1 - num2); break;
            case '*': result = result + (num1 * num2); break;
            case '/': 
                if (num2 != 0) result = result + (num1 / num2);
                else printf("Error: Division by zero\n"); result = NAN;
                break;
            case '%': 
                if ((int)num2 != 0)  result = result + ((int)num1 % (int)num2);
                else printf("Error: Modulo by zero\n"); result = NAN;
                break;
        }
    }
    if(!isnan(result)){
        if(result == (int)result) {
            printf("Result: %d\n", (int)result);
        } else {
            printf("Result: %f\n", result);
        }
    }

    //! Kept for reference, will be removed in future versions
    // Simple calculator (supports only two operands for now)
   /* if (tokenCount == 3 && isOperand(tokens[1][0])) {
        double num1 = atof(tokens[0]);
        double num2 = atof(tokens[2]);
        double result = 0;
        
        //printf("Debug - num1: %f, num2: %f, operator: %c\n", num1, num2, tokens[1][0]);
        
        switch(tokens[1][0]) {
            case '+': result = num1 + num2; break;
            case '-': result = num1 - num2; break;
            case '*': result = num1 * num2; break;
            case '/': 
                if (num2 != 0) result = num1 / num2;
                else printf("Error: Division by zero\n");
                break;
            case '%': 
                if ((int)num2 != 0) result = (int)num1 % (int)num2;
                else printf("Error: Modulo by zero\n");
                break;
        }
        if(result == (int)result) {
            printf("Result: %d\n", (int)result);
        } else {
            printf("Result: %f\n", result);
        }
    } else {
        printf("Error: Invalid expression format. Use: number operator number (e.g., \"3 + 4\" or 3+4)\n");
        if (tokenCount != 3) {
            printf("Expected 3 tokens, got %d\n", tokenCount);
        } else if (!isOperand(tokens[1][0])) {
            printf("Second token '%s' is not a valid operator\n", tokens[1]);
        }
    }
    */

    cleanup:
        for (int i = 0; i < tokenCount; i++) {
            free(tokens[i]);
        }
        free(expCopy);
}