#include <sklc_lib/utils/LinkedList.h>

#include <sklc_lib/utils/string.h>
#include <sklc_lib/utils/vector.h>
#include <sklc_lib/utils/tinyvec.h>

#include <stdlib.h>
#include <string.h>

// Sorts

static void __ll__quicksort(LinkedList* list, Node* left, Node* right);

void LinkedList_Quicksort(LinkedList* list) {
    if(list->head == NULL || list->head->next == NULL) return;
    __ll__quicksort(list, list->head, list->tail);
}

static void __ll__quicksort(LinkedList* list, Node* left, Node* right) {
    if(left == right || left->next == right) return;
    Node* pivot = left;
    Node* curr = left->next;
    while(curr != right->next) {
        if(list->compare(list, curr->value, pivot->value) < 0) {
            Node* tmp = curr->next;
            curr->next = pivot->next;
            pivot->next = curr;
            pivot = curr;
            curr = tmp;
        } else {
            curr = curr->next;
        }
    }
    right->next = pivot->next;
    pivot->next = left;
    __ll__quicksort(list, left, pivot);
    __ll__quicksort(list, pivot->next, right);
}

LinkedList* LinkedList_Create(
    uint64_t val_size,
    void (*val_dtor)(LinkedList* list, void* node_val), 
    void*(*val_cpy)(LinkedList* list, void* node_val),
    int  (*cmp)(LinkedList* list, void* a, void* b)
) {
    LinkedList* list = malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = val_size;
    list->value_destructor = val_dtor;
    list->value_copy = val_cpy;
    list->compare = cmp;
    return list;
}

uint64_t LinkedList_Count(LinkedList* list) {
    Node* cursor = list->head;
    uint64_t count = 0;
    while (cursor != NULL) {
        count++;
        cursor = cursor->next;
    }
    return count;
}

void LinkedList_Destroy(LinkedList* list) {
    Node* cursor = list->head;
    while (cursor != NULL) {
        Node* next = cursor->next;
        if (list->value_destructor) {
            list->value_destructor(list, cursor->value);
        }
        free(cursor);
        cursor = next;
    }
    free(list);
}

