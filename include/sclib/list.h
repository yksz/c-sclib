#ifndef SCLIB_LIST_H
#define SCLIB_LIST_H

#include <stdbool.h>

typedef struct node Node;
struct node
{
    void* data;
    Node* next;
    Node* prev;
};

typedef struct list List;

List* List_new          ();
void  List_free         (List* self);
int   List_size         (List* self);
bool  List_empty        (List* self);
Node* List_first        (List* self);
Node* List_last         (List* self);
Node* List_insertAfter  (List* self, void* data, Node* at);
Node* List_insertBefore (List* self, void* data, Node* at);
Node* List_pushFront    (List* self, void* data);
Node* List_pushBack     (List* self, void* data);
void* List_remove       (List* self, Node* node);
void  List_clear        (List* self);

#endif /* SCLIB_LIST_H */
