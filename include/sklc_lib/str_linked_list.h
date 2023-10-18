#ifndef _SKLC_LIB_STR_LINKED_LIST_H_
#define _SKLC_LIB_STR_LINKED_LIST_H_

#include <sklc_lib/string.h>

typedef struct str_linked_list {
    struct node* first;
    


} str_linked_list;

void str_linked_list_create(str_linked_list* list);
void str_linked_list_destroy(str_linked_list* list);
void str_linked_list_find(str_linked_list* list, void* value);


/// Yet to implement......

#endif//_SKLC_LIB_STR_LINKED_LIST_H_