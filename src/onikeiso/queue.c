#include "queue.h"

#include <stdlib.h>
#include <stdbool.h>

void create_queue(Queue* queue, int max_capacity) {
    queue->items = malloc(max_capacity * sizeof(void*));

    queue->stored = 0;
    queue->max_capacity = max_capacity;

    for(int i = 0; i < max_capacity; ++i) {
        queue->items[i] = NULL;
    }
}

void queue_push(Queue* queue, void* item) {
    if(queue->stored + 1 <= queue->max_capacity) {
        queue->items[queue->stored] = item;

        ++queue->stored;
    }
}

void* queue_pop(Queue* queue) {
    if((queue->stored - 1) >= 0) {
        return queue->items[--queue->stored];
    }

    return NULL;
}

int queue_empty(Queue* queue) {
    return queue->stored == 0;
}

int queue_size(Queue* queue) {
    return queue->stored;
}

void free_queue(Queue* queue) {
    free(queue->items);
}
