#include "sclib/array.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct array
{
    void** elems;
    int size;
    int capacity;
};

static const int default_capacity = 10;

Array* Array_new(int capacity)
{
    Array* array = (Array*) calloc(1, sizeof(Array));
    if (array == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        exit(EXIT_FAILURE);
    }
    if (capacity <= 0) {
        capacity = default_capacity;
    }
    array->elems = (void**) calloc(capacity, sizeof(void*));
    if (array->elems == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        exit(EXIT_FAILURE);
    }
    array->size = 0;
    array->capacity = capacity;
    return array;
}

void Array_free(Array* self)
{
    free(self->elems);
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
    return self->elems[index];
}

static void array_resize(Array* self)
{
    self->capacity *= 2;
    void** new_elems = (void**) realloc(self->elems, sizeof(void*) * self->capacity);
    if (new_elems == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        free(self->elems);
        exit(EXIT_FAILURE);
    }
    self->elems = new_elems;
}

void Array_append(Array* self, void* data)
{
    if (self->size >= self->capacity) {
        array_resize(self);
    }
    self->elems[self->size] = data;
    self->size++;
}

void* Array_remove(Array* self, int index)
{
    if (index < 0 || index >= self->size) {
        return NULL;
    }
    self->size--;
    void* data = self->elems[index];
    for (int i = index; i < self->size; i++) {
        self->elems[i] = self->elems[i + 1];
    }
    self->elems[self->size] = NULL;
    return data;
}

void Array_clear(Array* self)
{
    for (int i = 0; i < self->size; i++) {
        self->elems[i] = NULL;
    }
    self->size = 0;
}