void LinkedList_Clear(LinkedList* list) {
    Node* cursor = list->head;
    while (cursor != NULL) {
        Node* next = cursor->next;
        if (list->value_destructor) {
            list->value_destructor(list, cursor->value);
        }
        free(cursor);
        cursor = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

// These consider that the values are already copied
void LinkedList_PushBack(LinkedList* list, void* value) {
    Node* last = list->tail;
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    if (last == NULL) {
        list->head = node;
    } else {
        last->next = node;
    }
    list->tail = node;
    list->size++;
}

void LinkedList_PushBackNode(LinkedList* list, Node* node) {
    Node* last = list->tail;
    node->next = NULL;
    if (last == NULL) {
        list->head = node;
    } else {
        last->next = node;
    }
    list->tail = node;
    list->size++;
}

void LinkedList_PushFront(LinkedList* list, void* value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = list->head;
    list->head = node;
    if (list->tail == NULL) {
        list->tail = node;
    }
    list->size++;
}

void LinkedList_PushFrontNode(LinkedList* list, Node* node) {
    node->next = list->head;
    list->head = node;
    if(node->next == NULL) {
        list->tail = node;
    } else {
        Node* last = list->head;
        while (last->next != NULL) {
            last = last->next;
        }
        list->tail = last;
    }
    list->size++;   
}

void LinkedList_InsertAt(LinkedList* list, void* value, uint64_t id) {
    if (id == 0) {
        LinkedList_PushFront(list, value);
        return;
    }
    Node* cursor = list->head;
    for (uint64_t i = 0; i < id - 1; i++) {
        if (cursor == NULL) {
            // Out of bounds
            return;
        }
        cursor = cursor->next;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = cursor->next;
    cursor->next = newNode;
    list->size++;
}

void LinkedList_InsertNodeAt(LinkedList* list, Node* node, uint64_t id) {
    if (id == 0) {
        LinkedList_PushFrontNode(list, node);
        return;
    }
    Node* cursor = list->head;
    for (uint64_t i = 0; i < id - 1; i++) {
        if (cursor == NULL) {
            // Out of bounds
            return;
        }
        cursor = cursor->next;
    }
    node->next = cursor->next;
    cursor->next = node;
    list->size++;
}

// Will call the value_copy
void LinkedList_PushCopyBack(LinkedList* list, void* value) {
    void* copied_value = list->value_copy(list, value);
    Node* copied_node = malloc(sizeof(Node));
    copied_node->value = copied_value;
    LinkedList_PushBackNode(list, copied_node);
}

void LinkedList_PushCopyBackNode(LinkedList* list, Node* node) {
    Node* copied_node = malloc(sizeof(Node));
    copied_node->value = list->value_copy(list, node->value);
    LinkedList_PushBackNode(list, copied_node);
}

void LinkedList_PushCopyFront(LinkedList* list, void* value) {
    void* copied_value = list->value_copy(list, value);
    Node* copied_node = malloc(sizeof(Node));
    copied_node->value = copied_value;
    LinkedList_PushFrontNode(list, copied_value);
}

void LinkedList_PushCopyFrontNode(LinkedList* list, Node* node) {
    Node* copied_node = malloc(sizeof(Node));
    copied_node->value = list->value_copy(list, node->value);
    LinkedList_PushFrontNode(list, copied_node);
}

void LinkedList_InsertCopyAt(LinkedList* list, void* value, uint64_t id) {
    void* copied_value = list->value_copy(list, value);
    Node* copied_node = malloc(sizeof(Node));
    copied_node->value = copied_value;
    LinkedList_InsertNodeAt(list, copied_node, id);
}

void LinkedList_InsertNodeCopyAt(LinkedList* list, Node* node, uint64_t id) {
    Node* copied_node = malloc(sizeof(Node));
    copied_node->value = list->value_copy(list, node->value);
    LinkedList_InsertNodeAt(list, copied_node, id);
}

// Popped value has to be de-allocated by the caller
void* LinkedList_PopBack(LinkedList* list) {
    void* value = NULL;
    if(list->tail != NULL) {
        Node* last = list->tail;
        value = last->value;
        if(list->value_destructor) {
            list->value_destructor(list, last->value);
        }
        free(last);
        list->tail = last->next;
        if(list->tail == NULL) list->head = NULL;
        list->size--;
    }
    return value;
}

void* LinkedList_PopFront(LinkedList* list) {
    void* value = NULL;
    if(list->head != NULL) {
        Node* first = list->head;
        value = first->value;
        if(list->value_destructor) {
            list->value_destructor(list, first->value);
        }
        free(first);
        list->head = first->next;
        if(list->head == NULL) list->tail = NULL;
        list->size--;
    }
    return value;
}

// Get the value
void* LinkedList_GetAt(LinkedList* list, uint64_t id) {
    if(list->head == NULL || id >= list->size) return NULL;
    Node* cursor = list->head;
    for (uint64_t i = 0; i < id; i++) {
        cursor = cursor->next;
    }
    return cursor->value;
}

Node* LinkedList_GetNodeAt(LinkedList* list, uint64_t id) {
    if(list->head == NULL || id >= list->size) return NULL;
    Node* cursor = list->head;
    for (uint64_t i = 0; i < id; i++) {
        cursor = cursor->next;
    }
    return cursor;
}

void* LinkedList_PopAt(LinkedList* list, uint64_t id) {
    void* value = NULL;
    if(list->head == NULL || id >= list->size) return NULL;
    Node* cursor = list->head;
    Node* prev = NULL;
    for (uint64_t i = 0; i < id; i++) {
        prev = cursor;
        cursor = cursor->next;
    }
    value = cursor->value;
    if(list->value_destructor) {
        list->value_destructor(list, cursor->value);
    }
    if(prev != NULL) {
        prev->next = cursor->next;
    } else {
        list->head = cursor->next;
    }
    free(cursor);
    list->size--;
    return value;
}

// Get the value copy
void* LinkedList_GetCopyAt(LinkedList* list, uint64_t id) {
    if(list->head == NULL || id >= list->size) return NULL;
    Node* cursor = list->head;
    for (uint64_t i = 0; i < id; i++) {
        cursor = cursor->next;
    }
    void* value = list->value_copy(list, cursor->value);
    return value;
}

Node* LinkedList_GetNodeCopyAt(LinkedList* list, uint64_t id) {
    if(list->head == NULL || id >= list->size) return NULL;
    Node* cursor = list->head;
    for (uint64_t i = 0; i < id; i++) {
        cursor = cursor->next;
    }
    Node* copy = malloc(sizeof(Node));
    copy->value = list->value_copy(list, cursor->value);
    copy->next = NULL;
    return copy;
}

// Default functions
void __linked_list_default_destructor(LinkedList* list, void* value) {
    (void*)list;
    free(value);
}

void*__linked_list_default_copy(LinkedList* list, void* value) {
    void* copy = malloc(list->size);
    memcpy(copy, value, list->size);
    return copy;
}

int __linked_list_default_compare(LinkedList* list, void* a, void* b) {
    return memcmp(a, b, list->size);
}

void __linked_list_string_destructor(LinkedList* list, void* value) {
    (void*)list;
    StringDestroy(value);
    free(value);
}

void*__linked_list_string_copy(LinkedList* list, void* value) {
    (void*)list;
    string* copy = malloc(sizeof(string));  
    StringDuplicate(copy, *(string*)value);
    return copy;
}

int __linked_list_string_compare(LinkedList* list, void* a, void* b) {
   (void*)list;
   if(StringCompare(*(string*)a, *(string*)b) == 0) return -1;
   return 1;
}

void __linked_list_vector_destructor(LinkedList* list, void* value) {
    (void*)list;
    vector_destroy(value);
    free(value);
}

void*__linked_list_vector_copy(LinkedList* list, void* value) {
    (void*)list;
    vector* copy = malloc(sizeof(vector));  
    *copy = ((vector*)value)->copy(value);
    return copy;
}

int  __linked_list_vector_compare(LinkedList* list, void* a, void* b) {
    (void*)list;
    vector* va = (vector*)a;
    vector* vb = (vector*)b;
    return va->compare(va, vb);
}

void __linked_list_tinyvec_destructor(LinkedList* list, void* value) {
    (void*)list;
    tinyvec_destroy(value);
    free(value);
}

void*__linked_list_tinyvec_copy(LinkedList* list, void* value) {
    (void*)list;
    void* copy = malloc(TINYVEC_STRIDE * TINYVEC_LENGTH);  
    memcpy(copy, value, TINYVEC_STRIDE * TINYVEC_LENGTH);
    return copy;
}

int  __linked_list_tinyvec_compare(LinkedList* list, void* a, void* b) {
    (void*)list;
    return memcmp(a, b, TINYVEC_STRIDE * TINYVEC_LENGTH);
}

// For X-Dimension linked_list
void __linked_list_linked_list_destructor(LinkedList* list, void* value) {
    (void*)list;
    LinkedList_Destroy(value);
    free(value);
}

void*__linked_list_linked_list_copy(LinkedList* list, void* value) {
    LinkedList* copy = LinkedList_Create(list->size, list->value_destructor, list->value_copy, list->compare);
    Node* curr = ((LinkedList*)value)->head;
    while(curr != NULL) {
        LinkedList_PushBack(copy, curr->value);
        curr = curr->next;
    }
    return copy;
}

int  __linked_list_linked_list_compare(LinkedList* list, void* a, void* b) {
    LinkedList* la = (LinkedList*)a;
    LinkedList* lb = (LinkedList*)b;
    uint64_t la_len = LinkedList_Count(la);
    uint64_t lb_len = LinkedList_Count(lb);
    if(la_len != lb_len) return (int)la_len - (int)lb_len;
    Node* na = la->head;
    Node* nb = lb->head;
    while(na != NULL) {
        int cmp = list->compare(list, na->value, nb->value);
        if(cmp != 0) return cmp;
        na = na->next;
        nb = nb->next;
    }
    return 0;
}
