#include <stdlib.h>
#include <stdio.h>
#include <sklc_lib/utils/string.h>
#include <sklc_lib/utils/vector.h>
#include <sklc_lib/utils/linked_list.h>

int main() {
    // Create a linked list for strings
    linked_list* string_list = linked_list_create();
    
    // Test adding strings to the linked list
    string str1 = string_create_ccp("Hello", 5);
    string_list->AddLast(string_list, &str1, sizeof(string));
    
    string str2 = string_create_ccp("World", 5);
    string_list->AddLast(string_list, &str2, sizeof(string));
    
    // Print the contents of the string list
    Node* current_str = string_list->First;
    while (current_str != NULL) {
        if (current_str->value != NULL) {
            string* str = (string*)current_str->value;
            printf("String: %s\n", string_c_str(*str));
        }
        current_str = current_str->next;
    }
    
    // Free the data in each node of the string list
    Node* current_str_node = string_list->First;
    Node* next_str = NULL;
    while (current_str_node != NULL) {
        next_str = current_str_node->next;
        string_destroy((string*)current_str_node->value);
        free(current_str_node);
        current_str_node = next_str;
    }
    
    // Destroy the string list
    linked_list_destroy(string_list, false);
    
    // Create a linked list for vectors
    linked_list* vector_list = linked_list_create();
    
    // Test adding vectors to the linked list
    vector* vec1 = vector_create_ptr(int);
    int val1 = 1;
    vec1->push_back(vec1, &val1);
    int val2 = 2;
    vec1->push_back(vec1, &val2);
    string_list->AddLast(vector_list, vec1, sizeof(vector));
    
    vector* vec2 = vector_create_ptr(int);
    int val3 = 3;
    vec2->push_back(vec2, &val3);
    int val4 = 4;
    vec2->push_back(vec2, &val4);
    string_list->AddLast(vector_list, vec2, sizeof(vector));
    
    // Print the contents of the vector list
    Node* current_vec = vector_list->First;
    while (current_vec != NULL) {
        if (current_vec->value != NULL) {
            vector* vec = (vector*)current_vec->value;
            printf("Vector: ");
            for (size_t i = 0; i < vec->length; i++) {
                printf("%d\n", *(int*)vec->get_at(vec, i));
            }
            printf("\n");
        }
        current_vec = current_vec->next;
    }
    
    // Free the data in each node of the vector list
    Node* current_vec_node = vector_list->First;
    Node* next_vec = NULL;
    while (current_vec_node != NULL) {
        next_vec = current_vec_node->next;
        vector_destroy((vector*)current_vec_node->value);
        free(current_vec_node);
        current_vec_node = next_vec;
    }
    
    // Destroy the vector list
    linked_list_destroy(vector_list, false);
    
    return 0;
}
