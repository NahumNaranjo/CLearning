#ifndef TEXTPARSER_H
#define TEXTPARSER_H
    #include <string.h>
    #include <stdio.h>
    #include <map.h>
    #include <cfm2.h>

    typedef struct{
        void* function;
        void* arguments[];
    } instruction;

    typedef struct{
        char full[256];
        char cut[256];
        forms forms[20];
    } Verb;

    typedef struct{
        // Simples
        char simplePresent[256];
        char simplePast[256];
        char simpleFuture[256];
        
        // Continuous
        char presentContinuous[256];
        char pastContinuous[256];

        // Perfect
        char presentPerfect[256];
        char pastPerfect[256];

        // Perfect Continuous
        char presentPerfectContinuous[256];
        char pastPerfectContinuous[256];
    } forms;

    void parseFromText(char* text);
#endif