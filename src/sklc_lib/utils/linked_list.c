#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sklc_lib/utils/linked_list.h>

void linked_list_add_last(struct linked_list* list, void* value, u64 size);
void linked_list_add_last_node(struct linked_list* list, Node* node);
void linked_list_add_first(struct linked_list* list, void* value, u64 size);
void linked_list_add_first_node(struct linked_list* list, Node* node);
u64  linked_list_count(struct linked_list* list);
void linked_list_clear(struct linked_list* list);
void*linked_list_get_at(struct linked_list* list, u64 id);
Node*linked_list_get_node_at(struct linked_list* list, u64 id);

linked_list* linked_list_create() {
    linked_list* ret = malloc(sizeof(linked_list));
    ret->AddLast = linked_list_add_last;
    ret->AddLastNode = linked_list_add_last_node;
    ret->AddFirst = linked_list_add_first;
    ret->AddFirstNode = linked_list_add_first_node;
    ret->Count = linked_list_count;
    ret->Clear = linked_list_clear;
    ret->GetAt = linked_list_get_at;
    ret->GetNodeAt = linked_list_get_node_at;
    ret->count = 0;
    ret->First = NULL;
    ret->Last = NULL;
    return ret;
}

Node* linked_list_destroy(linked_list* list, b8 destroy_nodes) {
    /*
        printf("Function Name: %s\n", __func__);
        printf("List Address: %p\n", (void*)list);
        printf("List first_address: %p\n", (void*)list->First);
        printf("List first->next_address: %p\n", (void*)list->First != NULL ? list->First->next : NULL);
    */

    Node* current = list->First;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        if (destroy_nodes) {
            // Destroy the node value if needed
            if (current->value != NULL) {
                free(current->value);
            }
            free(current);
        }
        current = next;
    }

    free(list);
    return NULL;
}



void linked_list_add_last(struct linked_list* list, void* value, u64 size) {
    /*
        printf("Function Name: %s\n", __func__);
        printf("List Address: %p\n", (void*)list);
    */

    // Existing function code
    Node* to_add = Node_Create(value, size, NULL);
    //printf("Node Address: %p, Next Address: 0x%lx\n", (void*)to_add, (unsigned long)to_add->next);
    linked_list_add_last_node(list, to_add);
}

void linked_list_add_last_node(struct linked_list* list, Node* node) {
    /*
        printf("Function Name: %s\n", __func__);
        printf("List Address: %p\n", (void*)list);
        printf("Node Address: %p, Next Address: 0x%lx\n", (void*)node, (unsigned long)node->next);
    */

    // Existing function code
    if (list->Last == NULL) {
        list->First = node;
    } else {
        list->Last->next = node;
    }

    list->Last = node;
    list->count++;
}

void linked_list_add_first(struct linked_list* list, void* value, u64 size) {
    /*
        printf("Function Name: %s\n", __func__);
        printf("List Address: %p\n", (void*)list);
    */

    // Existing function code
    Node* new_node = Node_Create(value, size, NULL);
    //printf("Node Address: %p, Next Address: 0x%lx\n", (void*)new_node, (unsigned long)new_node->next);
    linked_list_add_first_node(list, new_node);
}

void linked_list_add_first_node(struct linked_list* list, Node* node) {
    /*
        printf("Function Name: %s\n", __func__);
        printf("List Address: %p\n", (void*)list);
        printf("Node Address: %p, Next Address: 0x%lx\n", (void*)node, (unsigned long)node->next);
    */

    // Existing function code
    Node* not_first_anymore = list->First;
    list->First = node;
    list->First->next = not_first_anymore;
    list->count++;
}

u64 linked_list_count(struct linked_list* list) {
    /*
        printf("Function Name: %s\n", __func__);
        printf("List Address: %p\n", (void*)list);
    */

    // Existing function code
    Node* node = list->First;
    u64 count = 0;
    
    while (node != NULL) {
        //printf("Node Address: %p, Next Address: 0x%lx\n", (void*)node, (unsigned long)node->next);
        count++;
        node = node->next;
    }
    
    return count;
}

void linked_list_clear(struct linked_list* list) {
    /*
        printf("Function Name: %s\n", __func__);
        printf("List Address: %p\n", (void*)list);
    */

    // Existing function code
    Node* node = list->First;
    while (node != NULL) {
        Node* next_node = node->next;
        //printf("Node Address to Clear: %p, Next Address: 0x%lx\n", (void*)node, (unsigned long)node->next);
        Node_Destroy(node);
        free(node);
        node = next_node;
    }
    list->First = NULL;
    list->Last = NULL;
    list->count = 0;
}

void* linked_list_get_at(struct linked_list* list, u64 id) {
    /*
        printf("Function Name: %s\n", __func__);
        printf("List Address: %p\n", (void*)list);
    */

    // Existing function code
    Node* node = linked_list_get_node_at(list, id);
    if (node != NULL) {
        return node->value;
    }
    return NULL;
}

Node* linked_list_get_node_at(struct linked_list* list, u64 id) {
    /*
        printf("Function Name: %s\n", __func__);
        printf("List Address: %p\n", (void*)list);
    */

    // Existing function code
    if (id >= list->count) {
        return NULL; // Index out of bounds
    }

    Node* node = list->First;
    u64 current_id = 0;

    while (node != NULL) {
        if (current_id == id) {
            //printf("Node Address at Index %lu: %p, Next Address: 0x%lx\n", id, (void*)node, (unsigned long)node->next);
            return node;
        }
        node = node->next;
        current_id++;
    }

    return NULL; // Node not found
}
