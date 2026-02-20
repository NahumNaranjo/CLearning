#ifndef CFM_H
#define CFM_H
    #include <stdio.h>
    #include <windows.h>
    #include <direct.h>
    #include <stringManipulation.h>

    FILE* lookInRoot(char* filename, char* type);
    char* ListDirectories(char* directory);
    char* rootFilePath();
    void* findFile(char* name, char* root, char* type);
    char* ParseFile(FILE* fp, size_t line);
#endif