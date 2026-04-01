#include "ccmanager.h"

void writeConfigFile(configFormat* config, char* filepath){
    FILE* fp = fopen(filepath, "w");
    if(!fp) return;
    for(int i = 0; config[i].arg; i++){
        fprintf(fp, "%s = %s\n", config[i].arg, config[i].val);
    }
    fclose(fp);
}

void appendConfigFile(configFormat* config, char* filepath){
    FILE* fp = fopen(filepath, "a");
    if(!fp) return;
    for(int i = 0; config[i].arg; i++){
        fprintf(fp, "%s = %s\n", config[i].arg, config[i].val);
    }
    fclose(fp);
}

configFormat* readConfigFile(char* filepath){
    FILE* fp = fopen(filepath, "r");
    if(!fp) return NULL;
    char buffer[128];
    configFormat returning[4096];
    char* token[2];
    size_t i = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        token[0] = strtok(buffer, " = ");
        token[1] = strtok(buffer, " = ");
        if(!token[0] || !token[1]) return returning;
        returning[i].arg = token[0];
        returning[i].val = token[1];
        i++;
    }
    returning[i+1].val = '\0';
    return returning;
}

// recives 
configFormat* parseStringToFormat(char* config){
    configFormat format[4096];
    size_t count = 0;
    for(int i = 0; config[i]; i+=2){
        *format[i].arg = config[i];
        *format[i].val = config[i+1];
        count = i;
    }
    format[count+1].val = '\0';
    return format;
}

char* parseFormatToString(configFormat* config){
    char* returning[8192];
    size_t j = 0;
    for(int i = 0; config[i].val; i+=2){
        returning[j] = config[i].arg;
        returning[j+1] = " = ";
        returning[j+2] = config[i+1].val;
        j+=3;
    }
    return *returning;
}