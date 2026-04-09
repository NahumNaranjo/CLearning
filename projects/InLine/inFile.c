#include "inFile.h"

programInfo* innit(char* root){
    // Open file
    cleanBackSlash(root);
    FILE* fp = fopen(root, "r");
    if(!fp){
        printf("Invalid root file\n");
        return NULL;
    }

    programInfo info;
    char buffer[1024];
    while(fgets(buffer, 1024, fp) != NULL){
        char* bufCopy = buffer;
        char* param;
        param = strtok(bufCopy, " = ");
        
        char dest[1024];
        // If {}, stores the values inside them
        if(strstr(buffer, "{") != 0){
            int idx1 = (strchr(buffer, '{') - buffer);
            int idx2 = (strchr(buffer, '}') - buffer);

            strncpy(dest, buffer + idx1, idx2 - idx1 + 1);
            dest[idx2 - idx1] = '\0';
            trimWhitespace(dest);
        } else{
            char* paramCopy = param;
            strtok(NULL, " = ");
            strcpy(dest, param);
            strcpy(param, paramCopy);
        }

        // Sign
        if(strcmp(param, "title") != 0){ // Game name
            info.title = dest;
            continue;
        } else if(strcmp(param, "dev") != 0){ // dev name
            info.dev = dest;
            continue;
        } else if(strcmp(param, "genre") != 0){ // game genre
            info.genre = dest;
            continue;
        }

        char* token;
        char* copy = dest;
        token = strtok(dest, ",");
        size_t loop = 0;
        while(token){
            char add[1024];
            if(strcmp(param, "verbs") != 0){
                if(loop == 0){
                    strcat(info.verbs, token);
                    continue;
                }
                sprintf(add, ", %s", token);
                strcat(info.verbs, add);
            } else if(strcmp(param, "nouns") != 0){
                if(loop == 0){
                    strcat(info.nouns, token);
                    continue;
                }
                sprintf(add, ", %s", token);
                strcat(info.nouns, add);
            } else if(strcmp(param, "adjectives") != 0){
                if(loop == 0){
                    strcat(info.adjectives, token);
                    continue;
                }
                sprintf(add, ", %s", token);
                strcat(info.adjectives, add);
            } else if(strcmp(param, "script") != 0){
                if(loop == 0){
                    strcat(info.script, token);
                    continue;
                }
                sprintf(add, ", %s", token);
                strcat(info.script, add);
            } else if(strcmp(param, "characters") != 0){
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
    char devEnv[1024];
    char titleEnv[1024];
    char scriptProgress[1024];

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
        perror("Couln't set scriptProgress to env, program might crash.");
    }

    return &info;
}

// write to an existing config file
int writeToFileFromArray(char** bit, FILE* file){
    char* name = bit[0];
    size_t idx = 0;

    size_t length = 0;
    for(int i = 0; bit[i] != NULL; i++){
        length += strlen(bit[i]);
    }

    char* values = malloc(length + 1);
    if(values == NULL){
        printf("Memory allocation failed\n");
        return 1;
    }

    values[0] = '\0';
    for(int i = 0; bit[i] != NULL; i++){
        strcat(values, bit[i]);
    }

    fprintf(file, "%s = {%s}", bit, values);
    free(values);
    return 0;
}

int writeToFileFromString(char* bit, FILE* file){
    if(!file || !bit) return 1;
    char* copy = bit;
    char* token; 
    token = strtok(copy, ";");
    List tokenList = createList(128);
    if(!tokenList.content) return 1;
    while(token){
        add(&tokenList, token);
        strtok(NULL, ";");
    }
    char* arg;
    char* val;
    for(size_t i = 0; i < tokenList.size; i++){
        arg = strtok(tokenList.content[i], " = ");
        val = arg;
        strtok(NULL, " = ");
        fprintf(file, "%s = %s", arg, val);
        if(tokenList.content[i+1] == NULL) break;
    }
    destroyList(&tokenList);
    return 0;
}

// If you find this, i really wanna play songs of syx