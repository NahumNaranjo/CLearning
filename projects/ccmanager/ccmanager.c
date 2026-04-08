#include "ccmanager.h"

void capCheck(configFormat* config, size_t* size){
    if((sizeof(config) / sizeof(configFormat*)) >= *size){
        *size = *size + (*size >> 2);
        config = (configFormat*)realloc(config, sizeof(configFormat*) * *size);
    }
}

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

//TODO: Pass returning to malloc
configFormat* readConfigFile(char* filepath){
    size_t size = 128;
    FILE* fp = fopen(filepath, "r");
    if(!fp) return NULL;
    char buffer[128];
    configFormat* returning =  (configFormat*)malloc(sizeof(configFormat) * size);
    char* token[2];
    size_t i = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        capCheck(returning, &size);
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

// recives a string and returns a configFormat
configFormat* parseStringToFormat(char* config){
    size_t size = 128;
    configFormat* format = (configFormat*)malloc(size * sizeof(configFormat*));
    size_t count = 0;
    for(int i = 0; config[i]; i+=2){
        capCheck(format, &size);
        *format[i].arg = config[i];
        *format[i].val = config[i+1];
        count = i;
    }
    *format[count+1].val = '\0';
    return format;
}

char* parseFormatToString(configFormat* config){
    size_t size = 128;
    char** returning = (char**)malloc(size*sizeof(char**));
    size_t j = 0;
    for(int i = 0; config[i].val; i+=2){
        if((sizeof(returning) / sizeof(char**)) >= size){
            size = size + (size >> 2);
            returning = (char**)realloc(config, sizeof(char**) * size);
        }
        returning[j] = config[i].arg;
        returning[j+1] = " = ";
        returning[j+2] = config[i+1].val;
        j+=3;
    }
    return *returning;
}