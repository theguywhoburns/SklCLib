#ifndef _SKLC_LIB_HASHMAP_H_
#define _SKLC_LIB_HASHMAP_H_

#include <sklc_lib/defines.h>

typedef struct unordered_hashmap {
    u32 capacity;
    void* data;

    void (*insert)(unordered_hashmap* map, const char* key, u64 key_length, void* value, u64 value_size);
    void (*clear) (unordered_hashmap* map);
    b8   (*exists)(unordered_hashmap* map, const char* key, u64 key_size);
    void*(*get_at)(unordered_hashmap* map, const char* key, u64 key_size);
} unordered_hashmap;


void unordered_hashmap_create(unordered_hashmap* map, u32 capacity);
void unordered_hashmap_destroy(unordered_hashmap* map);

#endif//_SKLC_LIB_HASHMAP_H_