#include "sclib/hashmap.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    HashMap* hashmap = HashMap_new_str();
    HashMap_add(hashmap, "a", "1");
    HashMap_add(hashmap, "b", "2");
    HashMap_add(hashmap, "c", "3");
    void** keys = HashMap_keys(hashmap);
    for (int i = 0; keys[i] != NULL; i++) {
        char* key = (char*) keys[i];
        char* val = (char*) HashMap_get(hashmap, key);
        printf("key: %s, val: %s\n", key, val);
    }
    free(keys);
    HashMap_free(hashmap);
    return 0;
}
