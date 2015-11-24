#include "sclib/stack.h"
#include <stdio.h>
#include "nanounit.h"

static int test_size()
{
    Stack* stack = Stack_new(0);
    nu_assert_eq_int(0, Stack_size(stack));

    int array[] = {1};
    Stack_push(stack, &array[0]);
    nu_assert_eq_int(1, Stack_size(stack));
    Stack_pop(stack);
    nu_assert_eq_int(0, Stack_size(stack));
    Stack_free(stack);
    return 0;
}

static int test_empty()
{
    Stack* stack = Stack_new(0);
    nu_assert(Stack_empty(stack));

    int array[] = {1};
    Stack_push(stack, &array[0]);
    nu_assert(!Stack_empty(stack));
    Stack_pop(stack);
    nu_assert(Stack_empty(stack));
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
    nu_assert_eq_int(3, Stack_size(stack));
    Stack_free(stack);
    return 0;
}

static int test_pop()
{
    Stack* stack = Stack_new(0);
    nu_assert_eq_ptr(NULL, Stack_pop(stack));

    int array[] = {1, 2, 3};
    Stack_push(stack, &array[0]);
    Stack_push(stack, &array[1]);
    Stack_push(stack, &array[2]);
    nu_assert_eq_ptr(&array[2], Stack_pop(stack));
    nu_assert_eq_int(2, Stack_size(stack));
    Stack_free(stack);
    return 0;
}

static int test_capacity()
{
    Stack* stack = Stack_new(2);
    int array[] = {1, 2, 3};
    nu_assert(Stack_push(stack, &array[0]));
    nu_assert(Stack_push(stack, &array[1]));
    nu_assert(!Stack_push(stack, &array[2]));
    Stack_pop(stack);
    nu_assert(Stack_push(stack, &array[2]));
    Stack_free(stack);
    return 0;
}

static int test_top()
{
    Stack* stack = Stack_new(0);
    nu_assert_eq_ptr(NULL, Stack_top(stack));

    int array[] = {1, 2, 3};
    Stack_push(stack, &array[0]);
    Stack_push(stack, &array[1]);
    Stack_push(stack, &array[2]);
    nu_assert_eq_ptr(&array[2], Stack_top(stack));
    nu_assert_eq_int(3, Stack_size(stack));
    Stack_free(stack);
    return 0;
}

int main()
{
    nu_run_test(test_size);
    nu_run_test(test_empty);
    nu_run_test(test_push);
    nu_run_test(test_pop);
    nu_run_test(test_capacity);
    nu_run_test(test_top);
    nu_report();
    return 0;
}
