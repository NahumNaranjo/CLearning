#ifndef CFM2_H
#define CFM2_H
    #include <stdio.h>
    #include "platform.h"
    #include <ariadne.h>

    FILE* lookInRoot(char* filename, char* type);
    char* getListedDirectories(char* directory);
    char* getRootFilePath();
    void* findFile(char* name, char* root, char* type);
    char** ParseFile(FILE* fp, size_t* line);
    WIN32_FIND_DATA* listFiles(char* key, char* path);
    int dirExists(const char* path);
    TCHAR* getCurrentDirectory();
#endif