#ifndef _DICTIONARY_KEYVALUEPAIR_H_
#define _DICTIONARY_KEYVALUEPAIR_H_

typedef struct KeyValuePair {
    void *key;
    void *value;
} KeyValuePair;

// The constructor for an entry requires the key, value, and sizes of each, allowing any data type to be stored.
KeyValuePair KeyValuePair_Create(void *key, unsigned long key_size, void *value, unsigned long value_size);
void KeyValuePair_Destroy(KeyValuePair *kv_pair);

#endif //_DICTIONARY_KEYVALUEPAIR_H_