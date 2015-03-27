#include "sclib/array.h"
#include "minunit.h"
#include <stdio.h>

static int test_size()
{
    Array* array = Array_new(0);
    assertEqual_int(0, Array_size(array));

    Array_append(array, "first");
    assertEqual_int(1, Array_size(array));
    Array_remove(array, 0);
    assertEqual_int(0, Array_size(array));
    Array_free(array);
    return 0;
}

static int test_empty()
{
    Array* array = Array_new(0);
    assertTrue(Array_empty(array));

    Array_append(array, "first");
    assertTrue(!Array_empty(array));
    Array_free(array);
    return 0;
}

static int test_get()
{
    Array* array = Array_new(0);
    assertEqual_ptr(NULL, Array_get(array, 0));
    assertEqual_ptr(NULL, Array_get(array, 1));
    assertEqual_ptr(NULL, Array_get(array, -1));

    Array_append(array, "first");
    Array_append(array, "second");
    Array_append(array, "third");
    assertEqual_str("first", (char*) Array_get(array, 0));
    assertEqual_str("second", (char*) Array_get(array, 1));
    assertEqual_str("third", (char*) Array_get(array, 2));
    Array_free(array);
    return 0;
}

static int test_append()
{
    Array* array = Array_new(2);

    Array_append(array, "first");
    assertEqual_int(1, Array_size(array));
    assertEqual_str("first", (char*) Array_get(array, 0));

    Array_append(array, "second");
    assertEqual_int(2, Array_size(array));
    assertEqual_str("second", (char*) Array_get(array, 1));

    Array_append(array, "third");
    assertEqual_int(3, Array_size(array));
    assertEqual_str("first", (char*) Array_get(array, 0));
    assertEqual_str("second", (char*) Array_get(array, 1));
    assertEqual_str("third", (char*) Array_get(array, 2));
    assertEqual_ptr(NULL, Array_get(array, 3));
    assertEqual_ptr(NULL, Array_get(array, 4));

    Array_free(array);
    return 0;
}

static int test_remove()
{
    Array* array = Array_new(2);
    assertTrue(!Array_remove(array, 0));
    assertTrue(!Array_remove(array, 1));
    assertTrue(!Array_remove(array, -1));

    Array_append(array, "first");
    Array_append(array, "second");
    Array_append(array, "third");
    assertEqual_str("first", (char*) Array_remove(array, 0));
    assertEqual_int(2, Array_size(array));
    assertEqual_str("second", (char*) Array_remove(array, 0));
    assertEqual_int(1, Array_size(array));
    assertEqual_str("third", (char*) Array_remove(array, 0));
    assertEqual_int(0, Array_size(array));
    assertEqual_ptr(NULL, Array_remove(array, 0));
    Array_free(array);
    return 0;
}

static int test_clear()
{
    Array* array = Array_new(0);
    Array_append(array, "first");
    Array_append(array, "second");
    Array_append(array, "third");
    Array_clear(array);
    for (int i = 0; i < Array_size(array); i++) {
        fail();
    }
    Array_free(array);
    return 0;
}

static void runAllTests()
{
    runTest(test_size);
    runTest(test_empty);
    runTest(test_get);
    runTest(test_append);
    runTest(test_remove);
    runTest(test_clear);
}

int main()
{
    runAllTests();
    reportTestResult();
    return 0;
}
