#include "inFile.h"


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

/*programInfo innit(char* root){
    programInfo info = {0};
    info.title = calloc(1024, 1);
    info.dev = calloc(1024, 1);
    info.genre = calloc(1024, 1);
    // info.verbs = (Verb*)calloc(1024, 1);
    info.nouns = calloc(1024, 1);
    info.adjectives = calloc(1024, 1);
    info.script = calloc(1024, 1);
    info.characters = calloc(1024, 1);

    if(!info.title || !info.dev || !info.genre || !info.verbs ||
       !info.nouns || !info.adjectives || !info.script || !info.characters){
        fprintf(stderr, "Memory allocation failed while initializing program info\n");
        return info;
    }

    #ifndef _WIN32
        cleanBackSlash(root);
    #endif
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
}*/
ProgramInfo info;


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

char* unzip(FILE* fp){

}

void* readFile(char* path, char mode){
    FILE* fp = fopen(path, "r");
    switch (mode){
        case 's':
            if(strstr(path, ".docx") == 0){
                
            }
            if(strstr(path, ".txt") == 0){

            }
            break;
        case 'k':
            if(strstr(path, ".docx") == 0){
                
            }
            if(strstr(path, ".csv") == 0){

            }
            break;
        case 'd':
            if(strstr(path, ".docx") == 0){
                
            }
            if(strstr(path, ".csv") == 0){
                char* keywords = "developer, dev, owner, genre, topic, date";
                Map* data = parse(path, keywords);

            }
            break;
    }
    fclose(fp);
}


void build(char* script){
    if(!strstr(script, ".inscript") && !strstr(script, ".inpt") && !strstr(script, ".incrpt") && !strstr(script, ".insc")){
        perror("Not a valid inscript file");
        return;
    }
    FILE* fp = fopen(script, "r");
    if(!fp){
        perror("Couldn't open the script");
        return;
    }
    char buffer[8192];
    fgets(buffer, sizeof(buffer), fp);
    if(!strstr(buffer, "#TYPE ")){
        perror("Couldn't read the game type correctly, please check the first line of your file and inscript documentation. For more information, email nnaranjo1@ucol.mx");
        return;
    }
    if(!strstr(buffer, "SEQUENCE") && !strstr(buffer, "SEQUENCE_BASED") && !strstr(buffer, "WRITTEN")){
        perror("Invalid game type.");
        return;
    }

    char* token;
    char* endptr;
    if(strstr(buffer, "WRITTEN")){
        printf("Written game type not supported yet");
        return;
    }
    if(strstr(buffer, "SEQUENCE") || strstr(buffer, "SEQUENCE_BASED")){
        info.type = "SEQUENCE";
    }
    while(fgets(buffer, sizeof(buffer), fp)){
        if(strstr(buffer, "##")){
            continue;
        }
        if(strstr(buffer, "#SECTION")){
            takeArgument(buffer, token);
            if(strcmp(token, "sign") == 0){
                while(fgets(buffer, sizeof(buffer), fp) && !strstr(buffer, "#SECTION")){
                    if(strstr(buffer, "NAME: ")){
                        takeArgument(buffer, token);
                        info.name = token;
                        continue;
                    }
                    if(strstr(buffer, "DEV: ")){
                        takeArgument(buffer, token);
                        info.dev = token;
                        continue;
                    }
                    if(strstr(buffer, "GENRE: ")){
                        takeArgument(buffer, token);
                        info.genre = token;
                    }
                }
            }
            if(strcmp(token, "options") == 0){
                while(fgets(buffer, sizeof(buffer), fp) && !strstr(buffer, "#SECTION")){
                    if(strstr(buffer, "INT_BUFFER_SIZE: ")){
                        takeArgument(buffer, token);
                        info.intBufferSize = strtol(token, &endptr, 10);
                        continue;
                    }
                    if(strstr(buffer, "STRING_BUFFER_SIZE: ")){
                        takeArgument(buffer, token);
                        info.stringBufferSize = strtol(token, &endptr, 10);
                        continue;
                    }
                }
            }
            if(strcmp(token, "data") == 0){
                while(fgets(buffer, sizeof(buffer), fp) && !strstr(buffer, "#SECTION")){
                    if(strstr(buffer, "INT: ")){
                        takeArgument(buffer, token);
                        info.intBufferSize = strtol(token, &endptr, 10);
                        continue;
                    }
                    if(strstr(buffer, "STRING: ")){
                        takeArgument(buffer, token);
                        info.stringBufferSize = strtol(token, &endptr, 10);
                        continue;
                    }
                }
            }
            if(strcmp(token, "nouns") == 0){
                
            }
            if(strcmp(token, "verbs") == 0){
                
            }
            if(strcmp(token, "adjectives") == 0){
                
            }
            if(strcmp(token, "script") == 0){
                
            }
        }
    }

    perror("There was an unexpected error, please check your code, you can find more information in the documentation or emailing nnaranjo1@ucol.mx.");
}


void SequenceInterpreter(char* instruction, ProgramInfo* info){

}

void WrittenInterpreter(char* instruction, ProgramInfo* info){

}


void takeArgument(char buffer[], char* token){
    token = strtok(buffer, " ");
    token = strtok(NULL, " ");
}

char interpreter(char* line){
    /*if(strstr(line, "#SECTION ")){
        return 's';
    }
    if(strstr(line, "#CLOSE")){
        return 'c';
    }
    if(strstr(line, "#GOTO")){
        return 'g';
    }
    if(strstr(line, "#VALUE")){
        return 'v';
    }
    if(strstr(line, "(EMBED)")){
        return 'e';
    }
    if(strstr(line, "(CALC)")){
        return '+';
    }
    if(strstr(line, "(COLOR: ")){
        return 'l';
    }
    if(strstr(line, "(OPTIONS)")){
        return 'o';
    }*/
}
// If you find this, i really wanna play songs of syx
// Hey! Alex from the future here, you did play songs of syx that day