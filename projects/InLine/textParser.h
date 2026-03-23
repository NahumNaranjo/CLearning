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
        char* full;
        char* cut;
    } Verb;

    void parseFromText(char* text);
#endif