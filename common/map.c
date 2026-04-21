#include "map.h"

//Finds key position in the array. Returns index or -1 if not found.
int FindKey(void* key, Map* map, size_t n){
    for(size_t i = 0; i < n; i++){
        if(map[i].key == key){
            return (int)i;
        }
    }
    return -1;
}

//Finds value position in the array. Returns index or -1 if not found.
int FindValue(void* value, Map* map, size_t n){
    for(size_t i = 0; i < n; i++){
        if(map[i].value == value){
            return (int)i;
        }
    }
    return -1;
}

//Confirms the existence of a key.
bool ExistKey(void* key, Map* map, size_t n){
    for(size_t i = 0; i < n; i++){
        if(map[i].key == key){
            return true;
        }
    }
    return false;
}

//Confirms the existence of a value.
bool ExistValue(void* value, Map* map, size_t n){
    for(size_t i = 0; i < n; i++){
        if(map[i].value == value){
            return true;
        }
    }
    return false;
}   