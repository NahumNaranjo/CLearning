#include "writeFile2.h"
#include "platform.h"


bool commonWriteFile(const char* path, CommonAnalyzeTextData* data) {
    FILE* file = fopen(path, "w");
    if (file == NULL) {
        return false;
    }
    fprintf(file, "Text Analysis Report\n");
    fprintf(file, "Total Words: %zu\n", *data->words);
    fprintf(file, "Total New Lines: %zu\n", *data->newLines);
    fprintf(file, "Most Common Word: %s\n", data->mostUsed);
    fprintf(file, "Total Unique Words: %zu\n", data->uniqueWords);
    CxtMap* tracker = data->tracker;
    for (size_t i = 0; i < data->uniqueWords; i++) {
        fprintf(file, "Word: %s - Frequency: %d\n", tracker[i].key, tracker[i].timesAppeared);
    }
    fclose(file);
    return true;
}

int mkdir_p(const char *path) {
    char tmp[256];
    char *p = NULL;
    size_t len;
    
    snprintf(tmp, sizeof(tmp), "%s", path);
    len = strlen(tmp);
    
    // Remove trailing slash if present
    if (tmp[len - 1] == '\\' || tmp[len - 1] == '/') {
        tmp[len - 1] = 0;
    }
    
    // Create directory and all parents
    for (p = tmp + 1; *p; p++) {
        if (*p == '\\' || *p == '/') {
            *p = 0;
            mkdir(tmp);  // Ignore errors (directory might already exist)
            *p = '\\';
        }
    }
    
    return mkdir(tmp);  // Create final directory
}

char* getFilePath(){
    mkdir_p("c:\\InCGames\\cl\\cxt\\reports");
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    static char path[256];
    snprintf(path, sizeof(path), "c:\\InCGames\\cl\\cxt\\reports\\analysis_report_%02d%02d%02d.txt", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    return path;
}

bool DirectoryExists(const char* path) {
    struct _stat info;
    if (_stat(path, &info) != 0) {
        return false; // Cannot access path
    }
    return (info.st_mode & _S_IFDIR) != 0; // Check if it's a directory
}