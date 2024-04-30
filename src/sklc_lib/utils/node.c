#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sklc_lib/utils/node.h>

Node* Node_Create (void* data, uint64_t size, Node* next) {
    Node* ret = malloc(sizeof(Node));
    assert(ret != NULL);
    ret->size = size;
    ret->value = malloc(ret->size);
    assert(ret->value != NULL);
    memcpy(ret->value, data, ret->size);
    ret->next = next;
    return ret;
}

Node* Node_Prepend(Node* head, void* data, uint64_t size) {
    Node* node = Node_Create(data, size, head);
    head = node;
    return head;
}

void  Node_Destroy(Node* node) {
    assert(node != NULL);
    if(node->value != NULL) free(node->value);
    free(node);
}