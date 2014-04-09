#ifndef SCLIB_ARRAY_H
#define SCLIB_ARRAY_H

#include <stdbool.h>

typedef struct array Array;

Array* Array_new    (int capacity);
void   Array_free   (Array* self);
int    Array_size   (Array* self);
bool   Array_empty  (Array* self);
void*  Array_get    (Array* self, int index);
void   Array_append (Array* self, void* data);
void*  Array_remove (Array* self, int index);
void   Array_clear  (Array* self);

#endif /* SCLIB_ARRAY_H */
