#include "Dictionary.h"
#include "Node/Node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Recursive algorithm to destroy the nodes in a dictionary - overrides the destructor of a BinarySearchTree
void recursive_dictionary_destroy(Node *cursor);

// Insert adds items to the dictionary - the user does not need to implement Elements themselves.
void insert_dict(Dictionary *dictionary, void *key, unsigned long key_size, void *value, unsigned long value_size);
// Search finds the value for a given key in the Dictionary.
void * search_dict(Dictionary *dictionary, void *key, unsigned long key_size);

Dictionary Dictionary_Create(int (*compare)(void *key_one, void *key_two)) {
    Dictionary dictionary;
    dictionary.binary_search_tree = BinarySearchTree_Create(compare);
    dictionary.keys = LinkedList_Create();
    dictionary.insert = insert_dict;
    dictionary.search = search_dict;
    return dictionary;
}

void Dictionary_Destroy(Dictionary *dictionary)
{
    LinkedList_Destroy(&dictionary->keys);
    recursive_dictionary_destroy(dictionary->binary_search_tree.head);
}

void recursive_dictionary_destroy(Node *cursor)
{
    if (cursor->previous)
    {
        recursive_dictionary_destroy(cursor->previous);
    }
    if (cursor->next)
    {
        recursive_dictionary_destroy(cursor->next);
    }
    KeyValuePair_Destroy((KeyValuePair*)cursor->data);
    free(cursor->data);
    free(cursor);
}

void *search_dict(Dictionary *dictionary, void *key, unsigned long key_size)
{
    int dummy_value = 0;
    KeyValuePair searchable = KeyValuePair_Create(key, key_size, &dummy_value, sizeof(dummy_value));
    // Use the iterate function of the BinarySearchTree to find the desired element.
    void * result = dictionary->binary_search_tree.search(&dictionary->binary_search_tree, &searchable);
    // Return either the value for that key or NULL if not found.
    if (result)
    {
        return ((KeyValuePair*)result)->value;
    }
    else
    {
        return NULL;
    }
}

void insert_dict(Dictionary *dictionary, void *key, unsigned long key_size, void *value, unsigned long value_size)
{
    // Create a new KeyValuePair.
    KeyValuePair kv_pair = KeyValuePair_Create(key, key_size, value, value_size);
    // Insert that KeyValuePair into the tree.
    dictionary->binary_search_tree.insert(&dictionary->binary_search_tree, &kv_pair, sizeof(kv_pair));
    dictionary->keys.insert(&dictionary->keys, dictionary->keys.length, key, key_size);
}

int compare_string_keys(void *kv_one, void *kv_two)
{
    if (strcmp((char *)(((KeyValuePair*)kv_one)->key), (char *)(((KeyValuePair*)kv_two)->key)) > 0)
    {
        return 1;
    }
    else if (strcmp((char *)(((KeyValuePair*)kv_one)->key), (char *)(((KeyValuePair*)kv_two)->key)) < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}