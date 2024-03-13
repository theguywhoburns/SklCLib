#ifndef _SKLC_LIB_UTILS_LINKED_LIST_H_
#define _SKLC_LIB_UTILS_LINKED_LIST_H_

#include <sklc_lib/defines.h>

typedef struct linked_list {
    struct Node* Start;
    u64 count;
    void (*AddLast)     (struct linked_list* list, void* value, u64 size);
    void (*AddFirst)    (struct linked_list* list, void* value, u64 size);
    void (*AddLastNode) (struct linked_list* list, struct Node* node, b8 allocate);
    void (*AddFirstNode)(struct linked_list* list, struct Node* node, b8 allocate);
    u64  (*Count)    (struct linked_list* list);
    void (*Clear)    (struct linked_list* list);
    void*(*GetAt)    (struct linked_list* list, u64 id);
    void*(*GetNodeAt)(struct linked_list* list, u64 ud);
} linked_list;

linked_list* linked_list_create();

#endif//_SKLC_LIB_UTILS_LINKED_LIST_H_