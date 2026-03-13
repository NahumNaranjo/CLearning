#ifndef CXT_GENERALDATA_H
#define CXT_GENERALDATA_H
    #include <stdio.h>
    #include "cxtMap.h"
    
    typedef struct {
        CxtMap* tracker;
        char* mostUsed;
        size_t* words;
        size_t* newLines;
        size_t uniqueWords;
    } CommonAnalyzeTextData;
    typedef struct  {
        CxtMap* tracker;
        char* mostUsed;
        size_t count;
    } CommonCommonWordsData;

#endif