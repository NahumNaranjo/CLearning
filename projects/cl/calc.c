#include "calc.h"

void calc(char* exp){
    char numbers[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
    char operands[5] = {'+', '*', '-', '/', '%'};
    // char keywords[4] = {'l', 't', 'c', 's'};  //! SAVED FOR LATER USE
    char* buffer[2048];

    trimWhitespace(exp);

    //  parses
    for(int i = 0; i < (sizeof(exp) / sizeof(exp[0])); i++){
        // makes numbers
        for(int j = 0; j < (sizeof(numbers) / sizeof(numbers[0])); j++){
            if(exp[i] == numbers[j]){
                if(confirmArray(numbers, *buffer[i-1]) == 0){
                    strcat(buffer[i-1], &numbers[j]);
                    i--;
                    break;
                }
                buffer[i] = &numbers[j];
            }
        }
        // saves operands
        for(int j = 0; j < (sizeof(operands) / sizeof(operands[0])); j++){
            if(exp[i] == operands[j]){
                buffer[i] = &numbers[j];
            }
        }
    }
    // calcs
    float result;
    for(int i = 0; i < (sizeof(buffer) / sizeof(buffer[0])); i++){
        if(confirmArray(numbers, *buffer[i]) == 1){
            if(*buffer[i++] == '+'){
                result = atof(buffer[i]) + atof(buffer[i+2]);
            }
            if(*buffer[i++] == '-'){
                result = atof(buffer[i]) - atof(buffer[i+2]);
            }
            if(*buffer[i++] == '*'){
                result = atof(buffer[i]) * atof(buffer[i+2]);
            }
            if(*buffer[i++] == '/' && (buffer[i] != 0 && buffer[i+2] != 0)){
                result = atof(buffer[i]) * atof(buffer[i+2]);
            }
            printf("%f", result);
            i += 3;
        }
    }
}