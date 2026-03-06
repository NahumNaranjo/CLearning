#ifndef GENERALDATA_H
#define GENERALDATA_H

    #include <stdio.h>
    #include "map.h"

    typedef struct {
        Map* tracker;
        char* mostUsed;
        size_t* words;
        size_t* newLines;
        size_t uniqueWords;
    } AnalyzeTextData;
    typedef struct  {
        Map* tracker;
        char* mostUsed;
        size_t count;
    } commonWordsData;
    typedef struct {
        char version[50];
        char name[100];
        char cmakeMinVersion[20];
        char ninjaMinVersion[20];
        char output[100];
    } BuildInfo;
    typedef struct  {
        char mode;
    } calcData;


#endif