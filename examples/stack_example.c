#include "container/stack.h"
#include <stdio.h>

int main()
{
    Stack* stack = Stack_new(0);
    Stack_push(stack, "first");
    Stack_push(stack, "second");
    Stack_push(stack, "third");
    while (!Stack_empty(stack)) {
        printf("data: %s\n", (char*) Stack_pop(stack));
    }
    Stack_free(stack);
    return 0;
}

