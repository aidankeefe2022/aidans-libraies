//
// Created by aidankeefe on 4/8/26.
//
#define AIDAN_SHORT_NAMES
#include <AidanAidAllocator.h>
#include "../src/AidanAidAllocator.c"
#include "../src/AidanArena.c"
#include "../src/AidanString.c"
#include "../src/AidanLinkedList.c"
#include "Testing.h"

int testAlloc() {
    struct aid_AidAllocator a = {0};
    i32 *i = aid_AidAlloc(&a, sizeof(i32));
    t_assert(i == a.mem.data[0])
    t_assert(a.mem.len == 1)
    t_assert(i != nullptr);
    *i = 4;
    t_assert(*i == 4);
    aid_AidReleaseAll(&a);
    return 0;
}


int main() {
    Tests_set ts = ts_init();
    reg_test(ts, testAlloc);
    run_tests(&ts);
    return 0;
}
