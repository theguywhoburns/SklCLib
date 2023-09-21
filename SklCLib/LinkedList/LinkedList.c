#include "LinkedList.h"
#include "Node/Node.h"

Node *iterate(struct LinkedList *linked_list, unsigned int index);
void insert_node(struct LinkedList *linked_list, unsigned int index, void *data, unsigned long size);

void remove_node(struct LinkedList *linked_list, unsigned int index);
void *retrieve_data(struct LinkedList *linked_list, unsigned int index);

void bubble_sort(struct LinkedList *linked_list, int (*compare)(void *a, void *b));
short binary_search(struct LinkedList *linked_list, void *query, int (*compare)(void *a, void *b));


LinkedList LinkedList_Create() {
    LinkedList new_list;
    new_list.head = ((void*)0);
    new_list.length = 0;

    new_list.insert =   insert_node;
    new_list.remove =   remove_node;
    new_list.retrieve = retrieve_data;
    new_list.sort =     bubble_sort;
    new_list.search =   binary_search;

    return new_list;
}

void LinkedList_destroy(LinkedList *linked_list) {
    for(unsigned int i = 0; i < linked_list->length; i++) {
        linked_list->remove(linked_list, 0);
    }
}

void destroy_node(Node *node_to_destroy) {
    Node_Destroy(node_to_destroy);
}

Node *iterate(struct LinkedList *linked_list, unsigned int index) {
    if(index >= linked_list->length)
        return ((void*)0);
    
    Node *cursor = linked_list->head;
    for(unsigned int i = 0; i < index; i++) {
        cursor = cursor->next;
    }
    return cursor;
}

void insert_node(struct LinkedList *linked_list, unsigned int index, void *data, unsigned long size) {
    Node *node_to_insert = Node_Create_Pointer(data, size);

    if(index == 0) {
        Node *cursor = iterate(linked_list, index - 1);
        node_to_insert->next = cursor->next;
        linked_list->head = node_to_insert;
    } else {
        Node *cursor = iterate(linked_list, index - 1);
        node_to_insert->next = cursor->next;
        cursor->next = node_to_insert;
    }

    linked_list->length += 1;
}

void remove_node(struct LinkedList *linked_list, unsigned int index) {
    if (index == 0)
    {
        Node *node_to_remove = linked_list->head;
        if (node_to_remove)
        {
            linked_list->head = node_to_remove->next;
            destroy_node(node_to_remove);
        }
    }
    else
    {
        Node *cursor = iterate(linked_list, index - 1);
        Node *node_to_remove = cursor->next;
        cursor->next = node_to_remove->next;
        destroy_node(node_to_remove);
    }
    linked_list->length -= 1;
}

void *retrieve_data(struct LinkedList *linked_list, unsigned int index) {
    Node *cursor = iterate(linked_list, index);
    if (cursor)
    {
        return cursor->data;
    }
    else
    {
        return ((void*)0);
    }
}

void bubble_sort(struct LinkedList *linked_list, int (*compare)(void *a, void *b))
{
    for (Node *i = linked_list->retrieve(linked_list, 0); i; i = i->next)
    {
        for (Node *n = i->next; n; n = n->next)
        {
            if (compare(i->data, n->data) > 0)
            {
               // Swap them.
                void *temporary = n->data;
                n->data = i->data;
                i->data = temporary;
            }
        }
    }
}

short binary_search(struct LinkedList *linked_list, void *query, int (*compare)(void *a, void *b))
{
    int position = linked_list->length/2;
    int min_checked = 0;
    int max_checked = linked_list->length;
    while (max_checked > min_checked)
    {
        void *data = linked_list->retrieve(linked_list, position);
        if (compare(data, query) == 1)
        {
            max_checked = position;
            if (position != (min_checked + position) / 2)
            {
                position = (min_checked + position) / 2;
            }
            else
            {
                break;
            }
        }
        else if (compare(data, query) == -1)
        {
            min_checked = position;
            if (position != (max_checked + position) / 2)
            {
                position = (max_checked + position) / 2;
            }
            else
            {
                break;
            }
        }
        else
        {
            return 1;
        }
    }
    return 0;
}