#include "sclib/list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct list
{
    Node* first;
    Node* last;
    int size;
};

List* List_new()
{
    List* list = (List*) calloc(1, sizeof(List));
    if (list == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        exit(EXIT_FAILURE);
    }
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
    return list;
}

void List_free(List* self)
{
    if (self->size > 0) {
        List_clear(self);
    }
    free(self);
}

int List_size(List* self)
{
    return self->size;
}

bool List_empty(List* self)
{
    return self->size == 0;
}

Node* List_first(List* self)
{
    return self->first;
}

Node* List_last(List* self)
{
    return self->last;
}

static Node* list_newNode(void* data)
{
    Node* node = (Node*) calloc(1, sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "ERROR: out of memory\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

static void list_insertAfter(List* self, Node* node, Node* at)
{
    node->prev = at;
    node->next = at->next;
    if (at->next == NULL) {
        self->last = node;
    } else {
        at->next->prev = node;
    }
    at->next = node;
}

static void list_insertBefore(List* self, Node* node, Node* at)
{
    node->prev = at->prev;
    node->next = at;
    if (at->prev == NULL) {
        self->first = node;
    } else {
        at->prev->next = node;
    }
    at->prev = node;
}

Node* List_insertAfter(List* self, void* data, Node* at)
{
    assert(at);

    Node* node = list_newNode(data);
    list_insertAfter(self, node, at);
    self->size++;
    return node;
}

Node* List_insertBefore(List* self, void* data, Node* at)
{
    assert(at);

    Node* node = list_newNode(data);
    list_insertBefore(self, node, at);
    self->size++;
    return node;
}

static void list_pushFront(List* self, Node* node)
{
    if (self->first == NULL) {
        self->first = node;
        self->last = node;
        node->prev = NULL;
        node->next = NULL;
    } else {
        list_insertBefore(self, node, self->first);
    }
}

static void list_pushBack(List* self, Node* node)
{
    if (self->last == NULL) {
        list_pushFront(self, node);
    } else {
        list_insertAfter(self, node, self->last);
    }
}

Node* List_pushFront(List* self, void* data)
{
    Node* node = list_newNode(data);
    list_pushFront(self, node);
    self->size++;
    return node;
}

Node* List_pushBack(List* self, void* data)
{
    Node* node = list_newNode(data);
    list_pushBack(self, node);
    self->size++;
    return node;
}

void* List_remove(List* self, Node* node)
{
    assert(node);

    if (node->prev == NULL) {
        self->first = node->next;
    } else {
        node->prev->next = node->next;
    }
    if (node->next == NULL) {
        self->last = node->prev;
    } else {
        node->next->prev = node->prev;
    }
    void* data = node->data;
    free(node);
    self->size--;
    return data;
}

void List_clear(List* self)
{
    Node* next;
    for (Node* n = self->first; n; n = next) {
        next = n->next;
        List_remove(self, n);
    }
}
