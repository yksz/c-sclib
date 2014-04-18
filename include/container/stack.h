#ifndef CONTAINER_STACK_H
#define CONTAINER_STACK_H

#include <stdbool.h>

typedef struct stack Stack;

Stack* Stack_new   (int capacity);
void   Stack_free  (Stack* self);
int    Stack_size  (Stack* self);
bool   Stack_empty (Stack* self);
bool   Stack_push  (Stack* self, void* data);
void*  Stack_pop   (Stack* self);
void*  Stack_top   (Stack* self);

#endif /* CONTAINER_STACK_H */
