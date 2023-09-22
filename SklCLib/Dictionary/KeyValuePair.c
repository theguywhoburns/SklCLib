#include "KeyValuePair.h"

#include <stdlib.h>
#include <string.h>
KeyValuePair KeyValuePair_Create(void *key, unsigned long key_size, void *value, unsigned long value_size) {
    KeyValuePair kv_pair;
    
    kv_pair.key = malloc(key_size);
    kv_pair.value = malloc(value_size);

    memcpy(kv_pair.key, key, key_size);
    memcpy(kv_pair.value, value, value_size);
    return kv_pair;
}

void KeyValuePair_Destroy(KeyValuePair *kv_pair) {
    free(kv_pair->key);
    free(kv_pair->value);
    free(kv_pair);
}