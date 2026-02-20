#include "calc.h"

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
    //printf("Debug - After trim: '%s'\n", expCopy);
    
    // Check if the expression has no spaces (like "651+34")
    int hasSpaces = 0;
    for (int i = 0; expCopy[i]; i++) {
        if (expCopy[i] == ' ') {
            hasSpaces = 1;
            break;
        }
    }
    
    if (!hasSpaces) {
        // Parse expression without spaces (e.g., "651+34")
        char temp[100];
        strcpy(temp, expCopy);
        
        // Find the operator position
        int operatorPos = -1;
        char operator = 0;
        
        for (int i = 0; temp[i]; i++) {
            if (temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/' || temp[i] == '%') {
                operatorPos = i;
                operator = temp[i];
                break;
            }
        }
        
        if (operatorPos > 0) {
            // Extract first number
            char num1[50] = {0};
            strncpy(num1, temp, operatorPos);
            
            // Extract second number
            char num2[50] = {0};
            strcpy(num2, temp + operatorPos + 1);
            
            tokens[0] = strdup(num1);
            tokens[1] = malloc(2);
            tokens[1][0] = operator;
            tokens[1][1] = '\0';
            tokens[2] = strdup(num2);
            tokenCount = 3;
            
            //printf("Debug - Parsed: '%s' %c '%s'\n", num1, operator, num2);
        } else {
            printf("Error: No operator found in expression\n");
            free(expCopy);
            return;
        }
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
    
    // Simple calculator (supports only two operands for now)
    if (tokenCount == 3 && isOperand(tokens[1][0])) {
        float num1 = atof(tokens[0]);
        float num2 = atof(tokens[2]);
        float result = 0;
        
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
        printf("Result: %f\n", result);
    } else {
        printf("Error: Invalid expression format. Use: number operator number (e.g., \"3 + 4\" or 3+4)\n");
        if (tokenCount != 3) {
            printf("Expected 3 tokens, got %d\n", tokenCount);
        } else if (!isOperand(tokens[1][0])) {
            printf("Second token '%s' is not a valid operator\n", tokens[1]);
        }
    }
    
    // Cleanup
    for (int i = 0; i < tokenCount; i++) {
        free(tokens[i]);
    }
    free(expCopy);
}