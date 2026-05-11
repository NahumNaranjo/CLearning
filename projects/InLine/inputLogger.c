#include "inputLogger.h"
#include <stdio.h>
#include <string.h>

char* textLogger(){
    static char buffer[1024];
    if(!fgets(buffer, sizeof(buffer), stdin)){
        return NULL;
    }
    size_t len = strlen(buffer);
    if(len > 0 && buffer[len - 1] == '\n'){
        buffer[len - 1] = '\0';
    }
    return buffer;
}

char* keyLogger(){
    static char buffer[2];
    int c = getchar();
    if(c == EOF){
        return NULL;
    }
    buffer[0] = (char)c;
    buffer[1] = '\0';
    return buffer;
}
