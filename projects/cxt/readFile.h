#ifndef READFILE_H
#define READFILE_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <hermes.h>
    #include "txtFunctions.h"
    char* readFile(const char *file, size_t *size_out);
    AnalyzeTextData* parseReportFiles(char *content);
    void* separateFiles(const char *file, size_t *size_out);
#endif