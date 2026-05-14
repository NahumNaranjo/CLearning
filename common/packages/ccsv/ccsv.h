#ifndef CCSV_H
#define CCSV_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// --- Conditional Dependency Management ---
#ifdef USE_CLIST
    #include <clist.h>
#else
    // Fallback definitions so the code compiles without the headers
    typedef char** List;
    #define CLIST_NULL NULL
#endif
#ifdef USE_ARIADNE
    #include <ariadne.h>
#endif

static inline int isKeyword(const char* compared, char keywordsArray[256][256], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(compared, keywordsArray[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Fixed resize: takes a pointer to the array and updates its capacity variable
static inline void resize(int needed_count, int* current_capacity, char*** array_ptr) {
    if (needed_count >= *current_capacity) {
        int new_capacity = *current_capacity + (*current_capacity >> 2) + 4;
        char** temporary = (char**)realloc(*array_ptr, new_capacity * sizeof(char*));
        if (temporary) {
            *array_ptr = temporary;
            *current_capacity = new_capacity;
        }
    }
}

static inline List parse(char* path, char* keywords) {
    if (strstr(path, ".csv") == NULL) {
        printf("That's not a valid CSV file. Returning to main menu.\n");
        return CLIST_NULL;
    }

    FILE* fp = fopen(path, "r");
    if (!fp) {
        printf("Couldn't open the file.\n");
        return CLIST_NULL;
    }
    
    #ifdef USE_ARIADNE
        trimWhitespace(keywords);
    #else
        char* end;

        while(isspace((unsigned char)*keywords)) keywords++;
        end = keywords + strlen(keywords) - 1;
        while(end > keywords && isspace((unsigned char)*end)) end--;

        *(end+1) = 0;
    #endif

    char keywordsArray[256][256] = {{0}}; 
    int position = 0;
    int charNum = 0;
    
    if (keywords) {
        for (int i = 0; keywords[i] && position < 256; i++) {
            if (keywords[i] == ',' || keywords[i] == ';' || keywords[i] == '|') {
                keywordsArray[position][charNum] = '\0';
                position++;
                charNum = 0;
                continue;
            }
            if (charNum < 255) {
                keywordsArray[position][charNum++] = keywords[i];
            }
        }
        if (charNum > 0) position++; // Count the final keyword
    }

    char buffer[1024];
    
    #ifdef USE_CLIST
        List results = createList(256);
    #else
        int capacity = 32;
        int count = 0;
        char** results = (char**)malloc(sizeof(char*) * capacity);
    #endif

    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = 0;
        char* token = strtok(buffer, ",;|");
        
        while (token) {
            if (keywords && isKeyword(token, keywordsArray, position)) {
                token = strtok(NULL, ",;|");
                continue;
            }
            
            #ifdef USE_CLIST
                add(&results, token);
            #else
                resize(count + 1, &capacity, &results);
                results[count] = strdup(token); 
                count++;
            #endif
            token = strtok(NULL, ",;|");
        }
    }
    
    #ifndef USE_CLIST
        resize(count + 1, &capacity, &results);
        results[count] = NULL;
    #endif

    fclose(fp);
    return results;
}
#endif // CCSV_H
