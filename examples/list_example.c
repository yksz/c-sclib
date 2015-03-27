#include "sclib/list.h"
#include <stdio.h>

int main()
{
    List* list = List_new();
    List_pushBack(list, "first");
    List_pushBack(list, "second");
    List_pushBack(list, "third");
    for (Element* e = List_first(list); e; e = e->next) {
        printf("data: %s\n", (char*) e->data);
    }
    List_free(list);
    return 0;
}
