#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

typedef struct LinkedList {
    struct Node *head;
    int length;

    void (*insert)  (struct LinkedList *linked_list, unsigned int index, void *data, 
        unsigned long size);
    void (*remove)  (struct LinkedList *linked_list, unsigned int index);
    void*(*retrieve)(struct LinkedList *linked_list, unsigned int index);  
    void (*sort)(    struct LinkedList *linked_list, int (*compare)(void *a, void *b));
    short (*search)( struct LinkedList *linked_list, void *query, int (*compare)(void *a, void *b));

} LinkedList;

LinkedList LinkedList_Create();
void LinkedList_Destroy(LinkedList *linked_list);

#endif //_LINKED_LIST_H_