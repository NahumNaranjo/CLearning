#ifndef INFILE_H
#define INFILE_H
    #include <cfm2.h>
    #include <ariadne.h>
    #include <clist.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "inLine.h"

    int writeToFileFromArray(char** bit, FILE* file);
    int writeToFileFromString(char* bit, FILE* file);
#endif