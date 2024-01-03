#ifndef ONIKEISO_QUEUE_H
#define ONIKEISO_QUEUE_H

typedef struct Queue {
    void** items;

    int capacity;
    int stored;
} Queue;

void create_queue(Queue* queue, int initial_capacity);

void queue_push(Queue* queue, void* item);

void* queue_pop(Queue* queue);

int queue_empty(Queue* queue);

int queue_size(Queue* queue);

int queue_capacity(Queue* queue);

void free_queue(Queue* queue);

void free_queue_content(Queue* queue);

/*
Queue queue;

create_queue(&queue, 1024);

for(int i = 0; i < 100; ++i) {
    int* item = malloc(sizeof(int));
    *item = i;

    queue_push(&queue, item);
}

while(queue_empty(&queue)) {
    int* item = (int*) queue_pop(&queue);

    printf("%d", *item);
}

free_queue(&queue)
*/

#endif
