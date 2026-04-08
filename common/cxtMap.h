#ifndef CXT_MAP_H
#define CXT_MAP_H
    #include <stdbool.h>
    #include <stddef.h>
    #include <string.h>

    typedef struct {
        char* key;
        int timesAppeared;
    } CxtMap;

    // Index of key in map, or -1 if not found. Pass used count as n.
    int CxtFindKey(char* key, CxtMap* map, size_t n);
    // True if key exists in the first n entries.
    bool CxtExistKey(char* key, CxtMap* map, size_t n);

#endif