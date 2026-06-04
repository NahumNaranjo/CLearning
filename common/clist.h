#ifndef CLIST_H
#define CLIST_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <stddef.h>
    #include <string.h>
    #include <ctype.h>
    #include <setjmp.h>
    #include <signal.h>
    #include <math.h>
    static jmp_buf buf;

    #define CLIST_NULL (List){0}

    // Python is an engineering marvel
    typedef struct{
        void** content;
        size_t size;
        size_t allocated;
    } List;

    // Checks if the ist hasn't gone out of bounds
    static inline int capCheck(List* list){
        if(!list) return 0;
        if(list->allocated == 0){
            size_t newSize = 8;
            void **tmp = (void**)realloc(list->content, newSize * sizeof(void*));
            if(!tmp) return 0;
            list->content = tmp;
            memset(list->content + list->size, 0, (newSize - list->size) * sizeof(void*));
            list->allocated = newSize;
            return 1;
        }
        if(list->size >= list->allocated){
            size_t newSize = list->allocated + (list->allocated >> 2) + 1;
            void **tmp = (void**)realloc(list->content, newSize * sizeof(void*));
            if(!tmp) return 0;
            list->content = tmp;
            memset(list->content + list->size, 0, (newSize - list->size) * sizeof(void*));
            list->allocated = newSize;
        }
        return 1;
    }

    // Moves all the values of a list, index makes it stop at a specific point and orientation ('l' or 'r') marks where it'll begin
    static inline void moveList(List* list, size_t index, char orientation){
        if(!list || !list->content) return;
        if(orientation != 'l' && orientation != 'r') return;

        if(orientation == 'r'){
            /* move elements one position to the right starting at index */
            if(list->size == 0 || index > list->size) return;
            capCheck(list);
            for(size_t i = list->size; i > index; i--){
                list->content[i] = list->content[i-1];
            }
        } else {
            /* move elements one position to the left starting at index */
            if(list->size == 0 || index >= list->size) return;
            for(size_t i = index; i < list->size - 1; i++){
                list->content[i] = list->content[i+1];
            }
            list->content[list->size-1] = NULL;
        }
    }

    // Deletes the last item
    static inline void pop(List* list){
        if(!list || list->size == 0) return;
        list->content[list->size - 1] = NULL;
        list->size--;
    }

    // Deletes a specific index and reorganizes the list
    static inline void cherryPick(List* list, size_t index){
        if(!list || list->size == 0 || index >= list->size) return;
        for(size_t i = index; i < list->size - 1; i++){
            list->content[i] = list->content[i+1];
        }
        list->content[list->size - 1] = NULL;
        list->size--;
    }


    // Adds an item to the last position of the list
    static inline void append(List* list, void* obj){
        if(!list) return;
        if(!capCheck(list)) return;
        list->content[list->size] = obj;
        list->size++;
    }

    // Inserts an item to a specific index
    static inline void insert(List* list, void* obj, size_t index){
        if(!list) return;
        if(index > list->size) index = list->size;
        if(!capCheck(list)) return;
        for(size_t i = list->size; i > index; i--){
            list->content[i] = list->content[i-1];
        }
        list->content[index] = obj;
        list->size++;
    }

    // Adds an item to the first position of the list
    static inline void add(List* list, void* obj){
        if(!list) return;
        if(!capCheck(list)) return;
        for(size_t i = list->size; i > 0; i--){
            list->content[i] = list->content[i-1];
        }
        list->content[0] = obj;
        list->size++;
    }

    //TODO: ERROR MANAGER

    // creates an empty list
    static inline List* createList(size_t size){
        List* list = (List*)malloc(sizeof(List));
        if(!list) return NULL;
        list->size = 0;
        list->allocated = 0;
        list->content = NULL;

        if(size == 0) return list;

        size_t capacity;
        if (size < 8) {
            capacity = size + 3;
        } else {
            capacity = size + (size >> 2) + 6;
        }
        list->content = (void**)malloc(capacity * sizeof(void*));
        if(!list->content){
            free(list);
            return NULL;
        }
        memset(list->content, 0, capacity * sizeof(void*));
        list->allocated = capacity;
        return list;
    }

    static inline void destroyList(List *list) {
        if (list->content) {
            free(list->content);
            list->content = NULL;
            list->size = 0;
            list->allocated = 0;
        }
    }

    // Returns the length of the list
    static inline size_t len(List* list){
        return list->size;
    }

    static inline void clistHandleCrash(int sig){
        longjmp(buf, 1);
    }

    //* ↓↓↓ Ariadne borrowings ↓↓↓

    // returns x quantity of characters of a string, f returns the first x and l returns the last x
    static inline char* clistgetXChars(char* string, int chars, char mode){
        if(chars <= 0 || !chars){
            perror("Can't get less than 1 character");
            return (char*)NULL;
        }
        if(!string){
            perror("No string to read");
            return (char*)NULL;
        }
        if((mode != 'l' && mode != 'f') || !mode){
            perror("Unsopported mode");
            return (char*)NULL;
        }
        char *returning = (char*)malloc(sizeof(char)*chars);
        if(mode == 'f'){
            for(int i = 0; i < chars && string[i] != '\0'; i++){
                returning[i] = string[i];
            }
            returning[chars] = '\0';
        } else if(mode == 'l'){
            int len = (int)strlen(string);
            int start = len - chars;
            if(start < 0) start = 0;
            int idx = 0;
            for(int i = start; i < len; i++){
                returning[idx++] = string[i];
            }
            returning[idx] = '\0';
        }
        return returning;
    }

    // First string check, borrowed from Ariadne
    static inline short clistSimpleHeuristic(char* string){
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
    static inline float clistEntropyAnalysis(char* value) {
        if (!value || !clistSimpleHeuristic(value)) return 8.0; // High entropy if not string
    
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
    static inline short clistSafeString(char* string){
        if(!string) return 0;
        if(setjmp(buf) == 0){
            signal(SIGSEGV, clistHandleCrash); 
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

    static inline int clistVote(void* value){
        signal(SIGSEGV, clistHandleCrash);
        // String guessing
        int votingResults = 0;
        char* string = (char*)value;

        votingResults += clistSafeString(string);
        votingResults += clistSimpleHeuristic(string);
        float entropy = clistEntropyAnalysis(string);
        if(entropy > 3.0 && entropy < 6.0){
            votingResults += 1;
        }
        return votingResults;
    }
    
    //* ↑↑↑ Ariadne borrowings ↑↑↑

    // Obiviously, couldn't make them O(1) D:

    // returns the index of the first appearance of an element
    // WARNING: Use only for string or numbers, structs are not supported
    static inline long findFirst(List* list, void* value){
        if(!list || !value) return -1;
        int votingResults = clistVote(value);
        for (size_t i = 0; i < list->size; i++){
            if(votingResults > 2){
                if(list->content[i] && strcmp((char*)list->content[i], (char*)value) == 0){
                    return (long)i;
                }
            } else {
                if(list->content[i] && *(size_t *)list->content[i] == *(size_t *)value) return (long)i;
            }
        }
        return -1;
    }
    //TODO: Add an universal resizer

    // returns the indexes of all appearances of a certain element
    static inline long* findAll(List* list, void* value){
        if(!list || !value) return NULL;
        int votingResults = clistVote(value);
        size_t capacity = 16;
        long *results = (long*)malloc(sizeof(long) * capacity);
        if(!results) return NULL;
        size_t count = 0;
        for(size_t i = 0; i < list->size; i++){
            int matched = 0;
            if(votingResults > 2){
                if(list->content[i] && strcmp((char*)list->content[i], (char*)value) == 0) matched = 1;
            } else {
                if(list->content[i] && *(size_t*)list->content[i] == *(size_t*)value) matched = 1;
            }
            if(matched){
                if(count >= capacity){
                    capacity *= 2;
                    long *tmp = (long*)realloc(results, sizeof(long) * capacity);
                    if(!tmp) break;
                    results = tmp;
                }
                results[count++] = (long)i;
            }
        }
        /* shrink to fit and append terminator -1 */
        if(count == 0){
            free(results);
            return NULL;
        }
        long *final = (long*)realloc(results, sizeof(long) * (count + 1));
        if(final){
            final[count] = -1;
            return final;
        }
        results[count] = -1;
        return results;
    }

#endif