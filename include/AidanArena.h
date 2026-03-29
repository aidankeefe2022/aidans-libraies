//
// Created by aidankeefe on 3/15/26.
//

#ifndef AIDAN_ARENA_H
#define AIDAN_ARENA_H 

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef AIDAN_SHORT_NAMES
    #define Arena Arena
#else
    #define Arena aid_Arena
#endif

typedef enum ARENA_STATUS {
    ARENA_OK,
    ARENA_ALLOCATION_ERROR,
    ARENA_CREATION_ERROR,
} ARENA_STATUS;


typedef struct aid_arena{
    uint8_t* currentPointer;
    size_t size;
    uint8_t* buffer;
}Arena;



Arena* aid_create_arena(size_t size_in_bytes);
void* aid_arena_alloc(Arena arena[static 1], size_t size, const size_t alignment);
ARENA_STATUS aid_arena_clear(Arena arena[static 1]);

#ifdef AIDAN_SHORT_NAMES
    Arena*(*arena_create)(size_t) = aid_create_arena;
    void* (*arena_alloc)(Arena*, size_t , const size_t) = aid_arena_alloc;
    ARENA_STATUS (*arena_clear) (Arena*) = aid_arena_clear;
#endif

#undef Arena

#endif //ACO_ARENA_H
