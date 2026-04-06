#ifndef CLIST_H
#define CLIST_H
    #include <stdio.h>
    #include <stdlib.h>

    typedef struct{
        void** content;
        int size;
        int allocated;
    } List;

    // Deletes the last item
    static inline void pop(List* list){

    }

    // Deletes a specific index
    static inline void cherryPick(List* list, size_t index){

    }


    // Adds an item to the last position of the list
    static inline void append(List* list, void* obj){

    }

    // Inserts an item to the a specific index
    static inline void insert(List* list, void* obj, size_t index){

    }

    // Adds an item to the first position of the list
    static inline void add(List* list, void* obj){

    }

    // create an empty list (Only compatible with string, byte, double, int, char, long, float and short)
    static inline void create(size_t size, char* type){
        if(
            type[0] != 's' && type[0] != 'i' && type[0] != 'h' &&
            type[0] != 'b' && type[0] != 'c' && type[0] != 'f' &&
            type[0] != 'd' && type[0] != 'l' 
        ) return;
        List list;
        list.allocated = size;
        switch(type[0]){
            case 's':
                char** stringArray = malloc(size * 1.225);
                break;
        }
    }

    // Returns the length of the list
    static inline int* len(List* list){
        return &list->allocated;
    }
#endif