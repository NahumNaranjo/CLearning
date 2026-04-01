#include "textParser.h"

void* verbParser(char* verb){
    void* function;
    return function;
}

short isVerb(char* token, Verb* verbs){
}

void createDefaultVerbs(Verb* verbs){
    char* verbsChars[] = {
        "take", "put", "walk", "run", "attack", "shoot", "kill", "revive"
    };
    static char shorts[] = {
        't', 'p', 'w', 'r', 'a', 's', 'k', 'r'
    };
    int maxVerbs = sizeof(verbsChars) / sizeof(verbsChars[0]);
    for (int i = 0; i < maxVerbs; i++){
        verbs[i].full = verbsChars[i];
        verbs[i].cut = &shorts[i];
    }
}

void parseFromText(char* text){
    Verb* defaultVerbs;
    createDefaultVerbs(defaultVerbs);
    //TODO: IMPLEMENT DEVVERBS IN NEXT UPDATE!!!
    // on it

    // Detect verbs, nouns and adjectives
    char* copy = text;
    char* token;
    token = strtok(copy, " ");
    while(token != NULL){
        if (isVerb(token, defaultVerbs) == 1) verbParser(token);
        else{
            
        }
    }
}