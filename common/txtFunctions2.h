#ifndef txtFUNCTIONS2_H
#define txtFUNCTIONS2_H
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #include <stddef.h>
    #include <string.h>
    #include <stdlib.h>
    #include "cxtGeneralData.h"

    //counts all words in the txt file
    size_t countWords(char *txt);
    //counts new lines
    size_t countNewLines(char *txt);
    //finds most common words in the file
    CommonCommonWordsData commonMostCommonWord(char *txt);
    //! UNUSED FUNCTION
    /*
    //checks if the word 
    bool compareWords(char **token, Map *wordMap, size_t **size);
    */
    //analyzes the text and returns both data
    CommonAnalyzeTextData* commonAnalyzeText(char *txt, size_t *size);
#endif