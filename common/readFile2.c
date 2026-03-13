#include "readFile2.h"


void* separateFiles(const char *file, size_t *size_out){
    if(!file) return NULL;
    if(strstr(file, "analysis_report_") != NULL){
        return commonParseReportFiles(readFile(file, size_out));
    } else{
        return readFile(file, size_out);
    }
    return NULL;
}

char* readFile(const char *file, size_t *size_out){
    if(!file) return NULL;
    FILE *f = fopen(file, "rb");
    if (!f) {
        return NULL;
    }

    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return NULL;
    }

    long size_long = ftell(f);

    if (size_long < 0) {
        fclose(f);
        return NULL;
    }

    size_t size = (size_t)size_long;

    if (size > SIZE_MAX - 1) {  // avoid overflow
        fclose(f);
        return NULL;
    }

    if (fseek(f, 0, SEEK_SET) != 0) {
        fclose(f);
        return NULL;
    }

    char *buffer = malloc(size + 1);
    if (!buffer) {
        fclose(f);
        return NULL;
    }

    size_t read_bytes = fread(buffer, 1, size, f);
    if (read_bytes != size) {
        free(buffer);
        fclose(f);
        return NULL;
    }

    buffer[size] = '\0';

    fclose(f);
    if (size_out) *size_out = size;
    return buffer;
}

CommonAnalyzeTextData* commonParseReportFiles(char *content){
    CommonAnalyzeTextData* data = malloc(sizeof(CommonAnalyzeTextData));
    if(!data) return NULL;
    data->tracker = NULL;
    data->mostUsed = NULL;
    data->words = malloc(sizeof(size_t));
    data->newLines = malloc(sizeof(size_t));
    data->uniqueWords = 0;
    if(!data->words || !data->newLines){
        free(data->words);
        free(data->newLines);
        free(data);
        return NULL;
    }
    char* line = strtok(content, "\n");
    size_t index = 0;
    while(line != NULL){
        if(strstr(line, "Total Words: ") != NULL){
            sscanf(line, "Total Words: %zu", data->words);
        } else if(strstr(line, "Total New Lines: ") != NULL){
            sscanf(line, "Total New Lines: %zu", data->newLines);
        } else if(strstr(line, "Most Common Word: ") != NULL){
            data->mostUsed = strdup(line + strlen("Most Common Word: "));
        } else if(strstr(line, "Total Unique Words: ") != NULL){
            sscanf(line, "Total Unique Words: %zu", &data->uniqueWords);
            data->tracker = malloc(data->uniqueWords * sizeof(CxtMap));
            if(!data->tracker){
                free(data->words);
                free(data->newLines);
                free(data->mostUsed);
                free(data);
                return NULL;
            }
        } else if(strstr(line, "Word: ") != NULL){
            while(index < data->uniqueWords && line != NULL){
                char word[256];
                int frequency;
                sscanf(line, "Word: %255[^-] - Frequency: %d", word, &frequency);
                data->tracker[index].key = strdup(word);
                data->tracker[index].timesAppeared = frequency;
                index++;
                line = strtok(NULL, "\n");
            }
        }
        line = strtok(NULL, "\n");
    }
    return data;
}