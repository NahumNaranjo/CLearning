#include "textParser.h"

void* verbParser(char* verb, Verb* verbs){
    if(!verb){
        return NULL;
    }
    return NULL;
}

short isVerb(char* token, Verb* verbs){
    if(!token || !verbs){
        return 0;
    }

    for(int i = 0; verbs[i].full != NULL; i++){
        if(strcmp(token, verbs[i].full) == 0){
            return 1;
        }
        if(verbs[i].shortened && strcmp(token, verbs[i].shortened) == 0){
            return 1;
        }
    }
    return 0;
}

void createDefaultVerbs(Verb* verbs){
    char* verbsChars[] = {
        "take", "put", "walk", "run", "attack", "shoot", "kill", "revive"
    };
    char* shorts[] = {
        "t", "p", "w", "r", "a", "s", "k", "r"
    };
    int maxVerbs = sizeof(verbsChars) / sizeof(verbsChars[0]);
    for (int i = 0; i < maxVerbs; i++){
        verbs[i].full = strdup(verbsChars[i]);
        verbs[i].shortened = shorts[i][0];
    }
    verbs[maxVerbs].full = NULL;
    verbs[maxVerbs].shortened = NULL;
}

void parseFromText(char* text){
    if(!text){
        return;
    }

    Verb defaultVerbs[9];
    createDefaultVerbs(defaultVerbs);

    char* copy = strdup(text);
    if(!copy){
        return;
    }

    char* token = strtok(copy, " \t\r\n");
    while(token != NULL){
        if(isVerb(token, defaultVerbs) == 1){
            verbParser(token);
        } else {
            printf("Unknown token: %s\n", token);
        }
        token = strtok(NULL, " \t\r\n");
    }

    free(copy);
}
