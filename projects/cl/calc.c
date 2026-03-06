#include "calc.h"

// Custom implementation of strndup since it's not available in C11 (stole it)
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
    return 
    c == '+' || c == '-' || c == '*' || c == '/' || 
    c == '%' || c == 's' || c == 'c' || c == 't';
}

calcData initialize() {
    calcData data;
    FILE* fp = lookInRoot("\\configs\\calc.config", "r");
    size_t size;
    char* config = ParseFile(fp, size);
    char* token = strtok(config, "\n");
    while(token){
        if(strcmp(token, "MODE = d") == 0){
            data.mode = 'd';
        }
        else if(strcmp(token, "MODE = r") == 0){
            data.mode = 'r';
        }
        token = strtok(NULL, "\n");
    }
    return data;
}

// Compute the result of num1 ope num2 and add it to result
void compute(double* result, double num1, double num2, char* ope, calcData data) {
    // printf("Debug - Computing: %f %s %f\n", num1, ope, num2);
    switch(*ope){
        case '+': *result += (int)(num1 + num2); break;
        case '-': *result += (int)(num1 - num2); break;
        case '*': *result += (int)(num1 * num2); break;
        case '/': 
            if (num2 != 0) *result += (int)(num1 / num2);
            else printf("Error: Division by zero\n"); *result = NAN;
            break;
        case '%': 
            if ((int)num2 != 0)  *result += (int)((int)num1 % (int)num2);
            else printf("Error: Modulo by zero\n"); *result = NAN;
            break;
        case 's':
            num1 = num1 * (M_PI / 180.0);
            if(data.mode == 'd') num1 = sin(num1) * (180.0/M_PI);
            else num1 = sin(num1);
            break;
        case 'c':
            num1 = num1 * (M_PI / 180.0);
            if(data.mode == 'd') num1 = cos(num1) * (180.0/M_PI);
            else num1 = cos(num1);
            break;
        case 't':
            num1 = num1 * (M_PI / 180.0);
            if(data.mode == 'd') num1 = cos(num1) * (180.0/M_PI);
            else num1 = cos(num1);
            break;
    }
}

void calc(char* exp) {
   // printf("Debug - calc received: '%s'\n", exp ? exp : "NULL");
    calcData data = initialize();
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
    Map tracker[100];
    size_t trackerCount = 0;
    // Organize operations order
    for (int i = 0; i < tokenCount; i++) {
        // printf("Debug - Processing token %d: '%s'\n", i, tokens[i]);
        if(isOperand(tokens[i][0]) == 1){
            tracker[trackerCount].key = tokens[i];
            tracker[trackerCount].timesAppeared = i;
            trackerCount++;
        }
    }
    // Process parentheses
    for (int i = 0; i < trackerCount; i++) {
        if(tokens[i][0] == '\0') continue; // Skip processed tokens
        // printf("Debug - Tracker %d: '%s' at index %d\n", i, tracker[i].key, tracker[i].timesAppeared);
        if(*tracker[i].key == '(' && *tracker[i - 1].key != 's' && *tracker[i - 1].key != 'c' && *tracker[i - 1].key != 't'){
            int openIndex = tracker[i].timesAppeared;
            int closeIndex = -1;
            for (int j = i + 1; j < trackerCount; j++) {
                if (*tracker[j].key == '(') {
                    openIndex = tracker[j].timesAppeared;
                } else if (*tracker[j].key == ')') {
                    closeIndex = tracker[j].timesAppeared;
                    break;
                }
            }
            if (closeIndex == -1) {
                printf("Error: Mismatched parentheses\n");
                goto cleanup;
            }
            // Extract sub-expression
            char* subExp = malloc(closeIndex - openIndex);
            if (!subExp) {
                printf("Error: Memory allocation failed\n");
                goto cleanup;
            }
            strncpy(subExp, expCopy + openIndex + 1, closeIndex - openIndex - 1);
            subExp[closeIndex - openIndex - 1] = '\0';
            // Recursively calculate sub-expression
            calc(subExp);
            free(subExp);
        }
    }
    // Process functions 
    for(int i = 0; i < trackerCount; i++) {
        if(tokens[i][0] == '\0') continue; // Skip processed tokens
        if(*tracker[i].key == 's' || *tracker[i].key == 'c' || *tracker[i].key == 't'){
            if(*tracker[tracker[i].timesAppeared + 1].key == '(' && *tracker[tracker[i].timesAppeared + 3].key == ')'){
                num1 = atof(tokens[tracker[i].timesAppeared + 2]);
                ope = tracker[i].key;
                compute(&result, num1, 0, ope, data);
                // Mark tokens as processed
                tokens[tracker[i].timesAppeared][0] = '\0';
                tokens[tracker[i].timesAppeared + 1][0] = '\0';
                tokens[tracker[i].timesAppeared + 2][0] = '\0';
                tokens[tracker[i].timesAppeared + 3][0] = '\0';
            }
            else {
                printf("Error: Invalid format for function '%c'. Use: s(30) or s ( 30 ) for sine of 30 degrees\n", *tracker[i].key);
                goto cleanup;
            }
        }
    }
    // Process remaining operations
    for (int i = 0; i < tokenCount; i++) {
        if(tokens[i][0] == '\0') continue; // Skip processed tokens
        if(isOperand(tokens[i][0]) == 1){
            ope = tokens[i];
            if(i == 0 || i == tokenCount - 1) {
                printf("Error: Expression cannot start or end with an operator\n");
                goto cleanup;
            }
            if(isNumber(tokens[i-1][0]) == 1) num1 = atof(tokens[i-1]);
            else {
                printf ("Error: Invalid number, this could be by an invalid expression format, or by an invalid number. Use: number operator number (e.g., \"3 + 4\" or 3+4)\n");
                goto cleanup;
            }
            if(isNumber(tokens[i+1][0]) == 1) num2 = atof(tokens[i+1]);
            else {
                printf ("Error: Invalid number, this could be by an invalid expression format, or by an invalid number. Use: number operator number (e.g., \"3 + 4\" or 3+4)\n");
                goto cleanup;
            }
            compute(&result, num1, num2, ope, data);
            // Mark tokens as processed
            tokens[i][0] = '\0';
            tokens[i-1][0] = '\0';
            tokens[i+1][0] = '\0';
        }
    }
    //! Deprecated code for simple left-to-right processing without operator precedence or parentheses handling
    /*
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
        if(tokens[i][0] == '(' || tokens[i][0] == ')'){

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

        compute(&result, num1, num2, ope, data);
    }
    */
    if(!isnan(result)){
        if(result == (int)result) {
            printf("Result: %d\n", (int)result);
        } else {
            printf("Result: %f\n", result);
        }
    }

    cleanup:
        for (int i = 0; i < tokenCount; i++) {
            free(tokens[i]);
        }
        free(expCopy);
}