#include <stdlib.h>
#include <memory.h>
#include "template.h"
#include "alloc.h"

#ifndef T
    #error "Type argument T is not defined for <vector.h>"
    #define T int
#endif


#define GROWTH_FACTOR 2
#define VEC_T $T(T, vector)


typedef struct VEC_T {
    T* data;
    size_t top;
    size_t capacity;
} VEC_T;

#define VEC_REALLOC(me, new_capacity) do {                                     \
    me->capacity = new_capacity;                                               \
    me->data = REALLOC(                                                        \
        T,                                                                     \
        me->data,                                                              \
        me->capacity                                                           \
    );                                                                         \
} while(0);

static inline void $T(VEC_T, init)(VEC_T *me) {
    me->data = ALLOC(T, 1);
    me->top = 0;
    me->capacity = 1;
}

static inline void $T(VEC_T, free)(VEC_T *me) {
    DEALLOC(me->data);
}

static inline T* $T(VEC_T, at)(VEC_T *me, size_t pos) {
    return me->data + pos;
}

static inline T* $T(VEC_T, front)(VEC_T *me) {
    return me->data;
}

static inline T* $T(VEC_T, back)(VEC_T *me) {
    return me->data + me->top - 1;
}

static inline T* $T(VEC_T, data)(VEC_T *me) {
    return me->data;
}

static inline void $T(VEC_T, push_back)(VEC_T *me, T value) {
    if (me->top == me->capacity)
        VEC_REALLOC(me, me->capacity * GROWTH_FACTOR);

    me->data[me->top] = value;
    me->top++;
}

static inline void $T(VEC_T, pop_back)(VEC_T *me) {
    me->top--;
}

static inline void $T(VEC_T, insert)(VEC_T *me, size_t pos, T value) {
    if (me->top == me->capacity)
        VEC_REALLOC(me, me->capacity * GROWTH_FACTOR);

    memmove(
        me->data + pos + 1,
        me->data + pos,
        (me->top - pos) * sizeof(T)
    );

    me->data[pos] = value;
    me->top++;
}

static inline void $T(VEC_T, erase)(VEC_T *me, size_t pos) {
    memmove(
        me->data + pos,
        me->data + pos + 1,
        (me->top - pos) * sizeof(T)
    );
    
    me->top--;
}

#undef T
#undef VEC_T
#undef GROWTH_FACTOR
#undef VEC_REALLOC

#undef ALLOC
#undef CALLOC
#undef REALLOC
#undef DEALLOC
