#include "inFile.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void appendCommaSeparated(char* dest, const char* value){
    if(!dest || !value) return;
    char* copy = strdup(value);
    if(!copy) return;
    char* token = strtok(copy, ",");
    while(token){
        trimWhitespace(token);
        if(*token != '\0'){
            if(dest[0] != '\0'){
                strcat(dest, ", ");
            }
            strcat(dest, token);
        }
        token = strtok(NULL, ",");
    }
    free(copy);
}

static char* parseValue(const char* raw){
    if(!raw) return NULL;
    char* value = strdup(raw);
    if(!value) return NULL;
    trimWhitespace(value);
    size_t len = strlen(value);
    if(len >= 2 && value[0] == '{' && value[len - 1] == '}'){
        value[len - 1] = '\0';
        memmove(value, value + 1, len - 1);
        trimWhitespace(value);
    }
    return value;
}

programInfo innit(char* root){
    programInfo info = {0};
    info.title = calloc(1024, 1);
    info.dev = calloc(1024, 1);
    info.genre = calloc(1024, 1);
    info.verbs = calloc(1024, 1);
    info.nouns = calloc(1024, 1);
    info.adjectives = calloc(1024, 1);
    info.script = calloc(1024, 1);
    info.characters = calloc(1024, 1);

    if(!info.title || !info.dev || !info.genre || !info.verbs ||
       !info.nouns || !info.adjectives || !info.script || !info.characters){
        fprintf(stderr, "Memory allocation failed while initializing program info\n");
        return info;
    }

    cleanBackSlash(root);
    FILE* fp = fopen(root, "r");
    if(!fp){
        fprintf(stderr, "Invalid root file: %s\n", root);
        return info;
    }

    char buffer[1024];
    while(fgets(buffer, sizeof(buffer), fp) != NULL){
        trimWhitespace(buffer);
        if(buffer[0] == '\0' || (buffer[0] == '/' && buffer[1] == '/')){
            continue;
        }

        char* delimiter = strchr(buffer, '=');
        if(!delimiter){
            continue;
        }

        *delimiter = '\0';
        char* key = buffer;
        char* valueText = delimiter + 1;
        trimWhitespace(key);
        trimWhitespace(valueText);
        char* value = parseValue(valueText);
        if(!value){
            continue;
        }

        if(strcmp(key, "title") == 0){
            strncpy(info.title, value, 1023);
        } else if(strcmp(key, "dev") == 0){
            strncpy(info.dev, value, 1023);
        } else if(strcmp(key, "genre") == 0){
            strncpy(info.genre, value, 1023);
        } else if(strcmp(key, "verbs") == 0){
            appendCommaSeparated(info.verbs, value);
        } else if(strcmp(key, "nouns") == 0){
            appendCommaSeparated(info.nouns, value);
        } else if(strcmp(key, "adjectives") == 0){
            appendCommaSeparated(info.adjectives, value);
        } else if(strcmp(key, "script") == 0){
            strncpy(info.script, value, 1023);
        } else if(strcmp(key, "characters") == 0){
            strncpy(info.characters, value, 1023);
        }
        free(value);
    }
    fclose(fp);

    char* devEnv = malloc(1024);
    char* titleEnv = malloc(1024);
    char* scriptProgress = malloc(1024);

    if(!devEnv || !titleEnv || !scriptProgress){
        fprintf(stderr, "Memory allocation failed for environment strings\n");
    } else {
        sprintf(devEnv, "DEV_NAME=%s", info.dev);
        sprintf(titleEnv, "TITLE=%s", info.title);
        sprintf(scriptProgress, "SCRIPT_PROGRESS=%d", 0);

        if(putenv(devEnv) != 0){
            perror("Couldn't set dev name to env, error logs won't work correctly");
        }
        if(putenv(titleEnv) != 0){
            perror("Couldn't set title name to env, error logs won't work correctly");
        }
        if(putenv(scriptProgress) != 0){
            perror("Couldn't set scriptProgress to env, program might crash.");
        }
    }

    return info;
}

int writeToFileFromArray(char** bit, FILE* file){
    if(!bit || !file || !bit[0]){
        return 1;
    }

    size_t length = 0;
    for(int i = 1; bit[i] != NULL; i++){
        length += strlen(bit[i]);
        if(bit[i + 1] != NULL){
            length += 2;
        }
    }

    char* values = malloc(length + 1);
    if(values == NULL){
        printf("Memory allocation failed\n");
        return 1;
    }

    values[0] = '\0';
    for(int i = 1; bit[i] != NULL; i++){
        if(i > 1){
            strcat(values, ", ");
        }
        strcat(values, bit[i]);
    }

    fprintf(file, "%s = {%s}", bit[0], values);
    free(values);
    return 0;
}

int writeToFileFromString(char* bit, FILE* file){
    if(!file || !bit) return 1;

    char* copy = strdup(bit);
    if(!copy) return 1;

    char* token = strtok(copy, ";");
    while(token){
        trimWhitespace(token);
        char* arg = strtok(token, " =");
        char* val = strtok(NULL, " =");
        if(arg && val){
            fprintf(file, "%s = %s\n", arg, val);
        }
        token = strtok(NULL, ";");
    }

    free(copy);
    return 0;
}

// If you find this, i really wanna play songs of syx