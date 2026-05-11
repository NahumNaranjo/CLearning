#include "install.h"

int checkDirs(){
    char root[2048];
    char* dir = getCurrentDirectory();
    snprintf(root, sizeof(root), "%s/common/", dir);
    if(dirExists(root) == 0){
        #ifdef _WIN32
            _mkdir(root);
        #else
            mkdir(root);
        #endif
    }
    free(dir);
    char pack[2048];
    snprintf(pack, sizeof(pack), "%spackages/", getRootFilePath());
    if(dirExists(pack) == 0){
        printf("No packages root file found, please check your installation and, if needed, reinstall from https://github.com/NahumNaranjo/CLearning\n");
        return 0;
    }
    return 1;
}

int isAvailable(char* name){
    const char* tools[] = {"cui", "ariadne", "cba", "hermes", "cxt", "clist", "cmap"};
    for (int i = 0; tools[i]; i++){
        if(strcmp(name, tools[i]) == 0) return 1;
    }
    return 0;
}

void* clInstall(char* name){
    if(checkDirs() == 0){
        return NULL;
    }
    
    char root[2048];
    snprintf(root, sizeof(root), "%spackages/", getRootFilePath());
    if(!root) {
        printf("An error ocurred with the filepath creation.\n");
        return NULL;
    }

    if(isAvailable(name) == 0){
        printf("No such dependency found, check for new updates on https://github.com/NahumNaranjo/CLearning\n");
        return NULL;
    }

    char current[2048];
    char* dir = getCurrentDirectory();
    snprintf(current, sizeof(current), "%s/common", dir);
    free(dir);
    if(!current){
        printf("Couldn't obtain current working directory");
        return NULL;
    }
    
    // Build the source and destination paths
    char sourcePath[2048];
    char destPath[2048];
    snprintf(sourcePath, sizeof(sourcePath), "%s%s", root, name);
    snprintf(destPath, sizeof(destPath), "%s/%s", current, name);
    
    char command[2048];
    
    #if defined(_WIN32) || defined(_WIN64)
        snprintf(command, sizeof(command), "robocopy \"%s\" \"%s\" /e", sourcePath, destPath);
    #elif defined(__linux__) || defined(__APPLE__)
        snprintf(command, sizeof(command), "cp -r \"%s\" \"%s\"", sourcePath, current);
    #endif
    
    printf("Copying package: %s\n", command);
    system(command);
    
    return NULL; // Add appropriate return value
}