#include "inLine.h"

void textStart(Verb* devVerbs){
    (void)devVerbs;
}

void textUpdate(char* text){
    if(!text){
        return;
    }
    parseFromText(text);
}
