#ifndef _SKLC_LIB_UTILS_NODE_H_
#define _SKLC_LIB_UTILS_NODE_H_

#include <sklc_lib/defines.h>

typedef struct Node {
    void* value;
    u64 size;
    struct Node* next;
} Node;

Node* Node_Create (void* data, u64 size, Node* next);
Node* Node_Prepend(Node* head, void* data, u64 size);
void  Node_Destroy(Node* node);

#endif//_SKLC_LIB_UTILS_NODE_H_