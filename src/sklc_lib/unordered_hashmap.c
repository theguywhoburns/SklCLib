#include <stdlib.h>
#include <string.h>
#include <sklc_lib/utils/hash.h>
#include <sklc_lib/unordered_hashmap.h>

typedef struct kv_pair {
    const char* key;
    void* value;
} kv_pair;


void unordered_hashmap_create(unordered_hashmap* map, u32 capacity) {
    map->capacity = capacity;
    map->data = malloc(sizeof(kv_pair) * capacity);
    memset(map->data, 0, sizeof(kv_pair) * capacity);

    map->insert = hashmap_insert;
    map->clear = hashmap_clear;
    map->exists = hashmap_value_exists;
    map->get_at = hashmap_get_at;
}

void hashmap_insert(unordered_hashmap* map, const char* key, u64 key_length, void* value, u64 value_size) {
    u32 index = hash_array_ccp_u32(key, map->capacity);
    kv_pair* ptr = map->data;
    ptr += index;
    check_ptr:
    if(ptr->key != NULL) {
        if(*ptr->key != *key) {
            ptr++;
            goto check_ptr;
        }

        if(memcmp(key, ptr->key, key_length) != 0) {
            ptr++;
            goto check_ptr;
        }
        goto set_value;    
    }

    ptr->key = malloc(sizeof(char) * key_length);
    memcpy(ptr->key, key, key_length);

    set_value:
    if(ptr->value != NULL) free(ptr->value);
    ptr->value = malloc(value_size);
    memcpy(ptr->value, value, value_size);

}

void hashmap_clear (unordered_hashmap* map) {

}

b8   hashmap_value_exists(unordered_hashmap* map, const char* key, u64 key_size) {

}

void* hashmap_get_at(unordered_hashmap* map, const char* key, u64 key_size) {

}

void unordered_hashmap_destroy(unordered_hashmap* map) {
    free(map->data);
    map->capacity = 0;
    map->clear = 0;
    map->data = 0;
    map->exists = 0;
    map->get_at = 0;
    map->insert = 0;
}
