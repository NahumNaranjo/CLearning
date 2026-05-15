#ifndef TEXTPARSER_H
#define TEXTPARSER_H
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <map.h>
    #include <cfm2.h>

    typedef struct{
        void* function;
        void* arguments[];
    } instruction;

    typedef struct{
        char* full;
        char shortened;
        void* action;

        // Time forms
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
    } Verb;

    void parseFromText(char* text);
#endif