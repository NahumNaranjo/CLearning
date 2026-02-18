//! DEPRACTED
//!  USE CFM.C INSTEAD
//!  KEPT ONLY FOR OLDER TOOLS' COMPATIBILITY
//! TO BE REMOVED

#include "lookForRootFiles.h"
#include <string.h>

FILE* lookForRootFiles(char* filename, char* type){
    char path[1024];
    snprintf(path, sizeof(path), "C:\\InCGames\\CL\\%s", filename);
    FILE *fp = fopen(path, type);
    if(fp == NULL){
        return NULL;
    }
    return fp; // caller must close
}

char* rootFilePath(){
    return "C:\\InCGames\\CL\\";
}

char* ListDirectories(char* directory){
    char path[1024];
    strncpy(path, directory, sizeof(path)-4);
    path[sizeof(path)-1] = '\0';
    strcat(path, "\\*");
    
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(path, &findData);
    
    if (hFind == INVALID_HANDLE_VALUE) {
        return NULL;
    }
    
    char* directories = malloc(1024 * sizeof(char));
    if(!directories) {
        FindClose(hFind);
        return NULL;
    }
    directories[0] = '\0';
    
    do {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0) {
                if(strlen(directories) + strlen(findData.cFileName) + 2 < 1024) {
                    strcat(directories, findData.cFileName);
                    strcat(directories, "\n");
                }
            }
        }
    } while (FindNextFileA(hFind, &findData));
    
    FindClose(hFind);
    return directories;
}