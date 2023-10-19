#ifndef _SKLC_LIB_NODE_H_
#define _SKLC_LIB_NODE_H_

typedef struct node {
    struct node* previous;

    struct node* parent;
    struct node* child;
    void* value_ptr;
    
    struct node* next;
} node;

// Creates the node(you have to create a pointer to it(malloc or new) manually)
node node_create(const void* value, unsigned long long size);

// Destroys the specified node (if you have malloced or new'ed it you have to free it manually)
void node_destroy(node* node_to_destroy);

// resets the value inside the node, but keeps the previous, 
//                                                 parent, 
//                                                 child and next nodes
void node_reset(node* node_to_reset, const void* value, unsigned long long size);

#endif//_SKLC_LIB_NODE_H_