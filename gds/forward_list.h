#include <stdlib.h>
#include <stdbool.h>
#include "template.h"
#include "alloc.h"


#ifndef T
    #error "Type argument T is not defined for <forward_list.h>"
    #define T int
#endif


#define LIST_T $T(T,  flist)
#define NODE_T $T(LIST_T, node)
#define ITER_T $T(LIST_T, iter)

typedef struct NODE_T {
    T data;
    struct NODE_T *next;
} NODE_T;

typedef struct LIST_T {
    NODE_T *head;
} LIST_T;


static inline void $T(NODE_T, init)(NODE_T *me, T value, NODE_T* next) {
    me->data = value;
    me->next = next;
}

static inline void $T(NODE_T, free)(NODE_T *me) {
    DEALLOC(me);
}

static inline void $T(LIST_T, init)(LIST_T *me) {
    me->head = NULL;
}

static inline void $T(LIST_T, free)(LIST_T *me) {
    NODE_T *curr = me->head;
    while (curr != NULL) {
        NODE_T *tmp = curr;
        curr = curr->next;
        $T(NODE_T, free)(tmp);
    }
}

static inline T* $T(LIST_T, front)(LIST_T *me) {
    return &me->head->data;
}

static inline bool $T(LIST_T, empty)(LIST_T *me) {
    return me->head == NULL;
}

static inline void $T(LIST_T, clear)(LIST_T *me) {
    $T(LIST_T, free)(me);
    $T(LIST_T, init)(me);
}

static inline void $T(LIST_T, push_front)(LIST_T *me, T value) {
    NODE_T *node = ALLOC(NODE_T, 1);
    $T(NODE_T, init)(node, value, me->head);
    me->head = node;
}

static inline void $T(LIST_T, pop_front)(LIST_T *me) {
    NODE_T *tmp = me->head;
    me->head = me->head->next;
    $T(NODE_T, free)(tmp);
}


#undef T
#undef NODE_T
#undef LIST_T

#undef ALLOC
#undef CALLOC
#undef REALLOC
#undef DEALLOC
