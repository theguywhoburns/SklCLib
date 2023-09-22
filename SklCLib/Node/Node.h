#ifndef  _NODE_H_
#define  _NODE_H_

typedef struct Node {
    void* data;

    struct Node* next;
    struct Node* previous;
} Node;

Node Node_Create(void* data, unsigned long size);
void Node_Destroy(Node *node);

Node *Node_Create_Pointer(void *data, unsigned long size);

#endif /*_NODE_H_*/