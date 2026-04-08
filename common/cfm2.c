#include "cfm2.h"

// Looks for files inside the CL folder path in InCGames parent folder
FILE* lookInRoot(char* filename, char* type){
    char path[1024];
    snprintf(path, sizeof(path), "C:/InCGames/CL/%s", filename);
    FILE *fp = fopen(path, type);
    if(fp == NULL){
        return NULL;
    }
    return fp; // caller must close
}

// returns the CL folder path in InCGames parent folder
char* getRootFilePath(){
    return "C:\\InCGames\\cl\\";
}

WIN32_FIND_DATA* listFiles(char* key, char* path){
    static WIN32_FIND_DATA buffer[512];
    size_t count = 0;
    WIN32_FIND_DATA wfd;
    HANDLE hfind = INVALID_HANDLE_VALUE;
    char fullPath[2048];

    if(!path){
        snprintf(fullPath, sizeof(fullPath), "%s*.*", getRootFilePath());
    }else if(strstr(path, "C:\\") == NULL){
        snprintf(fullPath, sizeof(fullPath), "%s%s\\*.*", getRootFilePath(), path);
    }else if(strstr(path, "\\*.*") == NULL){
        snprintf(fullPath, sizeof(fullPath), "%s\\*.*", path);
    }
    printf("[DEBUG] filepath: %s\n", fullPath);
    hfind = FindFirstFileA(fullPath, &wfd);
    if(hfind != INVALID_HANDLE_VALUE){
        do{
            if(!key && count < 511){
                buffer[count] = wfd;
                count++;
                continue;
            }
            if(strstr(wfd.cFileName, key) != NULL && count < 511){
                buffer[count] = wfd;
                count++;
                continue;
            }
        } while (FindNextFileA(hfind, &wfd) != 0);
        FindClose(hfind);
    }
    memset(&buffer[count], 0, sizeof(WIN32_FIND_DATA));

    return buffer;

}

// lists all child dirs of a root one
char* getListedDirectories(char* directory){
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

// Looks for a file in a root dir and all its child dirs
void* findFile(char* name, char* root, char* type){
    if(!type) return NULL;
    if(
        strcmp(type, "fr") == 0 && 
        strcmp(type, "frb") == 0 &&
        strcmp(type, "p") == 0
    ) {}
    else return NULL;

    if(strcmp(root, "r") == 0){
        root = getRootFilePath();
    }
    if(strcmp(root, "p") == 0){
        root = NULL;
        root = _getcwd(NULL, 0);
    }

    char* directories = getListedDirectories(root);

    char* token = strtok(directories, "\n");
    FILE* fp;
    while(token){
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
        if(strcmp(type, "fr") == 0){
            return fp;
        }
        fclose(fp);
        fp = NULL;
        if(strstr(type, "frb")){
            fp = fopen(root, "rb");
            return fp;
        }
    }
    return NULL;
}

// returns a line by line string of the file
char* ParseFile(FILE* fp, size_t* line){
    if(fp == NULL) return NULL;

    //TODO it really shouldnt go here but CSON is a great idea

    char* text[2048];
    size_t size;
    if(line == 0 || line == NULL){
        fgets(text[0], 0, fp);
        for(int i = 1; text[i]; i++){
            fgets(text[i], sizeof(text), fp);
        }
    }

    for (int i = 0; *line > i; i++){
        if(fgets(text[i], size, fp) != NULL){
            continue;
        }
        break;
    }
}

int dirExists(const char* path) {
    struct stat sb;

    // Call stat() to get file information. Returns 0 on success, -1 on failure.
    if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
        return 1; // It is a directory
    } else {
        return 0; // It does not exist or is not a directory
    }
}

TCHAR* getCurrentDirectory(){
    TCHAR* tszBuffer = malloc(MAX_PATH * sizeof(TCHAR));
    if (!tszBuffer) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }
    DWORD dwRet;

    // Get the current directory path
    dwRet = GetCurrentDirectory(MAX_PATH, tszBuffer);

    if (dwRet == 0) {
        printf("Error: Failed to get current directory (Error Code: %lu)\n", GetLastError());
        free(tszBuffer);
        return NULL;
    } else if (dwRet > MAX_PATH) {
        printf("Error: Buffer too small, required size is %lu\n", dwRet);
        free(tszBuffer);
        return NULL;
    }
    return tszBuffer;
}