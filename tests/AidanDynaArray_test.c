//
// Created by aidankeefe on 4/1/26.
//
#define AIDAN_SHORT_NAMES
#include <AidanDynaArray.h>
#include "../src/AidanString.c"
#include "Testing.h"

int testPush() {
    DArray_f32 arr = {0};
    arr_push(arr, 3.14);
    t_assert(arr.cap == 10);
    return 0;
}

int main() {
    Tests_set ts = {0};
    reg_test(ts, testPush);
    run_tests(&ts);
}