#ifndef SCLIB_LIST_H
#define SCLIB_LIST_H

#include <stdbool.h>

typedef struct element Element;
struct element
{
    void* data;
    Element* next;
    Element* prev;
};

typedef struct list List;

List*    List_new          (void);
void     List_free         (List* self);
int      List_size         (List* self);
bool     List_empty        (List* self);
Element* List_first        (List* self);
Element* List_last         (List* self);
Element* List_insertAfter  (List* self, void* data, Element* at);
Element* List_insertBefore (List* self, void* data, Element* at);
Element* List_pushFront    (List* self, void* data);
Element* List_pushBack     (List* self, void* data);
void*    List_remove       (List* self, Element* elem);
void     List_clear        (List* self);

#endif /* SCLIB_LIST_H */
