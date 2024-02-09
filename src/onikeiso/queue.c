#include "queue.h"

#include <stdlib.h>
#include <assert.h>

void create_queue(Queue* queue, int initial_capacity) {
    assert(initial_capacity > 0);

    queue->items = calloc(initial_capacity, sizeof(void*));

    queue->stored = 0;
    queue->capacity = initial_capacity;
}

void queue_push(Queue* queue, void* item) {
    if(queue->stored + 1 > queue->capacity) {
        queue->capacity = queue->capacity * 2;

        // Todo check if items is null
        queue->items = realloc(queue->items, queue->capacity * sizeof(void*));
    }

    queue->items[queue->stored] = item;
    ++queue->stored;
}

void* queue_pop(Queue* queue) {
    if(queue->stored == 0) {
        return NULL;
    }

    --queue->stored;
    void* popped_value = queue->items[queue->stored];

    if(queue->stored > 10 && (queue->stored <= queue->capacity / 2)) {
        queue->capacity = queue->capacity / 2;

        // Todo check if items is null
        queue->items = realloc(queue->items, queue->capacity * sizeof(void*));
    }

    return popped_value;
}

int queue_empty(Queue* queue) {
    return queue->stored == 0;
}

int queue_size(Queue* queue) {
    return queue->stored;
}

int queue_capacity(Queue* queue) {
    return queue->capacity;
}

void free_queue(Queue* queue) {
    free(queue->items);
}

void free_queue_content(Queue* queue) {
    for(int i = 0; i < queue->stored; ++i) {
        free(queue->items[i]);
    }
}