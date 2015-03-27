#ifndef SCLIB_HASHMAP_H
#define SCLIB_HASHMAP_H

#include <stdbool.h>
#include <stdint.h>

typedef struct hashmap HashMap;

typedef uint32_t (*HashMap_HashFunc)  (void* key);
typedef bool     (*HashMap_EqualFunc) (void* key1, void* key2);

HashMap* HashMap_new     (HashMap_HashFunc hash, HashMap_EqualFunc equal);
HashMap* HashMap_new_str (void);
HashMap* HashMap_new_int (void);
void     HashMap_free    (HashMap* self);
int      HashMap_size    (HashMap* self);
bool     HashMap_empty   (HashMap* self);
void*    HashMap_get     (HashMap* self, void* key);
void*    HashMap_add     (HashMap* self, void* key, void* value);
void*    HashMap_remove  (HashMap* self, void* key);
void     HashMap_clear   (HashMap* self);
void**   HashMap_keys    (HashMap* self);

// --- for debug

void HashMap_print_strstr (HashMap* self);

#endif /* SCLIB_HASHMAP_H */
