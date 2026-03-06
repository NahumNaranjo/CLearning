#ifndef CFM2_H
#define CFM2_H
    #include <stdio.h>
    #include <windows.h>
    #include <direct.h>
    #include <stringManipulation.h>

    FILE* lookInRoot(char* filename, char* type);
    char* getListedDirectories(char* directory);
    char* getRootFilePath();
    void* findFile(char* name, char* root, char* type);
    char* ParseFile(FILE* fp, size_t* line);
#endif