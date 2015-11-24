#include "sclib/queue.h"
#include <stdio.h>
#include "nanounit.h"

static int test_size()
{
    Queue* queue = Queue_new(0);
    nu_assert_eq_int(0, Queue_size(queue));

    int array[] = {1};
    Queue_enqueue(queue, &array[0]);
    nu_assert_eq_int(1, Queue_size(queue));
    Queue_dequeue(queue);
    nu_assert_eq_int(0, Queue_size(queue));
    Queue_free(queue);
    return 0;
}

static int test_empty()
{
    Queue* queue = Queue_new(0);
    nu_assert(Queue_empty(queue));

    int array[] = {1};
    Queue_enqueue(queue, &array[0]);
    nu_assert(!Queue_empty(queue));
    Queue_dequeue(queue);
    nu_assert(Queue_empty(queue));
    Queue_free(queue);
    return 0;
}

static int test_enqueue()
{
    Queue* queue = Queue_new(0);
    int array[] = {1, 2, 3};
    Queue_enqueue(queue, &array[0]);
    Queue_enqueue(queue, &array[1]);
    Queue_enqueue(queue, &array[2]);
    nu_assert_eq_int(3, Queue_size(queue));
    Queue_free(queue);
    return 0;
}

static int test_dequeue()
{
    Queue* queue = Queue_new(0);
    nu_assert_eq_ptr(NULL, Queue_dequeue(queue));

    int array[] = {1, 2, 3};
    Queue_enqueue(queue, &array[0]);
    Queue_enqueue(queue, &array[1]);
    Queue_enqueue(queue, &array[2]);
    nu_assert_eq_ptr(&array[0], Queue_dequeue(queue));
    nu_assert_eq_int(2, Queue_size(queue));
    Queue_free(queue);
    return 0;
}

static int test_capacity()
{
    Queue* queue = Queue_new(2);
    int array[] = {1, 2, 3};
    nu_assert(Queue_enqueue(queue, &array[0]));
    nu_assert(Queue_enqueue(queue, &array[1]));
    nu_assert(!Queue_enqueue(queue, &array[2]));
    Queue_dequeue(queue);
    nu_assert(Queue_enqueue(queue, &array[2]));
    Queue_free(queue);
    return 0;
}

static int test_front_back()
{
    Queue* queue = Queue_new(0);
    nu_assert_eq_ptr(NULL, Queue_front(queue));
    nu_assert_eq_ptr(NULL, Queue_back(queue));

    int array[] = {1, 2, 3};
    Queue_enqueue(queue, &array[0]);
    Queue_enqueue(queue, &array[1]);
    Queue_enqueue(queue, &array[2]);
    nu_assert_eq_ptr(&array[0], Queue_front(queue));
    nu_assert_eq_ptr(&array[2], Queue_back(queue));
    nu_assert_eq_int(3, Queue_size(queue));
    Queue_free(queue);
    return 0;
}

int main()
{
    nu_run_test(test_size);
    nu_run_test(test_empty);
    nu_run_test(test_enqueue);
    nu_run_test(test_dequeue);
    nu_run_test(test_capacity);
    nu_run_test(test_front_back);
    nu_report();
    return 0;
}
