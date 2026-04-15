//
// Created by aidankeefe on 4/8/26.
//
#define AIDAN_SHORT_NAMES
#include <AidanAidAllocator.h>
#include "../src/AidanAidAllocator.c"
#include "../src/AidanArena.c"
#include "../src/AidanString.c"
#include "../src/AidanLinkedList.c"
#include "../include/AidanTesting.h"

int testAlloc(test_arg) {
    struct aid_AidAllocator a = {0};
    i32 *i = aid_AidAlloc(&a, sizeof(i32));
    t_assert(i == a.mem.data[0])
    t_assert(a.mem.len == 1)
    t_assert(i != nullptr);
    *i = 4;
    t_assert(*i == 4);
    aid_AidReleaseAll(&a);
    test_end
}

int testRealloc(test_arg) {
    struct aid_AidAllocator a = {0};
    i32 *i = aid_AidAlloc(&a, sizeof(i32));
    i32 *y = aid_AidRealloc(&a, i, 2 * sizeof(i32));
    t_assert(y == a.mem.data[0])
    t_assert(a.mem.len == 1)
    t_assert(y != nullptr);
    *y = 4;
    t_assert(*y == 4);
    aid_AidReleaseAll(&a);
    test_end
}

int testFree(test_arg) {
    struct aid_AidAllocator a = {0};
    i32 *i = aid_AidAlloc(&a, sizeof(i32));
    t_assert(i == a.mem.data[0])
    aid_AidFreePtr(&a, i);
    t_assert(NULL == a.mem.data[0])
    aid_AidReleaseAll(&a);
    test_end
}



int main() {
    Tests_set ts = ts_init();
    reg_test(ts, testAlloc);
    reg_test(ts, testRealloc);
    reg_test(ts, testFree);
    run_tests(&ts);
    return 0;
}
