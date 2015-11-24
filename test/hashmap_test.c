#include "sclib/hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nanounit.h"

static int test_size()
{
    HashMap* hashmap = HashMap_new_str();
    nu_assert_eq_int(0, HashMap_size(hashmap));

    HashMap_add(hashmap, "a", "1");
    nu_assert_eq_int(1, HashMap_size(hashmap));
    HashMap_remove(hashmap, "a");
    nu_assert_eq_int(0, HashMap_size(hashmap));
    HashMap_free(hashmap);
    return 0;
}

static int test_empty()
{
    HashMap* hashmap = HashMap_new_str();
    nu_assert(HashMap_empty(hashmap));

    HashMap_add(hashmap, "a", "1");
    nu_assert(!HashMap_empty(hashmap));
    HashMap_free(hashmap);
    return 0;
}

static int test_get()
{
    HashMap* hashmap = HashMap_new_str();
    nu_assert_eq_ptr(NULL, HashMap_get(hashmap, "a"));

    HashMap_add(hashmap, "a", "1");
    HashMap_add(hashmap, "b", "2");
    HashMap_add(hashmap, "c", "3");
    nu_assert_eq_str("1", (char*) HashMap_get(hashmap, "a"));
    nu_assert_eq_str("2", (char*) HashMap_get(hashmap, "b"));
    nu_assert_eq_str("3", (char*) HashMap_get(hashmap, "c"));
    HashMap_free(hashmap);
    return 0;
}

static int test_insert()
{
    HashMap* hashmap = HashMap_new_str();
    nu_assert_eq_ptr(NULL, HashMap_get(hashmap, "a"));

    HashMap_add(hashmap, "a", "1");
    nu_assert_eq_int(1, HashMap_size(hashmap));
    nu_assert_eq_str("1", (char*) HashMap_get(hashmap, "a"));

    HashMap_add(hashmap, "b", "2");
    nu_assert_eq_int(2, HashMap_size(hashmap));
    nu_assert_eq_str("2", (char*) HashMap_get(hashmap, "b"));

    HashMap_add(hashmap, "a", "3");
    nu_assert_eq_int(2, HashMap_size(hashmap));
    nu_assert_eq_str("3", (char*) HashMap_get(hashmap, "a"));
    HashMap_free(hashmap);
    return 0;
}

static int test_delete()
{
    HashMap* hashmap = HashMap_new_str();
    nu_assert_eq_ptr(NULL, HashMap_remove(hashmap, "a"));

    HashMap_add(hashmap, "a", "1");
    HashMap_add(hashmap, "b", "2");
    HashMap_add(hashmap, "c", "3");
    nu_assert_eq_str("1", (char*) HashMap_remove(hashmap, "a"));
    nu_assert_eq_int(2, HashMap_size(hashmap));
    nu_assert_eq_str("2", (char*) HashMap_remove(hashmap, "b"));
    nu_assert_eq_int(1, HashMap_size(hashmap));
    nu_assert_eq_str("3", (char*) HashMap_remove(hashmap, "c"));
    nu_assert_eq_int(0, HashMap_size(hashmap));
    nu_assert_eq_ptr(NULL, (char*) HashMap_remove(hashmap, "a"));
    HashMap_free(hashmap);
    return 0;
}

static int test_clear()
{
    HashMap* hashmap = HashMap_new_str();
    HashMap_add(hashmap, "a", "1");
    HashMap_add(hashmap, "b", "2");
    HashMap_add(hashmap, "c", "3");
    HashMap_clear(hashmap);
    nu_assert_eq_int(0, HashMap_size(hashmap));
    nu_assert_eq_ptr(NULL, HashMap_remove(hashmap, "a"));
    HashMap_free(hashmap);
    return 0;
}

static int test_keys()
{
    HashMap* hashmap = HashMap_new_str();
    HashMap_add(hashmap, "a", "1");
    HashMap_add(hashmap, "b", "2");
    HashMap_add(hashmap, "c", "3");
    void** keys = HashMap_keys(hashmap);
    int size = 0;
    for (int i = 0; keys[i] != NULL; i++)
        size++;
    nu_assert_eq_int(3, size);
    free(keys);
    HashMap_free(hashmap);
    return 0;
}

static int test_key_int()
{
    int array[] = {1, 2, 3};
    HashMap* hashmap = HashMap_new_int();
    HashMap_add(hashmap, &array[0], "1");
    HashMap_add(hashmap, &array[1], "2");
    HashMap_add(hashmap, &array[2], "3");
    nu_assert_eq_str("1", (char*) HashMap_get(hashmap, &array[0]));
    nu_assert_eq_str("2", (char*) HashMap_get(hashmap, &array[1]));
    nu_assert_eq_str("3", (char*) HashMap_get(hashmap, &array[2]));
    HashMap_free(hashmap);
    return 0;
}

static int test_load()
{
    HashMap* hashmap = HashMap_new_str();
    HashMap_add(hashmap, "a", "1");
    HashMap_add(hashmap, "b", "2");
    HashMap_add(hashmap, "c", "3");
    HashMap_add(hashmap, "d", "4");
    HashMap_add(hashmap, "e", "5");
    HashMap_add(hashmap, "f", "6");
    HashMap_add(hashmap, "g", "7");
    HashMap_add(hashmap, "h", "8");
    HashMap_add(hashmap, "i", "9");
    HashMap_add(hashmap, "j", "10");
    HashMap_add(hashmap, "k", "11");
    HashMap_add(hashmap, "l", "12");
    HashMap_add(hashmap, "m", "13");
    HashMap_add(hashmap, "n", "14");
    HashMap_add(hashmap, "o", "15");
    HashMap_add(hashmap, "p", "16");
    HashMap_add(hashmap, "q", "17");
    HashMap_add(hashmap, "r", "18");
    HashMap_add(hashmap, "s", "19");
    HashMap_add(hashmap, "t", "20");
    HashMap_add(hashmap, "u", "21");
    HashMap_add(hashmap, "v", "22");
    HashMap_add(hashmap, "w", "23");
    HashMap_add(hashmap, "x", "24");
    HashMap_add(hashmap, "y", "25");
    HashMap_add(hashmap, "z", "26");
    HashMap_print_strstr(hashmap);
    HashMap_free(hashmap);
    return 0;
}

int main()
{
    nu_run_test(test_size);
    nu_run_test(test_empty);
    nu_run_test(test_get);
    nu_run_test(test_insert);
    nu_run_test(test_delete);
    nu_run_test(test_clear);
    nu_run_test(test_keys);
    nu_run_test(test_key_int);
    nu_run_test(test_load);
    nu_report();
    return 0;
}
