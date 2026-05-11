#include "errorHandler.h"
#include <stdlib.h>

static char* buildErrorCodesPath(void){
    static char path[512];
    char temp[512];
    strncpy(temp, __FILE__, sizeof(temp) - 1);
    temp[sizeof(temp) - 1] = '\0';
    char* lastBackslash = strrchr(temp, '\\');
    char* lastSlash = strrchr(temp, '/');
    char* lastSeparator = lastBackslash > lastSlash ? lastBackslash : lastSlash;
    if(lastSeparator){
        *(lastSeparator + 1) = '\0';
    } else {
        temp[0] = '\0';
    }
    snprintf(path, sizeof(path), "%serrorCodes.txt", temp);
    return path;
}

void logError(int *code, char* name){
    if(!code){
        fprintf(stderr, "logError: null code pointer\n");
        return;
    }

    List errList = getErrList();
    if(errList.allocated == 0){
        fprintf(stderr, "Couldn't allocate errList\n");
    }

    char error[1024];
    char* errorText = NULL;
    for (size_t i = 0; i < errList.size; i++){
        inlineError* err = (inlineError*)errList.content[i];
        if(!err) continue;
        if(err->code == *code){
            errorText = err->text;
            break;
        }
    }

    if(!errorText){
        fprintf(stderr, "Invalid error code: %d\n", *code);
        return;
    }

    time_t now = time(NULL);
    char* when = ctime(&now);
    if(when){
        size_t len = strlen(when);
        if(len && when[len - 1] == '\n'){
            when[len - 1] = '\0';
        }
    }

    snprintf(error, sizeof(error), "Error code number %d found at %s while executing %s: %s",
             *code,
             when ? when : "unknown time",
             name ? name : "unknown",
             errorText);
    fprintf(stderr, "%s\n", error);
}

List getErrList(){

    char* path = buildErrorCodesPath();
    FILE* fp = fopen(path, "r");
    if(!fp) {
        fprintf(stderr, "Couldn't open errorCodes.txt at '%s'\n", path);
        return CLIST_NULL;
    }

    if(fseek(fp, 0, SEEK_END) != 0){
        fclose(fp);
        return CLIST_NULL;
    }

    long length = ftell(fp);
    if(length < 0){
        fclose(fp);
        return CLIST_NULL;
    }
    rewind(fp);

    char* buffer = malloc((size_t)length + 1);
    if(!buffer){
        fprintf(stderr, "Couldn't allocate %ld bytes for a buffer\n", length);
        fclose(fp);
        return CLIST_NULL;
    }

    size_t read = fread(buffer, 1, (size_t)length, fp);
    fclose(fp);
    buffer[read] = '\0';

    List returning = createList(5);
    char* line = strtok(buffer, "\r\n");
    while(line){
        trimWhitespace(line);
        if(line[0] == '\0' || (line[0] == '/' && line[1] == '/')){
            line = strtok(NULL, "\r\n");
            continue;
        }

        char* delim = strstr(line, " = ");
        if(!delim){
            delim = strchr(line, '=');
        }
        if(!delim){
            line = strtok(NULL, "\r\n");
            continue;
        }

        *delim = '\0';
        char* codeText = line;
        char* message = delim + 1;
        trimWhitespace(codeText);
        trimWhitespace(message);
        if(message[0] == '='){
            message++;
            trimWhitespace(message);
        }

        inlineError* error = malloc(sizeof(*error));
        if(!error){
            line = strtok(NULL, "\r\n");
            continue;
        }
        error->code = atoi(codeText);
        error->text = strdup(message ? message : "");
        add(&returning, error);

        line = strtok(NULL, "\r\n");
    }

    free(buffer);
    return returning;
}