#include "sclib/list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct list
{
    Element* first;
    Element* last;
    int size;
};

static Element* element_new(void* data)
{
    Element* elem = (Element*) malloc(sizeof(Element));
    if (elem == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        return NULL;
    }
    elem->data = data;
    elem->next = NULL;
    elem->prev = NULL;
    return elem;
}

List* List_new(void)
{
    List* list = (List*) malloc(sizeof(List));
    if (list == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        return NULL;
    }
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
    return list;
}

void List_free(List* self)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return;
    }

    if (self->size > 0) {
        List_clear(self);
    }
    free(self);
}

int List_size(List* self)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return 0;
    }

    return self->size;
}

bool List_empty(List* self)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return false;
    }

    return self->size == 0;
}

Element* List_first(List* self)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return NULL;
    }

    return self->first;
}

Element* List_last(List* self)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return NULL;
    }

    return self->last;
}

static void list_insertAfter(List* self, Element* elem, Element* at)
{
    elem->prev = at;
    elem->next = at->next;
    if (at->next == NULL) {
        self->last = elem;
    } else {
        at->next->prev = elem;
    }
    at->next = elem;
}

static void list_insertBefore(List* self, Element* elem, Element* at)
{
    elem->prev = at->prev;
    elem->next = at;
    if (at->prev == NULL) {
        self->first = elem;
    } else {
        at->prev->next = elem;
    }
    at->prev = elem;
}

Element* List_insertAfter(List* self, void* data, Element* at)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return NULL;
    }
    if (at == NULL) {
        assert(false && "at must not be null");
        return NULL;
    }

    Element* elem = element_new(data);
    if (elem == NULL) {
        return NULL;
    }
    list_insertAfter(self, elem, at);
    self->size++;
    return elem;
}

Element* List_insertBefore(List* self, void* data, Element* at)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return NULL;
    }
    if (at == NULL) {
        assert(false && "at must not be null");
        return NULL;
    }

    Element* elem = element_new(data);
    if (elem == NULL) {
        return NULL;
    }
    list_insertBefore(self, elem, at);
    self->size++;
    return elem;
}

static void list_pushFront(List* self, Element* elem)
{
    if (self->first == NULL) {
        self->first = elem;
        self->last = elem;
        elem->prev = NULL;
        elem->next = NULL;
    } else {
        list_insertBefore(self, elem, self->first);
    }
}

static void list_pushBack(List* self, Element* elem)
{
    if (self->last == NULL) {
        list_pushFront(self, elem);
    } else {
        list_insertAfter(self, elem, self->last);
    }
}

Element* List_pushFront(List* self, void* data)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return NULL;
    }

    Element* elem = element_new(data);
    if (elem == NULL) {
        return NULL;
    }
    list_pushFront(self, elem);
    self->size++;
    return elem;
}

Element* List_pushBack(List* self, void* data)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return NULL;
    }

    Element* elem = element_new(data);
    if (elem == NULL) {
        return NULL;
    }
    list_pushBack(self, elem);
    self->size++;
    return elem;
}

void* List_remove(List* self, Element* elem)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return NULL;
    }
    if (elem == NULL) {
        assert(false && "elem must not be null");
        return NULL;
    }

    if (elem->prev == NULL) {
        self->first = elem->next;
    } else {
        elem->prev->next = elem->next;
    }
    if (elem->next == NULL) {
        self->last = elem->prev;
    } else {
        elem->next->prev = elem->prev;
    }
    void* data = elem->data;
    free(elem);
    self->size--;
    return data;
}

void List_clear(List* self)
{
    if (self == NULL) {
        assert(false && "self must not be null");
        return;
    }

    Element* next;
    for (Element* e = self->first; e; e = next) {
        next = e->next;
        List_remove(self, e);
    }
}
