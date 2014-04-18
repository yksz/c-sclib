#include "container/hashmap.h"
#include <stdio.h>
#include "container/array.h"

int main()
{
    HashMap* hashmap = HashMap_new_str();
    HashMap_add(hashmap, "a", "1");
    HashMap_add(hashmap, "b", "2");
    HashMap_add(hashmap, "c", "3");
    Array* keys = HashMap_keys(hashmap);
    for (int i = 0; i < Array_size(keys); i++) {
        char* key = (char*) Array_get(keys, i);
        char* val = (char*) HashMap_get(hashmap, key);
        printf("key: %s, val: %s\n", key, val);
    }
    Array_free(keys);
    HashMap_free(hashmap);
    return 0;
}
