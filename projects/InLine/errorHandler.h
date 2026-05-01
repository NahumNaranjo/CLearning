#ifndef INLINEERRORHANDLER_C
#define INLINEERRORHANDLER_C
    #include <string.h>
    #include <stdio.h>
    #include <clist.h>
    #include <time.h>

    typedef struct {
        int code;
        char* text;
    } inlineError;

    void logError(int *code, char* name);
    List getErrList();
#endif