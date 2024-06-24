#ifndef _SKLC_LIB_UTILS_LINKED_LIST_H_
#define _SKLC_LIB_UTILS_LINKED_LIST_H_

#include <sklc_lib/defines.h>

typedef struct Node {
    void* value;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* tail;
    uint64_t size;
    void (*value_destructor)(struct LinkedList* list, void* value);
    void*(*value_copy)(struct LinkedList* list, void* value);
    int  (*compare)(struct LinkedList* list, void* a, void* b);
} LinkedList;

LinkedList* LinkedList_Create(
    uint64_t val_size,
    void (*val_dtor)(LinkedList* list, void* node_val), 
    void*(*val_cpy)(LinkedList* list, void* node_val),
    int  (*cmp)(LinkedList* list, void* a, void* b)
);

uint64_t LinkedList_Count(LinkedList* list);
// Will free the allocated linked list
void LinkedList_Destroy(LinkedList* list);
// Will keep the allocated linked list
void LinkedList_Clear(LinkedList* list);

// These consider that the values are already copied
void LinkedList_PushBack(LinkedList* list, void* value);
void LinkedList_PushBackNode(LinkedList* list, Node* node);
void LinkedList_PushFront(LinkedList* list, void* value);
void LinkedList_PushFrontNode(LinkedList* list, Node* node);
void LinkedList_InsertAt(LinkedList* list, void* value, uint64_t id);
void LinkedList_InsertNodeAt(LinkedList* list, Node* node, uint64_t id);

// Will call the value_copy
void LinkedList_PushCopyBack(LinkedList* list, void* value);
void LinkedList_PushCopyBackNode(LinkedList* list, Node* node);
void LinkedList_PushCopyFront(LinkedList* list, void* value);
void LinkedList_PushCopyFrontNode(LinkedList* list, Node* node);
void LinkedList_InsertCopyAt(LinkedList* list, void* value, uint64_t id);
void LinkedList_InsertNodeCopyAt(LinkedList* list, Node* node, uint64_t id);

// Popped value has to be de-allocated by the caller
void* LinkedList_PopBack(LinkedList* list);
void* LinkedList_PopFront(LinkedList* list);

// Get the value
void* LinkedList_GetAt(LinkedList* list, uint64_t id);
Node* LinkedList_GetNodeAt(LinkedList* list, uint64_t id);
void* LinkedList_PopAt(LinkedList* list, uint64_t id);

// Get the value copy
void* LinkedList_GetCopyAt(LinkedList* list, uint64_t id);
Node* LinkedList_GetNodeCopyAt(LinkedList* list, uint64_t id);

// Sorts
void LinkedList_Quicksort(LinkedList* list);

// Default functions
void __linked_list_default_destructor(LinkedList* list, void* value);
void*__linked_list_default_copy(LinkedList* list, void* value);
int __linked_list_default_compare(LinkedList* list, void* a, void* b);

void __linked_list_string_destructor(LinkedList* list, void* value);
void*__linked_list_string_copy(LinkedList* list, void* value);
int __linked_list_string_compare(LinkedList* list, void* a, void* b);

void __linked_list_vector_destructor(LinkedList* list, void* value);
void*__linked_list_vector_copy(LinkedList* list, void* value);
int  __linked_list_vector_compare(LinkedList* list, void* a, void* b);

void __linked_list_tinyvec_destructor(LinkedList* list, void* value);
void*__linked_list_tinyvec_copy(LinkedList* list, void* value);
int  __linked_list_tinyvec_compare(LinkedList* list, void* a, void* b);

// For X-Dimension linked_list
void __linked_list_linked_list_destructor(LinkedList* list, void* value);
void*__linked_list_linked_list_copy(LinkedList* list, void* value);
int  __linked_list_linked_list_compare(LinkedList* list, void* a, void* b);

// Defines
#define LINK_LIST_DEF_DTOR __linked_list_default_destructor
#define LINK_LIST_DEF_CPY  __linked_list_default_copy
#define LINK_LIST_STR_DTOR __linked_list_string_destructor
#define LINK_LIST_STR_CPY  __linked_list_string_copy
#define LINK_LIST_VEC_DTOR __linked_list_vector_destructor
#define LINK_LIST_VEC_CPY  __linked_list_vector_copy
#define LINK_LIST_TINYVEC_DTOR __linked_list_tinyvec_destructor
#define LINK_LIST_TINYVEC_CPY  __linked_list_tinyvec_copy
#define LINK_LIST_LINK_LIST_DTOR __linked_list_linked_list_destructor
#define LINK_LIST_LINK_LIST_CPY  __linked_list_linked_list_copy

#endif//_SKLC_LIB_UTILS_LINKED_LIST_H_