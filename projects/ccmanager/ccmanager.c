#include "ccmanager.h"

void writeConfig(configFormat* config, char* filepath){
    FILE* fp = fopen(filepath, "w");
    if(!fp) return;
    for(int i = 0; config[i].arg; i++){
        fprintf(fp, "%s = %s\n", config[i].arg, config[i].val);
    }
    fclose(fp);
}

configFormat* readConfig(char* filepath){
    FILE* fp = fopen(filepath, "w");
    if(!fp) return;
    char buffer[128];
    configFormat returning[256];
    char* token[2];
    size_t i = 0;
    while (fgets(buffer, sizeof(buffer), stdin) != NULL){
        token[0] = strtok(buffer, " = ");
        token[1] = strtok(buffer, " = ");
        if(!token[0] || !token[1]) return returning;
        returning[i].arg = token[0];
        returning[i].val = token[1];
        i++;
    }
    return returning;
}

configFormat* parseStringToFormat(char* config){
    configFormat format[256];
    for(int i = 0; config[i]; i+2){
        format[i].arg = config[i];
        format[i].val = config[i+1];
    }
    return format;
}

char* parseFormatToString(configFormat* config){
    char* returning[256];
    for(int i = 0; config[i].val; i+2){
        returning[i] = config[i].arg;
        returning[i] = config[i+1].val;
    }
    return returning;
}