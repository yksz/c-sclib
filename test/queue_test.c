#include "container/queue.h"
#include "minunit.h"
#include <stdio.h>

static int test_size()
{
    Queue* queue = Queue_new(0);
    assertEqual_int(0, Queue_size(queue));

    int array[] = {1};
    Queue_enqueue(queue, &array[0]);
    assertEqual_int(1, Queue_size(queue));
    Queue_dequeue(queue);
    assertEqual_int(0, Queue_size(queue));
    Queue_free(queue);
    return 0;
}

static int test_empty()
{
    Queue* queue = Queue_new(0);
    assertTrue(Queue_empty(queue));

    int array[] = {1};
    Queue_enqueue(queue, &array[0]);
    assertTrue(!Queue_empty(queue));
    Queue_dequeue(queue);
    assertTrue(Queue_empty(queue));
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
    assertEqual_int(3, Queue_size(queue));
    Queue_free(queue);
    return 0;
}

static int test_dequeue()
{
    Queue* queue = Queue_new(0);
    assertEqual_ptr(NULL, Queue_dequeue(queue));

    int array[] = {1, 2, 3};
    Queue_enqueue(queue, &array[0]);
    Queue_enqueue(queue, &array[1]);
    Queue_enqueue(queue, &array[2]);
    assertEqual_ptr(&array[0], Queue_dequeue(queue));
    assertEqual_int(2, Queue_size(queue));
    Queue_free(queue);
    return 0;
}

static int test_capacity()
{
    Queue* queue = Queue_new(2);
    int array[] = {1, 2, 3};
    assertTrue(Queue_enqueue(queue, &array[0]));
    assertTrue(Queue_enqueue(queue, &array[1]));
    assertTrue(!Queue_enqueue(queue, &array[2]));
    Queue_dequeue(queue);
    assertTrue(Queue_enqueue(queue, &array[2]));
    Queue_free(queue);
    return 0;
}

static int test_front_back()
{
    Queue* queue = Queue_new(0);
    assertEqual_ptr(NULL, Queue_front(queue));
    assertEqual_ptr(NULL, Queue_back(queue));

    int array[] = {1, 2, 3};
    Queue_enqueue(queue, &array[0]);
    Queue_enqueue(queue, &array[1]);
    Queue_enqueue(queue, &array[2]);
    assertEqual_ptr(&array[0], Queue_front(queue));
    assertEqual_ptr(&array[2], Queue_back(queue));
    assertEqual_int(3, Queue_size(queue));
    Queue_free(queue);
    return 0;
}

static void runAllTests()
{
    runTest(test_size);
    runTest(test_empty);
    runTest(test_enqueue);
    runTest(test_dequeue);
    runTest(test_capacity);
    runTest(test_front_back);
}

int main()
{
    runAllTests();
    reportTestResult();
    return 0;
}
