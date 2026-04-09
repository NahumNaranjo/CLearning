#ifndef INLINEERRORHANDLER_C
#define INLINEERRORHANDLER_C
    #include <string.h>

    typedef struct  {
        int error;
        char* name;
        char* time;
    } inlineErrorCode;
    void logError(inlineErrorCode* code);
#endif