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
        char* thirdPerson;
        char* shortVer;
        void* action;
    } Verb;

    typedef struct{
        char* text;
        void* value;
    } Attribute;

    typedef struct{
        char* name;
        char* description;
        int type;
        Attribute attributes[];
    } Noun;

    typedef struct{
        char* text;
        char* attribute;
        int modifier;
    } Adjective;

    void createDefaultVerbs(Verb* verbs);
    void parseFromText(char* text);
    void* verbParser(char* verb, Verb* verbs);
#endif