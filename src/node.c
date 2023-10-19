#include <stdlib.h>
#include <string.h>

#include <sklc_lib/node.h>

node node_create(const void* value, unsigned long long size) {
    node ret = {0};
    ret.value_ptr = malloc(size);
    memcpy(ret.value_ptr, value, size);
    return ret;
}

void node_destroy(node* node_to_destroy) {
    free(node_to_destroy->value_ptr);
}

void node_reset(node* node_to_reset, const void* value, unsigned long long size) {
    free(node_to_reset->value_ptr);
    node_to_reset->value_ptr = malloc(size);
    memcpy(node_to_reset->value_ptr, value, size);
}
