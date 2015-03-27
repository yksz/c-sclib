#include "sclib/queue.h"

#include <stdio.h>
#include <stdlib.h>
#include "sclib/list.h"

struct queue
{
    int capacity;
    List* list;
};

Queue* Queue_new(int capacity)
{
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    if (queue == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        return NULL;
    }
    queue->capacity = (capacity > 0) ? capacity : 0;
    queue->list = List_new();
    return queue;
}

void Queue_free(Queue* self)
{
    free(self->list);
    free(self);
}

int Queue_size(Queue* self)
{
    return List_size(self->list);
}

bool Queue_empty(Queue* self)
{
    return List_size(self->list) == 0;
}

bool Queue_enqueue(Queue* self, void* data)
{
    if (self->capacity != 0
            && List_size(self->list) >= self->capacity) {
        return false;
    }
    if (List_pushBack(self->list, data) == NULL) {
        return false;
    }
    return true;
}

void* Queue_dequeue(Queue* self)
{
    if (Queue_empty(self)) {
        return NULL;
    }
    return List_remove(self->list, List_first(self->list));
}

void* Queue_front(Queue* self)
{
    if (Queue_empty(self)) {
        return NULL;
    } else {
        return List_first(self->list)->data;
    }
}

void* Queue_back(Queue* self)
{
    if (Queue_empty(self)) {
        return NULL;
    } else {
        return List_last(self->list)->data;
    }
}
