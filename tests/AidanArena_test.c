//
// Created by aidankeefe on 3/30/26.
//
#define AIDAN_SHORT_NAMES
#include <AidanArena.h>
#include "../src/AidanArena.c"

#include "AidanCommon.h"
#include "Testing.h"

int testCreateArena() {
    Arena* a = arena_create(MiB(1));
    t_assert(a);
    arena_free(a);
    return 0;
}


int testAllocate() {
    Arena* a = arena_create(MiB(1));
    t_assert(a);
    u64* i = arena_alloc(a, sizeof(u64), alignof(u64));
    t_assert(i);
    *i = 6;
    t_assert(*i == 6);
    arena_free(a);
    return 0;
}

int main() {
    Tests_set ts = {0};
    reg_test(ts, testCreateArena);
    reg_test(ts, testAllocate);
    run_tests(&ts);
}
