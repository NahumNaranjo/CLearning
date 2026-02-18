#include "cfm.h"

FILE* lookInRoot(char* filename, char* type){
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

void* findFile(char* name, char* root, char* type){
    if(!type) return NULL;
    if(
        strcmp(type, "fr") != 0 && 
        strcmp(type, "frb") != 0 &&
        strcmp(type, "p") != 0
    ) return NULL;

    if(strcmp(root, "r") == 0){
        root = rootFilePath();
    }
    if(strcmp(root, "p") == 0){
        root = NULL;
        root = _getcwd(NULL, 0);
    }

    if(strstr(name, "\\") != NULL){
        cleanBackSlash(name);
    }

    char* directories = ListDirectories(root);

    char* token = strtok(directories, "\n");
    FILE* fp;
    while(token){
        if(strstr(token, "\\") != NULL){
            cleanBackSlash(token);
        }
        strcat(token, ("/%s", name));
        fp = fopen(token, "r");

        if(fp == NULL){
            fclose(fp);
            token = strtok(NULL, "\n");
            continue;
        }

        if(strcmp(type, "p") == 0){
            return token;
        }
        if(strcmp(type, "r") == 0){
            return fp;
        }
        fclose(fp);
        fp = NULL;
        if(strstr(type, "fr")){
            fp = fopen(root, type);
        }
    }
    return NULL;
}

void cleanBackSlash(char* source) {
    if (source == NULL) return NULL;
    
    for (size_t i = 0; source[i] != '\0'; i++) {
        if (source[i] == '\\') {
            source[i] = '/';
        }
    }
}