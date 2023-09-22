#include "Queue.h"

void push(struct Queue *queue, void *data, unsigned long size);
void *peek(struct Queue *queue);
void pop (struct Queue *queue);

Queue Queue_Create() {
    struct Queue queue;
    queue.list = LinkedList_Create();
    
    queue.push = push;
    queue.peek = peek;
    queue.pop = pop;
    
    return queue;
}

Queue Queue_Create_Ptr() {
    Queue queue;
    queue.list = LinkedList_Create();
    
    queue.push = push;
    queue.peek = peek;
    queue.pop = pop;
    
    return queue;
}

void Queue_Destroy(Queue *queue) {
    LinkedList_Destroy(&queue->list);
}

void push(struct Queue *queue, void *data, unsigned long size)
{
    queue->list.insert(&queue->list, queue->list.length, data, size);
}

void *peek(struct Queue *queue)
{
    void *data = queue->list.retrieve(&queue->list, 0);
    return data;
}

void pop(struct Queue *queue)
{
    queue->list.remove(&queue->list, 0);
}