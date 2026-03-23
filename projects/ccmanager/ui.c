#include "ui.h"


//TODO: DISPLAY ALL CONFIG OPTIONS INSTEAD OF THE FILE ITSELF
void displayConfigs(char* path){
    char command[128];
    sprintf(command, "type \"%s\"\n", path);
    system(command);
    printf("This is \"%s\", do you wish to change anything?\n", path);
}