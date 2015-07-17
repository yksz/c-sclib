#include "sclib/array.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct array
{
    int size;
    int capacity;
    void** table;
};

static const int kDefaultCapacity = 10;

Array* Array_new(int capacity)
{
    Array* array = (Array*) malloc(sizeof(Array));
    if (array == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        return NULL;
    }
    array->size = 0;
    array->capacity = (capacity > 0) ? capacity : kDefaultCapacity;
    array->table = (void**) malloc(sizeof(void*) * array->capacity);
    if (array->table == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        return NULL;
    }
    return array;
}

void Array_free(Array* self)
{
    free(self->table);
    free(self);
}

int Array_size(Array* self)
{
    return self->size;
}

bool Array_empty(Array* self)
{
    return self->size == 0;
}

void* Array_get(Array* self, int index)
{
    if (index < 0 || index >= self->size) {
        return NULL;
    }
    return self->table[index];
}

static bool array_resize(Array* self)
{
    self->capacity *= 2;
    void** newTable = (void**) realloc(self->table, sizeof(void*) * self->capacity);
    if (newTable == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        return false;
    }
    self->table = newTable;
    return true;
}

bool Array_append(Array* self, void* data)
{
    if (self->size >= self->capacity) {
        if (!array_resize(self)) {
            return false;
        }
    }
    self->table[self->size] = data;
    self->size++;
    return true;
}

void* Array_remove(Array* self, int index)
{
    if (index < 0 || index >= self->size) {
        return NULL;
    }
    self->size--;
    void* data = self->table[index];
    for (int i = index; i < self->size; i++) {
        self->table[i] = self->table[i + 1];
    }
    self->table[self->size] = NULL;
    return data;
}

void Array_clear(Array* self)
{
    for (int i = 0; i < self->size; i++) {
        self->table[i] = NULL;
    }
    self->size = 0;
}
