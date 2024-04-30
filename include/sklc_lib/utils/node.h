#ifndef _SKLC_LIB_UTILS_NODE_H_
#define _SKLC_LIB_UTILS_NODE_H_

#include <sklc_lib/defines.h>

typedef struct Node {
    void* value;
    uint64_t size;
    struct Node* next;
} Node;

Node* Node_Create (void* data, uint64_t size, Node* next);
Node* Node_Prepend(Node* head, void* data, uint64_t size);
void  Node_Destroy(Node* node);

#endif//_SKLC_LIB_UTILS_NODE_H_