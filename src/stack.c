#include "sclib/stack.h"

#include <stdio.h>
#include <stdlib.h>
#include "sclib/list.h"

struct stack
{
    List* list;
    int capacity;
};

Stack* Stack_new(int capacity)
{
    Stack* stack = (Stack*) calloc(1, sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        exit(EXIT_FAILURE);
    }
    stack->list = List_new();
    stack->capacity = (capacity > 0) ? capacity : 0;
    return stack;
}

void Stack_free(Stack* self)
{
    free(self->list);
    free(self);
}

int Stack_size(Stack* self)
{
    return List_size(self->list);
}

bool Stack_empty(Stack* self)
{
    return List_size(self->list) == 0;
}

bool Stack_push(Stack* self, void* data)
{
    if (self->capacity != 0
            && List_size(self->list) >= self->capacity) {
        return false;
    }
    List_pushBack(self->list, data);
    return true;
}

void* Stack_pop(Stack* self)
{
    if (Stack_empty(self)) {
        return NULL;
    }
    return List_remove(self->list, List_last(self->list));
}

void* Stack_top(Stack* self)
{
    if (Stack_empty(self)) {
        return NULL;
    } else {
        return List_last(self->list)->data;
    }
}
