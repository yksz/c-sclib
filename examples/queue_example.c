#include "container/queue.h"
#include <stdio.h>

int main()
{
    Queue* queue = Queue_new(0);
    Queue_enqueue(queue, "first");
    Queue_enqueue(queue, "second");
    Queue_enqueue(queue, "third");
    while (!Queue_empty(queue)) {
        printf("data: %s\n", (char*) Queue_dequeue(queue));
    }
    Queue_free(queue);
    return 0;
}
