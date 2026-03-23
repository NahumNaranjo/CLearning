#include "textParser.h"

void* verbParser(char* verb){
    void* function;
    return function;
}

short isVerb(char* token, Map* verbs){
}

Verb* createDefaultVerbs(){
    char* verbsChars[] = {
        "take", "put", "walk", "run", "attack", "shoot", "kill", "revive"
    };
    char* shorts[] = {
        't', 'p', 'w', 'r', 'a', 's', 'k', 'r'
    };
    Verb verbs[256];
    for (int i = 0; verbsChars[i]; i++){
        verbs[i].full = verbsChars[i];
        verbs[i].cut = shorts[i];
    }
    return verbs;
}

void parseFromText(char* text){
    Verb* defaultVerbs = createDefaultVerbs();
    //TODO: IMPLEMENT DEVVERBS IN NEXT UPDATE!!!
    char* copy = text;
    char* token;
    token = strtok(copy, " ");
    while(token != NULL){
        if (isVerb(token, defaultVerbs) == 1) verbParser(token);
        else{
            
        }
    }
}