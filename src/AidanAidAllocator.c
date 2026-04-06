//
// Created by aidankeefe on 4/6/26.
//
#include <AidanAidAllocator.h>

void* aid_AidAlloc(struct aid_AidAllocator* a, size_t size) {
    if (a->freeList.size > 0) {
        auto node = aid_pop_first(&a->freeList);
        if (node.type == U64) {
            void* ptr = malloc(size);
            a->mem.data[node.U64] = ptr;
            return ptr;
        }
        return nullptr;
    }
    void* ptr = malloc(size);
    aid_arr_push(a->mem, ptr);
    return ptr;
}
bool aid_AidFreePtr(struct aid_AidAllocator* a, void* ptr) {
    for (u64 i = 0; i < a->mem.len; i++) {
        if (a->mem.data[i] == ptr) {
            aid_push(&a->freeList, &i, U64);
            a->mem.data[i] = NULL;
            free(ptr);
            return true;
        }
    }
    return false;
}
void aid_AidReleaseAll(struct aid_AidAllocator* a) {
    for (u64 i = 0; i < a->mem.len; i++) {
        if (a->mem.data[i] != NULL)
            free(a->mem.data[i]);
    }
}
