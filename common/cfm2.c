#include "cfm2.h"

// Looks for files inside the CL folder path in InCGames parent folder
// Falls back to the current repository directory if the hardcoded path is not available.
FILE* lookInRoot(char* filename, char* type){
    if(!filename || !type) {
        return NULL;
    }

    char normalized[1024];
    strncpy(normalized, filename, sizeof(normalized) - 1);
    normalized[sizeof(normalized) - 1] = '\0';
    cleanBackSlash(normalized);

    while(normalized[0] == '/' || normalized[0] == '\\'){
        memmove(normalized, normalized + 1, strlen(normalized));
    }

    char cwd[1024] = {0};
    getcwd(cwd, sizeof(cwd));

    char parent[1024] = {0};
    if(cwd[0]){
        strncpy(parent, cwd, sizeof(parent) - 1);
        parent[sizeof(parent) - 1] = '\0';
        char* lastSlash = strrchr(parent, '/');
        if(!lastSlash) lastSlash = strrchr(parent, '\\');
        if(lastSlash) {
            *lastSlash = '\0';
        }
    }

    char candidates[6][1024];
    int count = 0;

    if(strchr(filename, ':') || filename[0] == '/' || filename[0] == '\\'){
        strncpy(candidates[count++], normalized, sizeof(candidates[0]));
    }
    else {
        snprintf(candidates[count++], sizeof(candidates[0]), "C:/InCGames/CL/%s", normalized);
        if(cwd[0]){
            snprintf(candidates[count++], sizeof(candidates[0]), "%s/%s", cwd, normalized);
            snprintf(candidates[count++], sizeof(candidates[0]), "%s/common/%s", cwd, normalized);
        }
        if(parent[0]){
            snprintf(candidates[count++], sizeof(candidates[0]), "%s/%s", parent, normalized);
            snprintf(candidates[count++], sizeof(candidates[0]), "%s/common/%s", parent, normalized);
        }
    }

    for(int i = 0; i < count; i++){
        FILE *fp = fopen(candidates[i], type);
        if(fp){
            return fp;
        }
    }
    return NULL;
}

char** capCheck(char** config, size_t* capacity, size_t length){
    if(!capacity) return config;
    if(length + 1 >= *capacity){
        size_t newCapacity = *capacity + (*capacity >> 2);
        if(newCapacity <= length + 1){
            newCapacity = length + 2;
        }
        char** tmp = (char**)realloc(config, sizeof(char*) * newCapacity);
        if(tmp){
            config = tmp;
            *capacity = newCapacity;
        }
    }
    return config;
}

// returns the CL folder path in InCGames parent folder
char* getRootFilePath(){
    return "C:/InCGames/cl/";
}

WIN32_FIND_DATA* listFiles(char* key, char* path){
    static WIN32_FIND_DATA buffer[512];
    size_t count = 0;
    WIN32_FIND_DATA wfd;
    HANDLE hfind = INVALID_HANDLE_VALUE;
    char fullPath[2048];

    if(!path){
        snprintf(fullPath, sizeof(fullPath), "%s*.*", getRootFilePath());
    }else if(strstr(path, "C:/") == NULL){
        snprintf(fullPath, sizeof(fullPath), "%s%s/*.*", getRootFilePath(), path);
    }else if(strstr(path, "/*.*") == NULL){
        snprintf(fullPath, sizeof(fullPath), "%s/*.*", path);
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
    strcat(path, "/*");
    
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
    if(!name || !type) return NULL;
    if(strcmp(type, "fr") != 0 && strcmp(type, "frb") != 0 && strcmp(type, "p") != 0){
        return NULL;
    }

    const char* searchRoot = root;
    char* cwdRoot = NULL;
    if(searchRoot == NULL){
        searchRoot = getRootFilePath();
    } else if(strcmp(searchRoot, "r") == 0){
        searchRoot = getRootFilePath();
    } else if(strcmp(searchRoot, "p") == 0){
        cwdRoot = (char*)malloc(1024);
        if(!cwdRoot || !getcwd(cwdRoot, 1024)) {
            free(cwdRoot);
            return NULL;
        }
        searchRoot = cwdRoot;
    }

    char normalizedName[1024];
    strncpy(normalizedName, name, sizeof(normalizedName) - 1);
    normalizedName[sizeof(normalizedName) - 1] = '\0';
    if(strstr(normalizedName, "/") != NULL){
        cleanBackSlash(normalizedName);
    }

    char* directories = getListedDirectories((char*)searchRoot);
    if(!directories){
        free(cwdRoot);
        return NULL;
    }

    char* token = strtok(directories, "\n");
    while(token){
        if(strstr(token, "/") != NULL){
            cleanBackSlash(token);
        }

        char fullPath[1024];
        snprintf(fullPath, sizeof(fullPath), "%s/%s", token, normalizedName);

        FILE* fp = NULL;
        if(strcmp(type, "frb") == 0){
            fp = fopen(fullPath, "rb");
        } else {
            fp = fopen(fullPath, "r");
        }

        if(fp == NULL){
            token = strtok(NULL, "\n");
            continue;
        }

        if(strcmp(type, "p") == 0){
            char* p = _strdup(fullPath);
            fclose(fp);
            free(directories);
            free(cwdRoot);
            return p;
        }

        free(directories);
        free(cwdRoot);
        return fp;
    }

    free(directories);
    free(cwdRoot);
    return NULL;
}

// returns a line by line string of the file
char** ParseFile(FILE* fp, size_t* line){
    if(fp == NULL) return NULL;

    size_t capacity = 128;
    size_t lines = 0;
    char** text = (char**)malloc(capacity * sizeof(char*));
    if(!text) return NULL;

    char buffer[1024];
    while(fgets(buffer, sizeof(buffer), fp)) {
        if(lines + 1 >= capacity) {
            text = capCheck(text, &capacity, lines);
            if(!text) return NULL;
        }

        size_t len = strlen(buffer);
        text[lines] = (char*)malloc(len + 1);
        if(!text[lines]){
            for(size_t j = 0; j < lines; j++){
                free(text[j]);
            }
            free(text);
            return NULL;
        }
        memcpy(text[lines], buffer, len + 1);
        lines++;
    }

    if(line) {
        *line = lines;
    }
    return text;
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

