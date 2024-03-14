#ifndef _SKLC_LIB_UTILS_LINKED_LIST_H_
#define _SKLC_LIB_UTILS_LINKED_LIST_H_

#include <sklc_lib/defines.h>
#include <sklc_lib/utils/node.h>

typedef struct linked_list {
    struct Node* First;
    struct Node* Last;
    u64 count;
    void (*AddLast)     (struct linked_list* list, void* value, u64 size);
    void (*AddFirst)    (struct linked_list* list, void* value, u64 size);
    void (*AddLastNode) (struct linked_list* list, struct Node* node);
    void (*AddFirstNode)(struct linked_list* list, struct Node* node);
    u64  (*Count)    (struct linked_list* list);
    //use only if you dont have manually allocated variables in nodes
    void (*Clear)    (struct linked_list* list);
    void*(*GetAt)    (struct linked_list* list, u64 id);
    struct Node*(*GetNodeAt)(struct linked_list* list, u64 id);
} linked_list;

linked_list* linked_list_create();
//if the node has an allocated variable in it, you have to deallocate it yoourself
Node* linked_list_destroy(linked_list* list, b8 destroy_nodes);

#endif//_SKLC_LIB_UTILS_LINKED_LIST_H_