#include "container/stack.h"
#include "minunit.h"
#include <stdio.h>

static int test_size()
{
    Stack* stack = Stack_new(0);
    assertEqual_int(0, Stack_size(stack));

    int array[] = {1};
    Stack_push(stack, &array[0]);
    assertEqual_int(1, Stack_size(stack));
    Stack_pop(stack);
    assertEqual_int(0, Stack_size(stack));
    Stack_free(stack);
    return 0;
}

static int test_empty()
{
    Stack* stack = Stack_new(0);
    assertTrue(Stack_empty(stack));

    int array[] = {1};
    Stack_push(stack, &array[0]);
    assertTrue(!Stack_empty(stack));
    Stack_pop(stack);
    assertTrue(Stack_empty(stack));
    Stack_free(stack);
    return 0;
}

static int test_push()
{
    Stack* stack = Stack_new(0);
    int array[] = {1, 2, 3};
    Stack_push(stack, &array[0]);
    Stack_push(stack, &array[1]);
    Stack_push(stack, &array[2]);
    assertEqual_int(3, Stack_size(stack));
    Stack_free(stack);
    return 0;
}

static int test_pop()
{
    Stack* stack = Stack_new(0);
    assertEqual_ptr(NULL, Stack_pop(stack));

    int array[] = {1, 2, 3};
    Stack_push(stack, &array[0]);
    Stack_push(stack, &array[1]);
    Stack_push(stack, &array[2]);
    assertEqual_ptr(&array[2], Stack_pop(stack));
    assertEqual_int(2, Stack_size(stack));
    Stack_free(stack);
    return 0;
}

static int test_capacity()
{
    Stack* stack = Stack_new(2);
    int array[] = {1, 2, 3};
    assertTrue(Stack_push(stack, &array[0]));
    assertTrue(Stack_push(stack, &array[1]));
    assertTrue(!Stack_push(stack, &array[2]));
    Stack_pop(stack);
    assertTrue(Stack_push(stack, &array[2]));
    Stack_free(stack);
    return 0;
}

static int test_top()
{
    Stack* stack = Stack_new(0);
    assertEqual_ptr(NULL, Stack_top(stack));

    int array[] = {1, 2, 3};
    Stack_push(stack, &array[0]);
    Stack_push(stack, &array[1]);
    Stack_push(stack, &array[2]);
    assertEqual_ptr(&array[2], Stack_top(stack));
    assertEqual_int(3, Stack_size(stack));
    Stack_free(stack);
    return 0;
}

static void runAllTests()
{
    runTest(test_size);
    runTest(test_empty);
    runTest(test_push);
    runTest(test_pop);
    runTest(test_capacity);
    runTest(test_top);
}

int main()
{
    runAllTests();
    reportTestResult();
    return 0;
}
