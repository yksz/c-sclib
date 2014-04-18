#include "container/hashmap.h"
#include "minunit.h"
#include <stdio.h>
#include <string.h>

static int test_size()
{
    HashMap* hashmap = HashMap_new_str();
    assertEqual_int(0, HashMap_size(hashmap));

    HashMap_add(hashmap, "a", "1");
    assertEqual_int(1, HashMap_size(hashmap));
    HashMap_remove(hashmap, "a");
    assertEqual_int(0, HashMap_size(hashmap));
    HashMap_free(hashmap);
    return 0;
}

static int test_empty()
{
    HashMap* hashmap = HashMap_new_str();
    assertTrue(HashMap_empty(hashmap));

    HashMap_add(hashmap, "a", "1");
    assertTrue(!HashMap_empty(hashmap));
    HashMap_free(hashmap);
    return 0;
}

static int test_get()
{
    HashMap* hashmap = HashMap_new_str();
    assertEqual_ptr(NULL, HashMap_get(hashmap, "a"));

    HashMap_add(hashmap, "a", "1");
    HashMap_add(hashmap, "b", "2");
    HashMap_add(hashmap, "c", "3");
    assertEqual_str("1", (char*) HashMap_get(hashmap, "a"));
    assertEqual_str("2", (char*) HashMap_get(hashmap, "b"));
    assertEqual_str("3", (char*) HashMap_get(hashmap, "c"));
    HashMap_free(hashmap);
    return 0;
}

static int test_insert()
{
    HashMap* hashmap = HashMap_new_str();
    assertEqual_ptr(NULL, HashMap_get(hashmap, "a"));

    HashMap_add(hashmap, "a", "1");
    assertEqual_int(1, HashMap_size(hashmap));
    assertEqual_str("1", (char*) HashMap_get(hashmap, "a"));

    HashMap_add(hashmap, "b", "2");
    assertEqual_int(2, HashMap_size(hashmap));
    assertEqual_str("2", (char*) HashMap_get(hashmap, "b"));

    HashMap_add(hashmap, "a", "3");
    assertEqual_int(2, HashMap_size(hashmap));
    assertEqual_str("3", (char*) HashMap_get(hashmap, "a"));
    HashMap_free(hashmap);
    return 0;
}

static int test_delete()
{
    HashMap* hashmap = HashMap_new_str();
    assertEqual_ptr(NULL, HashMap_remove(hashmap, "a"));

    HashMap_add(hashmap, "a", "1");
    HashMap_add(hashmap, "b", "2");
    HashMap_add(hashmap, "c", "3");
    assertEqual_str("1", (char*) HashMap_remove(hashmap, "a"));
    assertEqual_int(2, HashMap_size(hashmap));
    assertEqual_str("2", (char*) HashMap_remove(hashmap, "b"));
    assertEqual_int(1, HashMap_size(hashmap));
    assertEqual_str("3", (char*) HashMap_remove(hashmap, "c"));
    assertEqual_int(0, HashMap_size(hashmap));
    assertEqual_ptr(NULL, (char*) HashMap_remove(hashmap, "a"));
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
    assertEqual_int(0, HashMap_size(hashmap));
    assertEqual_ptr(NULL, HashMap_remove(hashmap, "a"));
    HashMap_free(hashmap);
    return 0;
}

static int test_keys()
{
    HashMap* hashmap = HashMap_new_str();
    HashMap_add(hashmap, "a", "1");
    HashMap_add(hashmap, "b", "2");
    HashMap_add(hashmap, "c", "3");
    Array* keys = HashMap_keys(hashmap);
    assertEqual_int(3, Array_size(keys));
    Array_free(keys);
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
    assertEqual_str("1", (char*) HashMap_get(hashmap, &array[0]));
    assertEqual_str("2", (char*) HashMap_get(hashmap, &array[1]));
    assertEqual_str("3", (char*) HashMap_get(hashmap, &array[2]));
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

static void runAllTests()
{
    runTest(test_size);
    runTest(test_empty);
    runTest(test_get);
    runTest(test_insert);
    runTest(test_delete);
    runTest(test_clear);
    runTest(test_keys);
    runTest(test_key_int);
    runTest(test_load);
}

int main()
{
    runAllTests();
    reportTestResult();
    return 0;
}
