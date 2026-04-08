#ifndef COMMON_MAP_H
#define COMMON_MAP_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef struct {
    void* key;
    void* value;
} Map;

//Finds key position in the array. Returns index or -1 if not found.
static inline int FindKey(void* key, Map* map, size_t n){
    for(size_t i = 0; i < n; i++){
        if(map[i].key == key){
            return (int)i;
        }
    }
    return -1;
}

//Finds value position in the array. Returns index or -1 if not found.
static inline int FindValue(void* value, Map* map, size_t n){
    for(size_t i = 0; i < n; i++){
        if(map[i].value == value){
            return (int)i;
        }
    }
    return -1;
}

//Confirms the existence of a key.
static inline bool ExistKey(void* key, Map* map, size_t n){
    for(size_t i = 0; i < n; i++){
        if(map[i].key == key){
            return true;
        }
    }
    return false;
}

//Confirms the existence of a value.
static inline bool ExistValue(void* value, Map* map, size_t n){
    for(size_t i = 0; i < n; i++){
        if(sizeof(value) == sizeof(char*) ? strcmp((char*)map[i].value, (char*)value) == 0: map[i].value == value){
            return true;
        }
    }
    return false;
}   

#endif
