#ifndef STRINGMANIPULATION_H
#define STRINGMANIPULATION_H
    #include <string.h>
    #include <stdio.h>
    #include <ctype.h>

    char* trimWhitespace(char* str);
    char* LineGetter(char* line, size_t size, FILE* file);
    void cleanBackSlash(char* source);
#endif