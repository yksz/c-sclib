#include "sclib/array.h"
#include <stdio.h>
#include "nanounit.h"

static int test_size()
{
    Array* array = Array_new(0);
    nu_assert_eq_int(0, Array_size(array));

    Array_append(array, "first");
    nu_assert_eq_int(1, Array_size(array));
    Array_remove(array, 0);
    nu_assert_eq_int(0, Array_size(array));
    Array_free(array);
    return 0;
}

static int test_empty()
{
    Array* array = Array_new(0);
    nu_assert(Array_empty(array));

    Array_append(array, "first");
    nu_assert(!Array_empty(array));
    Array_free(array);
    return 0;
}

static int test_get()
{
    Array* array = Array_new(0);
    nu_assert_eq_ptr(NULL, Array_get(array, 0));
    nu_assert_eq_ptr(NULL, Array_get(array, 1));
    nu_assert_eq_ptr(NULL, Array_get(array, -1));

    Array_append(array, "first");
    Array_append(array, "second");
    Array_append(array, "third");
    nu_assert_eq_str("first", (char*) Array_get(array, 0));
    nu_assert_eq_str("second", (char*) Array_get(array, 1));
    nu_assert_eq_str("third", (char*) Array_get(array, 2));
    Array_free(array);
    return 0;
}

static int test_append()
{
    Array* array = Array_new(2);

    Array_append(array, "first");
    nu_assert_eq_int(1, Array_size(array));
    nu_assert_eq_str("first", (char*) Array_get(array, 0));

    Array_append(array, "second");
    nu_assert_eq_int(2, Array_size(array));
    nu_assert_eq_str("second", (char*) Array_get(array, 1));

    Array_append(array, "third");
    nu_assert_eq_int(3, Array_size(array));
    nu_assert_eq_str("first", (char*) Array_get(array, 0));
    nu_assert_eq_str("second", (char*) Array_get(array, 1));
    nu_assert_eq_str("third", (char*) Array_get(array, 2));
    nu_assert_eq_ptr(NULL, Array_get(array, 3));
    nu_assert_eq_ptr(NULL, Array_get(array, 4));

    Array_free(array);
    return 0;
}

static int test_remove()
{
    Array* array = Array_new(2);
    nu_assert(!Array_remove(array, 0));
    nu_assert(!Array_remove(array, 1));
    nu_assert(!Array_remove(array, -1));

    Array_append(array, "first");
    Array_append(array, "second");
    Array_append(array, "third");
    nu_assert_eq_str("first", (char*) Array_remove(array, 0));
    nu_assert_eq_int(2, Array_size(array));
    nu_assert_eq_str("second", (char*) Array_remove(array, 0));
    nu_assert_eq_int(1, Array_size(array));
    nu_assert_eq_str("third", (char*) Array_remove(array, 0));
    nu_assert_eq_int(0, Array_size(array));
    nu_assert_eq_ptr(NULL, Array_remove(array, 0));
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
        nu_fail();
    }
    Array_free(array);
    return 0;
}

int main()
{
    nu_run_test(test_size);
    nu_run_test(test_empty);
    nu_run_test(test_get);
    nu_run_test(test_append);
    nu_run_test(test_remove);
    nu_run_test(test_clear);
    nu_report();
    return 0;
}
