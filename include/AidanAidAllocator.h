//
// Created by aidankeefe on 4/6/26.
//

#ifndef AIDANS_AIDANAIDALLOCATOR_H
#define AIDANS_AIDANAIDALLOCATOR_H

#include <AidanCommon.h>
#include <AidanDynaArray.h>
#include <AidanLinkedList.h>
#include <stdlib.h>

#ifdef AiDAN_SHORT_NAMES
#define AidAllocator_t AidAllocator
#else
#define AidAllocator_t aid_AidAllocator
#endif

typedef struct aid_AidAllocator {
    struct aid_DArray_void mem;
    struct aid_LinkedList freeList;
}AidAllocator_t;

void* aid_AidAlloc(AidAllocator_t* a, size_t size);
bool aid_AidFreePtr(AidAllocator_t* a, void* ptr);
void aid_AidReleaseAll(AidAllocator_t* a);
void* aid_AidRealloc(AidAllocator_t* a, void* ptr, size_t size);



#undef AidAllocator_t

#endif
