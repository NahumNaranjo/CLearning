#ifndef ARIADNE_H
#define ARIADNE_H
    #include <string.h>
    #include <stdio.h>
    #include <ctype.h>

    // chops the whitespaces
    static inline char* trimWhitespace(char* str) {
        char* end;

        // Trim leading space
        while(isspace((unsigned char)*str)) str++;

        if(*str == 0)  // All spaces?
            return str;

        // Trim trailing space
        end = str + strlen(str) - 1;
        while(end > str && isspace((unsigned char)*end)) end--;

        // Write new null terminator
        *(end+1) = 0;

        return str;
    }

    // Cleans "\\" off in a file path
    static inline void cleanBackSlash(char* source) {
        if (source == NULL) return;
    
        for (size_t i = 0; source[i] != '\0'; i++) {
            if (source[i] == '\\') {
                source[i] = '/';
            }
        }
    }
    
#endif