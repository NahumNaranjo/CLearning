#ifndef CCMANAGER_H
#define CCMANAGER_H
    #include <cfm2.h>
    #include <stdio.h>

    typedef struct {
        char* arg;
        char* val;
    } configFormat;
    
    configFormat* parseStringToFormat(char* filePath);
#endif
