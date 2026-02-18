#ifndef CFM_H
#define CFM_H
    #include <stdio.h>
    #include <windows.h>
    #include <direct.h>
    FILE* lookInRoot(char* filename, char* type);
    char* ListDirectories(char* directory);
    char* rootFilePath();
#endif