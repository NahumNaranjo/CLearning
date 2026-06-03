#include "map.h"

//Finds key position in the array. Returns index or -1 if not found.
int FindKey(void* key, Map* map, size_t n){
    int result = vote(key);
    if(vote(key) >= 2){
    for(size_t i = 0; i < n; i++){
        if(strcmp(map[i].key, key) == 0){
            return (int)i;
        }
    }
        return 0;
    }
    for(size_t i = 0; i < n; i++){
        if(map[i].key == key){
            return (int)i;
        }
    }
    return 0;
}

//Finds value position in the array. Returns index or -1 if not found.
int FindValue(void** value, Map* map, size_t n, char mode){
    int result = vote(value);
    switch (mode){
        case 'c': //coincidence
            for(int i = 0; i < n; i++){
                for(int j = 0; j < (sizeof(value) / sizeof(void**)); i++){
                    if(result >= 2){
                        if(strcmp(map[i].value[j], value[j]) == 0){
                            return i;
                        }
                    } else {
                         if(map[i].value[j] == value[j]){
                            return i;
                         }
                    }
                }
            }    
        break;
        case 'a': //Full array
            int coincidence = 0;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < (sizeof(value) / sizeof(void**)); j++){
                     if(result >= 2){
                         if(strcmp(map[i].value[j], value[j] == 0)){
                            coincidence++;
                        }
                        if(coincidence == (sizeof(value) / sizeof(void**))){
                            return i;
                        }
                    } else {
                        if(map[i].value[j] == value[j]){
                            coincidence++;
                        }
                        if(coincidence == (sizeof(value) / sizeof(void**))){
                             return i;
                        }
                    }
                }
            }
        break;
        case 'l': // lone string
            for(int i = 0; i < n; i++){
                if(result >= 2){
                    if(strcmp(map[i].value, value) == 0){
                        return i;
                    }
                } else {
                    if(map[i].value == value){
                        return i;
                    }
                }
            }
        break;
    }
    return -1;
}

//Confirms the existence of a key.
int ExistKey(void* key, Map* map, size_t n){
    int result = vote(key);
    if(vote(key) >= 2){
        for(size_t i = 0; i < n; i++){
            if(strcmp(map[i].key, key) == 0){
                return 1;
            }
        }
        return 0;
    }
    for(size_t i = 0; i < n; i++){
        if(map[i].key == key){
            return 1;
        }
    }
    return 0;
}

//Confirms the existence of a value.
int ExistValue(void** value, Map* map, size_t n, char mode){
        int result = vote(value);
    switch (mode){
        case 'c':
            for(int i = 0; i < n; i++){
                for(int j = 0; j < (sizeof(value) / sizeof(void**)); i++){
                    if(result >= 2){
                        if(strcmp(map[i].value[j], value[j]) == 0){
                            return 1;
                        }
                    } else {
                         if(map[i].value[j] == value[j]){
                                return 1;
                         }
                    }
                }
            }    
        break;
        case 'a':
            int coincidence = 0;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < (sizeof(value) / sizeof(void**)); j++){
                     if(result >= 2){
                         if(strcmp(map[i].value[j], value[j] == 0)){
                            coincidence++;
                        }
                        if(coincidence == (sizeof(value) / sizeof(void**))){
                            return 1;
                        }
                    } else {
                        if(map[i].value[j] == value[j]){
                            coincidence++;
                        }
                        if(coincidence == (sizeof(value) / sizeof(void**))){
                             return 1;
                        }
                    }
                }
            }
        break;
        case 'l':
            for(int i = 0; i < n; i++){
                if(result >= 2){
                    if(strcmp(map[i].value, value) == 0){
                        return 1;
                    }
                } else {
                    if(map[i].value == value){
                        return 1;
                    }
                }
            }
        break;
    }
    return 0;
}   

Map* createMap(int size) {
    Map* returning = (Map*)malloc(sizeof(Map) * size);
    if (returning) {
        for (size_t i = 0; i < size; i++) {
            returning[i].key = NULL;
            returning[i].value = NULL;
        }
    }
    return returning;
}