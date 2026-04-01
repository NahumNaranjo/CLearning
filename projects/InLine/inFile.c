#include "inFile.h"

programInfo* innit(char* root){
    cleanBackSlash(root);
    FILE* fp = fopen(root, "r");
    if(!fp){
        printf("Invalid root file\n");
        return NULL;
    }

    programInfo info;
    char buffer[1024];
    while(fgets(buffer, 1024, fp) != NULL){
        char bufCopy = buffer;
        char* param;
        param = strtok(bufCopy, " = ");
        
        char dest[1024];
        if(strstr(buffer, "{") != 0){
            int idx1 = strchr(buffer, '{');
            int idx2 = strchr(buffer, '}');

            strncpy(dest, buffer + idx1, idx2 - idx1 + 1);
            dest[idx2 - idx1] = '\0';
            trimWhitespace(dest);
        } else{
            char paramCopy = param;
            strtok(NULL, " = ");
            strcpy(dest, param);
            param = paramCopy;
        }

        if(strcmp(param, "title") != NULL){
            info.title = dest;
            return;
        } else if(strcmp(param, "dev") != NULL){
            info.dev = dest;
            return;
        } else if(strcmp(param, "genre") != NULL){
            info.genre = dest;
            return;
        }

        char* token;
        char* copy = dest;
        token = strtok(dest, ",");
        size_t loop = 0;
        while(token){
            char add[1024];
            if(strcmp(param, "verbs") != NULL){
                if(loop == 0){
                    strcat(info.verbs, token);
                    continue;
                }
                sprintf(add, ", %s", token);
                strcat(info.verbs, add);
            } else if(strcmp(param, "nouns") != NULL){
                if(loop == 0){
                    strcat(info.nouns, token);
                    continue;
                }
                sprintf(add, ", %s", token);
                strcat(info.nouns, add);
            } else if(strcmp(param, "adjectives") != NULL){
                if(loop == 0){
                    strcat(info.adjectives, token);
                    continue;
                }
                sprintf(add, ", %s", token);
                strcat(info.adjectives, add);
            } else if(strcmp(param, "script") != NULL){
                if(loop == 0){
                    strcat(info.script, token);
                    continue;
                }
                sprintf(add, ", %s", token);
                strcat(info.script, add);
            } else if(strcmp(param, "characters") != NULL){
                if(loop == 0){
                    strcat(info.characters, token);
                    continue;
                }
                sprintf(add, ", %s", token);
                strcat(info.characters, add);
            }
            if(loop < 1) loop++;
            strtok(NULL, ",");
        }
    }
}

// use a mode in case bit is an array of strings, if not, use s mode
void writeInFile(char* bit, FILE* file, char mode){
    if(!file) return;
    if(mode != 'a' && mode != 's') return;
    if(mode == 'a'){
        char* name = bit[0];
        size_t idx = 0;

        size_t length = 0;
        for(int i = 0; bit[i] != NULL; i++){
            length += strlen(bit[i]);
        }

        char* values = malloc(length + 1);
        if(values == NULL){
            printf("Memory allocation failed\n");
            return;
        }

        values[0] = '\0';
        for(int i = 0; bit[i] != NULL; i++){
            strcat(values, bit[i]);
        }

        fprintf(file, "%s = {%s}", bit, values);
        free(values);
        return;
    } else {
        fprintf(file, "%s", bit);
    }    
}