#ifndef _QUEUE_H_
#define _QUEUE_H_

#include"LinkedList/LinkedList.h"

typedef struct Queue {
    struct LinkedList list;

    void (*push)(struct Queue *queue, void* data, unsigned long size);
    void*(*peek)(struct Queue *queue);
    void (*pop )(struct Queue *queue);
} Queue;

Queue Queue_Create();
void Queue_Destroy(Queue *queue);

#endif //_QUEUE_H_