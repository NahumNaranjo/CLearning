#ifndef INFILE_H
#define INFILE_H
    #include <cfm2.h>
    #include <ariadne.h>
    #include <clist.h>
    typedef struct{
        char* title;
        char* dev;
        char* genre;
        char* verbs;
        char* nouns;
        char* adjectives;
        char* script;
        char* characters;
    } programInfo;

    programInfo* innit(char* root);
    int writeToFileFromArray(char** bit, FILE* file);
    int writeToFileFromString(char* bit, FILE* file);
#endif