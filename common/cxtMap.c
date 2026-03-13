#include "cxtMap.h"

//Finds key position in the array. Returns index or -1 if not found.
int CxtFindKey(char* key, CxtMap* map, size_t n){
    for(size_t i = 0; i < n; i++){
        if(map[i].key == key){
            return (int)i;
        }
    }
    return -1;
}


//Confirms the existence of a key.
bool CxtExistKey(char* key, CxtMap* map, size_t n){
    for(size_t i = 0; i < n; i++){
        if(map[i].key == key){
            return true;
        }
    }
    return false;
}
  