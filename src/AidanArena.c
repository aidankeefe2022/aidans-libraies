//
// Created by aidankeefe on 3/15/26.
//
#include <AidanArena.h>

/*
 * create an arena according
 */
struct aid_arena* aid_create_arena(const size_t size_in_bytes) {
    struct aid_arena* arena = calloc(1, sizeof(*arena));
    if (arena == nullptr) return nullptr;
    uint8_t* buffer = calloc(size_in_bytes, sizeof(char));
    if (!buffer){
        free(arena);
        return nullptr;
    }
    arena->buffer = buffer;
    arena->currentPointer = arena->buffer;
    arena->size = size_in_bytes;

    return arena;
}

static void* aid_arena_ptr_align(void* ptr, const size_t alignment) {
    uintptr_t p = (uintptr_t)ptr;
    uintptr_t aligned = (p + alignment - 1) & ~(alignment - 1);
    return (void*)aligned;
}

void* aid_arena_alloc(struct aid_arena arena[static 1], size_t size, const size_t alignment) {
    if (arena->currentPointer - arena->buffer + size > arena->size) {
        return nullptr;
    }
    void* ptr = aid_arena_ptr_align(arena->currentPointer, alignment);
    arena->currentPointer = ptr + size ;
    return ptr;
}


ARENA_STATUS aid_arena_clear(struct aid_arena arena[static 1]) {
    memset(arena->buffer, 0, arena->currentPointer - (uint8_t*)arena->buffer);
    arena->currentPointer = arena->buffer;
    return ARENA_OK;
}

ARENA_STATUS aid_arena_free(struct aid_arena* arena) {
    free(arena->buffer);
    free(arena);
    return ARENA_OK;
}
