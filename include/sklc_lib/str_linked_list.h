#ifndef _SKLC_LIB_STR_LINKED_LIST_H_
#define _SKLC_LIB_STR_LINKED_LIST_H_

#include <sklc_lib/node.h>
#include <sklc_lib/vector.h>
#include <sklc_lib/string.h>

typedef struct str_linked_list {
    node* first;
    node* last;

    unsigned long long length;
} str_linked_list;

void str_linked_list_create(str_linked_list* list, string str_first_value);
void str_linked_list_destroy(str_linked_list* list);

// returns the index
unsigned long long str_linked_list_find(str_linked_list* list, string value);

// returns the vector of strings
vector str_linked_list_to_vector_string(str_linked_list* list);

// returns the vector of char*
vector str_linked_list_to_vector_cp(str_linked_list* list);

// If the list is destroyed the node will not be destroyed, so it's value would be kept...
// but try not to use them add_before and add_after, ok?
node* str_linked_list_find_node_by_value(str_linked_list* list, string value);
node* str_linked_list_find_node_by_index(str_linked_list* list, unsigned long long value);

// The nodes don't have to be allocated, they'll be copied to automatically allocated nodes
void str_linked_list_add_after(str_linked_list* list, node* after, string value);

// The nodes don't have to be allocated, they'll be copied to automatically allocated nodes
void str_linked_list_add_before(str_linked_list* list, node* before, string value);

// The nodes don't have to be allocated, they'll be copied to automatically allocated nodes
void str_linked_list_add_first(str_linked_list* list, string value);

// The nodes don't have to be allocated, they'll be copied to automatically allocated nodes
void str_linked_list_add_last(str_linked_list* list, string value);




/// Yet to implement......

#endif//_SKLC_LIB_STR_LINKED_LIST_H_