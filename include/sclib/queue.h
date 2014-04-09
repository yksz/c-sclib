#ifndef SCLIB_QUEUE_H
#define SCLIB_QUEUE_H

#include <stdbool.h>

typedef struct queue Queue;

Queue* Queue_new     (int capacity);
void   Queue_free    (Queue* self);
int    Queue_size    (Queue* self);
bool   Queue_empty   (Queue* self);
bool   Queue_enqueue (Queue* self, void* data);
void*  Queue_dequeue (Queue* self);
void*  Queue_front   (Queue* self);
void*  Queue_back    (Queue* self);

#endif /* SCLIB_QUEUE_H */
