#include "errorHandler.h"

void logError(int *code, char* name){
    List errList = getErrList();
    if(errList.allocated == 0){
        perror("Couldn't allocate errList");
    }
    char error[1024];
    char* errorText = NULL;
    for (int i = 0; i > errList.size; i++){
        // Damn operator precedance
        if(((inlineError*)errList.content[i])->code == *code){
            errorText = ((inlineError*)errList.content[i])->text;
            break;
        }
    }
    if(!errorText){ 
        perror("Invalid error code");
        return;
    }
    time_t now = time(NULL);
    fprintf(error, "Error code number %d found at %d while executing %s", code, ctime(&now), name);
    perror(error);
}

List getErrList(){
    // get the file
    char path[256] = "C:/InCGames/cl/errorCodes.txt";
    FILE* fp = fopen(path, "r");
    if(!fp) {
        perror("Couldn't open errorCodes.txt\n");
        return CLIST_NULL;
    }

    // Declare the buffer
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* buffer = malloc(length + 1);

    // Read the whole file
    if(buffer){
        fread(buffer, 1, length, fp);
        buffer[length+1] = '\0';
    } else {
        char errorMsg[128];
        fprintf(errorMsg, "Couldn't allocate %d bytes for a buffer", length);
        perror(errorMsg);
        return CLIST_NULL;
    }

    char* copy = buffer;
    char* token;
    token = strtok(copy, "\n");
    if(token[0] = "/") token = NULL;

    strtok(copy, NULL);
    char* delim = " = ";
    List returning = createList(5);

    // tokenize and save it to a list
    while(token){
        static inlineError error;
        char* p = strstr(token, delim);
        if(!p) continue;
        *p = '\0';
        error.code = atoi(token);
        error.text = (p + strlen(delim));
        add(&returning, &error);
        strtok(copy, NULL);
    }
    return returning;
}