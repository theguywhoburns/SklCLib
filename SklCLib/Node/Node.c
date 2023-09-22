#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Node.h"

Node Node_Create(void* data, unsigned long size) {
    if (size < 1)
    {
        // Confirm the size of the data is at least one, otherwise exit with an error message.
        printf("Invalid data size for node...\n");
        exit(1);
    }
    // Create a Node instance to be returned
    struct Node node;
    // Allocate space for the data if it is of a supported type
    node.data = malloc(size);
    memcpy(node.data, data, size);
    // Initialize the pointers.
    node.next = NULL;
    node.previous = NULL;
    return node;
}

Node *Node_Create_Pointer(void *data, unsigned long size) {
    Node *new_node = malloc(sizeof(Node));
    *new_node = Node_Create(data, size);
    return new_node;
}

void Node_Destroy(Node *node) {
    free(node->data);
    free(node);   
}