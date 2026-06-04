#ifndef INLINE_H
#define INLINE_H
    #include "inputLogger.h"
    #include "renderer.h"
    #include "textParser.h"
    #include "inFile.h"
    #include "inputLogger.h"
    #include "dialog.h"
    #include "errorHandler.h"
    #include <clist.h>
    #include <cfm2.h>

    typedef struct{
        //Sign
        char* type;
        char* name;
        char* dev;
        char* genre;

        // Options
        size_t intBufferSize;
        size_t stringBufferSize;

        // Verbs
        List verbs;

        // Nouns
        List nouns;

        //Vars
        List ints;
        List strings;

    } ProgramInfo;

    typedef struct{
        char* name;
        long value;
    } IntVar;

    typedef struct{
        char* name;
        char value[1024];
    } stringVar;
    
    void textUpdate(char* text);
    void textStart(Verb* devVerbs);
#endif