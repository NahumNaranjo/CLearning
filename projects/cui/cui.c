#include "cui.h"


Menu* createMenu(char* title, MenuOption* options, size_t count){
    Menu* menu = (Menu*)malloc(sizeof(Menu));
    if(menu == NULL) return NULL;
    menu->title, title;
    menu->options = options;
    menu->optionCount = count;

    return menu;
}

char* readInput(char* prompt, size_t maxl){
    static char buffer[512];
    printf("%s", prompt);
    if(!fgets(buffer, (int)maxl, stdin)){
        return NULL;
    }

    size_t len = strlen(buffer);
    if(len > 0 && buffer[len-1] == '\n'){
        buffer[len-1] = '\0';
    }

    return buffer;
}

void* displayTitle(char* title){
    printf("\n%s\n", title);
    printf("================================\n");
}

char* displayMenu(Menu* menu){
    for (size_t i = 0; i < menu->optionCount; i++){
        printf("%zu. %s\n", i+1, menu->options[i].label);
    }

    printf("================================\n");
    char* input = readInput("Select an option\n", 256);

    if(!input) return NULL;

    int choice = atoi(input);
    if(choice > 0 && choice <= (int)menu->optionCount){
        return menu->options[choice-1].returnValue;
    }
    
    printf("Invalid option. Try again.\n");
    return displayMenu(menu);
}

int validateMenuOption(char* input, size_t optionCount){
    int choice = atoi(input);
    return(choice > 0 && choice <= (int) optionCount) ? choice : -1;
}

void freeMenu(Menu* menu){
    if(menu) free(menu);
}