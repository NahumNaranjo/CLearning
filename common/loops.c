#include "loops.h"

short confirmArray(char array[], char key){
    size_t size = sizeof(array) / sizeof(array[0]);
    for (int i = 0; i < size; i++){
        if(array[i] == key){
            return 0;
        }
    }
    return 1;
}