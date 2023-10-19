#include <stdlib.h>
#include <sklc_lib/str_linked_list.h>

void str_linked_list_create(str_linked_list* list, string str_first_value) {
    node* first = malloc(sizeof(node));
    string set = string_create_str(str_first_value);
    *first = node_create(&set, sizeof(string));
    list->first = first;
    list->last = first;
    list->length = 1;
}

void str_linked_list_destroy(str_linked_list* list) {
    node* prev = list->last;
    list->last = 0;
    while(prev) {
        string* temp = prev->value_ptr;
        string_destroy(temp);
        node* tmp = prev->previous;
        node_destroy(prev);
        free(prev);
        prev = tmp;
    }
    
}

// returns the index, returns -1 if not found
long long str_linked_list_find(str_linked_list* list, string value) {
    node* next = list->first;
    unsigned long long ret_index = 0;
    while (next) {
        string* tmp = next->value_ptr;
        if(string_equals_str_str(*tmp, value)) return ret_index;
        next = next->next;
        ret_index++;
    }
    return -1;
}

// returns the vector of strings
vector str_linked_list_to_vector_string(str_linked_list* list) {
    vector ret = vector_create(string);
    ret.reserve(&ret, list->length);
    node* next;
    while (next) {
        ret.push_back(&ret, next->value_ptr);
        next = next->next;
    }
    return ret;
}

// returns the vector of char*
vector str_linked_list_to_vector_cp(str_linked_list* list) {
    vector ret = vector_create(char*);
    ret.reserve(&ret, list->length);
    node* next;
    while (next) {
        ret.push_back(&ret, string_c_str(*((string*)next->value_ptr)));
        next = next->next;
    }
    return ret;
}

node* str_linked_list_find_node_by_value(str_linked_list* list, string value) {
    node* next = list->first;
    while (next) {
        string* tmp = next->value_ptr;
        if(string_equals_str_str(*tmp, value)) {
            node* ret = malloc(sizeof(node));
            string ret_str = string_create_str(*tmp);
            *ret = node_create(&ret_str, sizeof(string));
        }
        next = next->next;
    }
    return NULL;
}

node* str_linked_list_find_node_by_index(str_linked_list* list, unsigned long long value) {
    node* next = list->first;
    for (unsigned long long i = 0; i < value; i++) {
        next = next->next;
        if(next == NULL) return NULL;
    }
    node* ret = malloc(sizeof(node));
    string ret_str = string_create_str(*((string*)next->value_ptr));
    *ret = node_create(&ret_str, sizeof(string));
    return ret;
}

// The nodes don't have to be allocated, they'll be copied to automatically allocated nodes
void str_linked_list_add_after(str_linked_list* list, node* after, string value) {
    node* next = after->next;

    node* nod = malloc(sizeof(node));
    string ret_str = string_create_str(value);
    *nod = node_create(&ret_str, sizeof(string));
    after->next = nod;
    nod->previous = next;
    nod->next = next;
    next->previous = nod;
    list->length++;
}

// The nodes don't have to be allocated, they'll be copied to automatically allocated nodes
void str_linked_list_add_before(str_linked_list* list, node* before, string value) {
    node* prev = before->previous;

    node* nod = malloc(sizeof(node));
    string ret_str = string_create_str(value);
    *nod = node_create(&ret_str, sizeof(string));
    before->previous = nod;
    nod->previous = prev;
    nod->next = before;
    prev->next = nod;
    list->length++;
}

// The nodes don't have to be allocated, they'll be copied to automatically allocated nodes
void str_linked_list_add_first(str_linked_list* list, string value) {
    node* nod = malloc(sizeof(node));
    string ret_str = string_create_str(value);
    *nod = node_create(&ret_str, sizeof(string));
    nod->next = list->first->next;
    list->first->next->previous = nod;
    list->first = nod;
    list->length++;
}

// The nodes don't have to be allocated, they'll be copied to automatically allocated nodes
void str_linked_list_add_last(str_linked_list* list, string value) {
    node* nod = malloc(sizeof(node));
    string ret_str = string_create_str(value);
    *nod = node_create(&ret_str, sizeof(string));
    list->last->next = nod;
    list->last = nod;
    list->length++;
}