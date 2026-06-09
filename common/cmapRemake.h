#ifndef CMAP_REMAKE_H
#define CMAP_REMAKE_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    typedef enum {RED, BLACK} Color;
    typedef struct RBNode{
        char* key;
        void* value;
        Color color;
        struct RBNode* left;
        struct RBNode* right;
        struct RBNode* parent;
    } RBNode;

    typedef struct{
        RBNode** buckets;
        // Keep it at a power of 2 because computers love that ;D
        size_t capacity;
        size_t size;
        float loadFactor;
    } HashMap;

    // FNV-1a Hash
    static inline unsigned int hashVal(const char* key, size_t capacity){
        unsigned int hash = 2166136261u;
        while(*key){
            hash ^= (unsigned char)*key++; // never seen ^=
            hash *= 16777619u;
        }

        return hash & (capacity - 1);
    }

    // Creates a new tree node
    static inline RBNode* createNode(const char* key, void *value){
        RBNode* node = (RBNode*)malloc(sizeof(RBNode));
        node->key = strdup(key);
        node->value = value;
        node->color = RED;
        node->left = node->right = node->parent = NULL;
    }

    // Rotates to the left
    static inline void rotateLeft(RBNode **root, RBNode* x){
        RBNode* y = x->right;
        x->right = y->left;
        if(y->left != NULL) y->left->parent = x;
        y->parent = x->parent;
        if(x->parent == NULL) *root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // Rotates to the right
    static inline void rotateRight(RBNode **root, RBNode *y) {
        RBNode *x = y->left;
        y->left = x->right;
        if (x->right != NULL) x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == NULL) *root = x;
        else if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    // Java-style rb tree
    static inline void rbInsertFixup(RBNode** root, RBNode *z){
        while(z->parent && z->parent->parent->color == RED){
            if(z->parent == z->parent->parent->left){
                RBNode* y = z->parent->parent->right;
                if(y && y->color == RED){
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if(z == z->parent->right){
                        z = z->parent->parent;
                        rotateLeft(root, z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateRight(root, z->parent->parent);
                }
            } else {
                RBNode* y = z->parent->parent->left;
                if(y && y->color == RED){
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if(z == z->parent->left){
                        z = z->parent;
                        rotateRight(root, z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateLeft(root, z->parent->parent);
                }
            }
        }
        (*root)->color = BLACK;
    }

    static inline int treeInsert(RBNode** root, const char* key, void* value){
        RBNode* z = createNode(key, value);
        RBNode* y = NULL;
        RBNode* x = *root;
        while(x != NULL){
            y = x;
            int cmp = strcmp(z->key, x->key);
            if(cmp < 0){
                x = x->left;
            } else if(cmp > 0){
                x = x->right;
            } else{
                x->value = value;
                free(z->key);
                free(z);
                return 0;
            }
        }

        z->parent = y;
        if(y==NULL){
            *root = z;
        } else if(strcmp(z->key, y->key) < 0){
            y->left = z;
        } else {
            y->right = z;
        }
        rbInsertFixup(root, z);
        return 1;
    }

    static inline void CMapRemakePut(HashMap* map, const char *key, void* value);

    static inline void migrateTree(HashMap *new_map, RBNode *node) {
        if (node == NULL) return;
        migrateTree(new_map, node->left);
        migrateTree(new_map, node->right);
    
        CMapRemakePut(new_map, node->key, node->value);
    
        free(node->key);
        free(node);
    }

    static inline void CMapRemakeResize(HashMap *map) {
        size_t old_capacity = map->capacity;
        RBNode **old_buckets = map->buckets;

        map->capacity = old_capacity * 2;
        map->buckets = (RBNode**)calloc(map->capacity, sizeof(RBNode*));
        map->size = 0;

        for (size_t i = 0; i < old_capacity; i++) {
            if (old_buckets[i] != NULL) {
                migrateTree(map, old_buckets[i]);
            }
        }
        free(old_buckets);
    }

    static inline void* CmapRemakeGet(HashMap *map, const char *key) {
        unsigned int index = hashVal(key, map->capacity);
        RBNode *node = map->buckets[index];

        while (node != NULL) {
            int cmp = strcmp(key, node->key);
            if (cmp < 0) node = node->left;
            else if (cmp > 0) node = node->right;
            else return node->value; 
        }
        return NULL;
    }

    void CMapRemakePut(HashMap *map, const char *key, void *value) {
        if ((float)(map->size + 1) / map->capacity > map->loadFactor) {
            CMapRemakeResize(map);
        }

        unsigned int index = hashVal(key, map->capacity);
        if (treeInsert(&map->buckets[index], key, value)) {
            map->size++;
        }
    }

    HashMap* CMapCreate() {
        HashMap *map = (HashMap*)malloc(sizeof(HashMap));
        map->capacity = 16; // Must be power of 2
        map->size = 0;
        map->loadFactor = 0.75f;
        map->buckets = (RBNode**)calloc(map->capacity, sizeof(RBNode*));
        return map;
    }
#endif