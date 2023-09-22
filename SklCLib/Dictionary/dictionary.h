#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include "LinkedList/LinkedList.h"
#include "BinarySearchTree/BinarySearchTree.h"
#include "KeyValuePair.h"
typedef struct Dictionary {
    BinarySearchTree binary_search_tree;
    LinkedList keys;
    void (*insert)(struct Dictionary *dictionary, void *key, unsigned long key_size, void *value, unsigned long value_size);
    void*(*search)(struct Dictionary *dictionary, void *key, unsigned long key_size);

} Dictionary;

Dictionary Dictionary_Create(int (*compare)(void *entry_one, void *entry_two));
void Dictionary_Destroy(Dictionary *dictionary);

int compare_string_keys(void *entry_one, void *entry_two);

#endif//_DICTIONARY_H_