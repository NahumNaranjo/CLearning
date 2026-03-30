#ifndef CCMANAGER_H
#define CCMANAGER_H
    #include <cfm2.h>
    #include <stdio.h>
    #include "ccmui.h"

    typedef struct {
        char* arg;
        char* val;
    } configFormat;
    
    configFormat* parseStringToFormat(char* filePath);
    configFormat* readConfigFile(char* filepath);
    void writeConfigFile(configFormat* config, char* filepath);
    char* parseFormatToString(configFormat* config);
    void appendConfigFile(configFormat* config, char* filepath);
#endif
