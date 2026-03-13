#include "ui.h"

//TODO: To be fixed and remade
/*
char* BuildUI(){
    static char input[256];
    printf("CBA Main menu:\n");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    
    // Exit command
    if(strcmp(input, "exit") == 0 || strcmp(input, "Exit") == 0){
        printf("Exiting CBA...\n");
        return "0";
    }
    // build
    if(strcmp(input, "build") == 0 || strcmp(input, "Build") == 0){
        printf("Building project...\n");
        build();
        return "0";
    }
    // prepare
    if(strcmp(input, "generate") == 0 || 
       strcmp(input, "Generate") == 0 ||
       strcmp(input, "-g") == 0 ||
       strcmp(input, "-G") == 0){
        generateFiles();
        printf("Build files generated. Run \"build\" command to build the project.\n");
        return "0";
    }
    //clean
    if(strcmp(input, "clean") == 0 || strcmp(input, "Clean") == 0){
        clean();
        printf("Build directory cleaned.\n");
        return "0";
    }
    // config
    if((strcmp(input, "config") == 0 || strcmp(input, "Config") == 0) && 
       (strstr(input, "-n") != NULL || strstr(input, "-N") != NULL)){
        printf("Opening config file...\n");
        system("notepad configs\\cba.config");
        return "0";
    }
    else if(strcmp(input, "config") == 0 || strcmp(input, "Config") == 0){
        config("c");  // Pass string, not char
        return "0";
    }

    // build change
    if((strcmp(input, "change") == 0 || strcmp(input, "Change") == 0) && 
       (strstr(input, "-n") != NULL || strstr(input, "-N") != NULL)){
        printf("Changing build configuration...\n");
        system("notepad cba.build");
        return "0";
    } else {
        config("b");  // Pass string, not char
        return "0";
    }
    printf("Unknown command. Type \"help\" for a list of available commands.\n");
    return input;
}

void config(char* type){
    if(strcmp(type, "c") != 0 && strcmp(type, "b") != 0) return;  // Compare strings
    FILE* fp;
    if(strcmp(type, "c") == 0){
        BuildInfo buildInfo;
        fp = lookInRoot("configs\\cba.config", "r");
        if(fp == NULL) {
            printf("Error: Could not open cba.config file.\n"); 
            return;
        }
        // Rest of your config code...
    } else {
        fp = lookInRoot("cba.build", "r");
        if(fp == NULL){
            printf("Error: Could not open cba.build file.\n");
            return;
        }
    }
}
    */