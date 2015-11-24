#include "sclib/list.h"
#include <stdio.h>
#include "nanounit.h"

#define LEN(array) (sizeof(array)/sizeof(array[0]))

static int test_new()
{
    List* list = List_new();
    nu_assert_eq_ptr(NULL, List_first(list));
    nu_assert_eq_ptr(NULL, List_last(list));
    nu_assert_eq_int(0, List_size(list));
    return 0;
}

static int test_free()
{
    List* list1 = List_new();
    List_free(list1);

    List* list2 = List_new();
    List_pushBack(list2, "first");
    List_pushBack(list2, "second");
    List_pushFront(list2, "zero");
    List_pushBack(list2, "third");
    List_free(list2);
    return 0;
}

static int test_size()
{
    List* list = List_new();
    nu_assert_eq_int(0, List_size(list));

    List_pushBack(list, "first");
    List_pushBack(list, "second");
    List_pushFront(list, "zero");
    List_pushBack(list, "third");
    nu_assert_eq_int(4, List_size(list));
    List_free(list);
    return 0;
}

static int test_empty()
{
    List* list = List_new();
    nu_assert(List_empty(list));

    List_pushBack(list, "first");
    nu_assert(!List_empty(list));
    List_free(list);
    return 0;
}

static int test_iterator()
{
    List* list = List_new();
    for (Element* e = List_first(list); e; e = e->next) {
        nu_fail();
    }
    List_free(list);
    return 0;
}

static int test_pushBack()
{
    char* strs[] = {"first", "second", "third"};
    List* list = List_new();
    for (int i = 0; i < LEN(strs); i++) {
        List_pushBack(list, strs[i]);
    }
    int i = 0;
    for (Element* e = List_first(list); e; e = e->next) {
        nu_assert_eq_str(strs[i], (char*) e->data);
        i++;
    }
    List_free(list);
    return 0;
}

static int test_remove()
{
    List* list = List_new();
    List_pushBack(list, "first");
    List_pushBack(list, "second");
    List_pushFront(list, "zero");
    List_pushBack(list, "third");
    char* data;
    data = List_remove(list, List_first(list));
    nu_assert_eq_str("zero", data);
    data = List_remove(list, List_last(list));
    nu_assert_eq_str("third", data);
    List_free(list);
    return 0;
}

static int test_clear()
{
    List* list = List_new();
    List_pushBack(list, "first");
    List_pushBack(list, "second");
    List_pushFront(list, "zero");
    List_pushBack(list, "third");
    List_clear(list);
    nu_assert_eq_ptr(List_first(list), NULL);
    nu_assert_eq_ptr(List_last(list), NULL);
    nu_assert_eq_int(List_size(list), 0);
    List_free(list);
    return 0;
}

int main()
{
    nu_run_test(test_new);
    nu_run_test(test_free);
    nu_run_test(test_size);
    nu_run_test(test_empty);
    nu_run_test(test_iterator);
    nu_run_test(test_pushBack);
    nu_run_test(test_remove);
    nu_run_test(test_clear);
    nu_report();
    return 0;
}
