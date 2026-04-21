#ifndef COMMON_MAP_H
#define COMMON_MAP_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    void* key;
    void* value;
} Map;

// Pass the same Map* to every call (allocate once, reuse).
// Returns index of key in map, or -1 if not found.
int FindKey(void* key, Map* map, size_t n);

// Returns index of value in map, or -1 if not found.
int FindValue(void* value, Map* map, size_t n);

bool ExistKey(void* key, Map* map, size_t n);
bool ExistValue(void* value, Map* map, size_t n);

#endif
