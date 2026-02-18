//! DEPRACTED
//! USE CFM.H INSTEAD
//! KEPT ONLY FOR OLDER TOOLS' COMPATIBILITY
//! TO BE REMOVED

#ifndef LOOKINGFORROOTFILES_H
#define LOOKINGFORROOTFILES_H
    #include <stdio.h>
    #include <windows.h>
    #include <stdlib.h>
    FILE* lookForRootFiles(char* filename, char* type);
    char* ListDirectories(char* directory);
    char* rootFilePath();
#endif