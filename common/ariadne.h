#ifndef ARIADNE_H
#define ARIADNE_H
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <setjmp.h>
    #include <signal.h>
    #include <math.h>
    static jmp_buf buf;

    static inline void handleCrash(int sig){
        longjmp(buf, 1);
    }

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

    // Cleans "\" off in a file path
    static inline void cleanBackSlash(char* source) {
        if (source == (char*)NULL) return;
    
        for (size_t i = 0; source[i] != '\0'; i++) {
            if (source[i] == '\\') {
                source[i] = '/';
            }
        }
    }

    // returns x quantity of characters of a string, f returns the first x and l returns the last x
    static inline char getXChars(char* string, int chars, char mode){
        if(chars <= 0 || !chars){
            perror("Can't get less than 1 character");
            return '\0';
        }
        if(!string){
            perror("No string to read");
            return '\0';
        }
        if((mode != 'l' && mode != 'f') || !mode){
            perror("Unsopported mode");
            return '\0';
        }
        char *returning = (char*)malloc(sizeof(char)*chars);
        if(mode == 'f'){
            for(int i = 0; i < chars; i++){
                returning[i] = string[i];
            }
        } else if(mode == 'l'){
            for(int i = chars; i > 0; i--){
                returning[-(i - chars)] = string[-(i - chars)];
            }
        }
        return *returning;
    }

    // First string check, borrowed from Ariadne
    static inline short SimpleHeuristic(char* string){
        short nullFound = 0;
        // Checks for \0
        for(int i = 0; i < 256; i++){
            // checks for valid string chars
            if(
                isprint((unsigned char)string[i]) || 
                isspace((unsigned char)string[i]) ||
                string[i] == '\n' || string[i] == '\t' ||
                string[i] == '\\' || string[i] == '\"' ||
                string[i] == '\'' || string[i] == '\b' ||
                string[i] == '\a' || string[i] == '\r' ||
                string[i] == '\v' || string[i] == '\f'
            ){
                continue;
            }

            // checks for null terminator
            if(string[i] == '\0' && i > 0){
                return 1;
            }
            if(string[i] == '\0' && i == 0){
                return 0;
            }
        }
        return 0;
    }

    // return's a string's randomness
    static inline float EntropyAnalysis(char* value) {
        if (!value || !SimpleHeuristic(value)) return 8.0; // High entropy if not string
    
        int counts[256] = {0};
        int len = 0;
    
        // scan up to 256 chars or until null
        for (int i = 0; i < 256 && value[i] != '\0'; i++) {
            counts[(unsigned char)value[i]]++;
            len++;
        }
    
        if (len == 0) return 8.0;
    
        float entropy = 0;
        for (int i = 0; i < 256; i++) {
            if (counts[i] > 0) {
                float p = (float)counts[i] / len;
                entropy -= p * log2f(p);
            }
        }
        return entropy;
    }

    // Does string-only operations and returns 1 if it all went alright
    static inline short SafeString(char* string){
        if(!string) return 0;
        if(setjmp(buf) == 0){
            signal(SIGSEGV, handleCrash); 
            volatile size_t len = 0;
            char* p = string;
            for(int i = 0; i < 512; i++) {
                if (p[i] == '\0') {
                    signal(SIGSEGV, SIG_DFL);
                    return 1;
                }
            }
            signal(SIGSEGV, SIG_DFL);
            return 0;
        } else {
            signal(SIGSEGV, SIG_DFL);
            return 0;
        }
        
    }


    static inline int vote(void* value){
        signal(SIGSEGV, handleCrash);
        // String guessing
        int votingResults = 0;
        char* string = (char*)value;

        votingResults += SafeString(string);
        votingResults += SimpleHeuristic(string);
        float entropy = EntropyAnalysis(string);
        if(entropy > 3.0 && entropy < 6.0){
            votingResults += 1;
        }
        return votingResults;
    }

    static inline char* toLowerCase(char* string){
        char* returning = malloc(sizeof(char) * 128);
        for(int i = 0; i < strlen(string); i++){
            returning[i] = tolower(string[i]);
        }
        return returning;
    }

    static inline char* toUpperCase(char* string){
        char* returning = malloc(sizeof(char) * 128);
        for(int i = 0; i < strlen(string); i++){
            returning[i] = toupper(string[i]);
        }
        return returning;
    }
    
#endif