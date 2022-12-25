#ifdef ALLOCATOR
    #define ALLOC(T, size)           $(T *) (ALLOCATOR, alloc)(size * sizeof(T))
    #define CALLOC(T, size)          $(T *) (ALLOCATOR, calloc)(size, sizeof(T))
    #define REALLOC(T, memptr, size) $(T *) (ALLOCATOR, realloc)(memptr, size * sizeof(T))
    #define DEALLOC(memptr)          $(ALLOCATOR, dealloc)(memptr)
#else
    #define ALLOC(T, size)           (T *) malloc(size * sizeof(T))
    #define CALLOC(T, size)          (T *) calloc(size, sizeof(T))
    #define REALLOC(T, memptr, size) (T *) realloc(memptr, size * sizeof(T))
    #define DEALLOC(memptr)          free(memptr)
#endif
