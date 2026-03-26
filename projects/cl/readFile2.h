#ifndef READFILE2_H
#define READFILE2_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <txtFunctions2.h>
    char* readFile(const char *file, size_t *size_out);
    CommonAnalyzeTextData* parseReportFiles(char *content);
    void* separateFiles(const char *file, size_t *size_out);
#endif