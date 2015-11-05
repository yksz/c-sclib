#include "sclib/stack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "sclib/list.h"

struct stack
{
    int capacity;
    List* list;
};

Stack* Stack_new(int capacity)
{
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        return NULL;
    }
    stack->capacity = (capacity > 0) ? capacity : 0;
    stack->list = List_new();
    return stack;
}

void Stack_free(Stack* self)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return;
    }

    free(self->list);
    free(self);
}

int Stack_size(Stack* self)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return 0;
    }

    return List_size(self->list);
}

bool Stack_empty(Stack* self)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return false;
    }

    return List_size(self->list) == 0;
}

bool Stack_push(Stack* self, void* data)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return false;
    }

    if (self->capacity != 0
            && List_size(self->list) >= self->capacity) {
        return false;
    }
    if (List_pushBack(self->list, data) == NULL) {
        return false;
    }
    return true;
}

void* Stack_pop(Stack* self)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return NULL;
    }

    if (Stack_empty(self)) {
        return NULL;
    }
    return List_remove(self->list, List_last(self->list));
}

void* Stack_top(Stack* self)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return NULL;
    }

    if (Stack_empty(self)) {
        return NULL;
    } else {
        return List_last(self->list)->data;
    }
}
