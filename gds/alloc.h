#ifdef ALLOCATOR
    #define ALLOC(T, size)           (T *) $T(ALLOCATOR, alloc)(size * sizeof(T))
    #define CALLOC(T, size)          (T *) $T(ALLOCATOR, calloc)(size, sizeof(T))
    #define REALLOC(T, memptr, size) (T *) $T(ALLOCATOR, realloc)(memptr, size * sizeof(T))
    #define DEALLOC(memptr)          $T(ALLOCATOR, dealloc)(memptr)
#else
    #define ALLOC(T, size)           (T *) malloc(size * sizeof(T))
    #define CALLOC(T, size)          (T *) calloc(size, sizeof(T))
    #define REALLOC(T, memptr, size) (T *) realloc(memptr, size * sizeof(T))
    #define DEALLOC(memptr)          free(memptr)
#endif
