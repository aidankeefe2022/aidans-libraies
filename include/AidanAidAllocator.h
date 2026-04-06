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
#define AidAllocator AidAllocator
#else
#define AidAllocator aid_AidAllocator
#endif

typedef struct aid_AidAllocator {
    struct aid_DArray_void mem;
    struct aid_LinkedList freeList;
}AidAllocator;

void* aid_AidAlloc(AidAllocator* a, size_t size);
bool aid_AidFreePtr(AidAllocator* a, void* ptr);
void aid_AidReleaseAll(AidAllocator* a);




#undef AidAllocator
#undef AidAllocatorCode

#endif
