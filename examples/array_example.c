#include "sclib/array.h"
#include <stdio.h>

int main()
{
    Array* array = Array_new(0);
    Array_append(array, "first");
    Array_append(array, "second");
    Array_append(array, "third");
    for (int i = 0; i < Array_size(array); i++) {
        printf("data: %s\n", (char*) Array_get(array, i));
    }
    Array_free(array);
    return 0;
}
