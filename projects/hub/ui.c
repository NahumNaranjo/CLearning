#include "ui.h"
#include <string.h>

char* BuildUI(){
    static char option[256]; // Buffer for input
    printf("Welcome to the Hub!\n");
    printf("Please, select an option (In progress):\n");
    printf("1. CXT\n");
    printf("2. CBA");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    if (!fgets(option, sizeof(option), stdin)) {
        printf("Error reading input\n");
        return NULL;
    }
    // Remove newline
    size_t len = strlen(option);
    if (len > 0 && option[len-1] == '\n') {
        option[len-1] = '\0';
    }
    return option; // Return pointer to the buffer
}