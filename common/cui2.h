#ifndef CUI2_H
#define CUI2_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "platform.h"
    #include "ariadne.h"

    typedef struct {
        char* label;
        char* returnValue;
    } MenuOption;

    typedef struct {
        char title[256];
        MenuOption* options;
        size_t optionCount;
    } Menu;

    Menu* createMenu(char* title, MenuOption* options, size_t count);
    
    char* displayMenu(Menu* menu);
    
    char* readInput(char* prompt, size_t maxLen);
    
    int validateMenuOption(char* input, size_t optionCount);
    
    void freeMenu(Menu* menu);

    void* displayTitle(char* title);

#endif