//
// Created by aidankeefe on 4/1/26.
//
#define AIDAN_SHORT_NAMES
#include <AidanDynaArray.h>
#include "../src/AidanString.c"
#include "../src/AidanArena.c"
#include "Testing.h"

int testPush_String() {
    DArray_string arr = {0};
    String s1 = STR_LIT("hello");
    arr_push(arr, &s1);
    t_assert(arr.cap == 10);
    t_assert(arr.len == 1);
    t_assert(str_cmp(arr.data[0],&STR_LIT("hello")) == true);
    return 0;
}

int testPop_String() {
    DArray_string arr = {0};
    String s1 = STR_LIT("hello");
    arr_push(arr, &s1);
    t_assert(arr.cap == 10);
    t_assert(arr.len == 1);
    t_assert(str_cmp(arr.data[0],&STR_LIT("hello")) == true);
    String* str2 = arr_pop(arr);
    t_assert(str_cmp(arr.data[0],&STR_LIT("hello")) == true);
    t_assert(arr.len == 0);
    return 0;
}

int testPush_f32() {
    DArray_f32 arr = {0};
    arr_push(arr, 3.14f);
    t_assert(arr.cap == 10);
    t_assert(arr.len == 1);
    t_assert(arr.data[0] == 3.14f);

    arr_push(arr, 6.7f);
    t_assert(arr.cap == 10);
    t_assert(arr.len == 2);
    t_assert(arr.data[0] == 3.14f);
    t_assert(arr.data[1] == 6.7f);
    return 0;
}

int testPop_f32() {
    DArray_f32 arr = {0};
    arr_push(arr, 3.14f);
    t_assert(arr.cap == 10);
    t_assert(arr.len == 1);
    t_assert(arr.data[0] == 3.14f);

    f32 popVal = arr_pop(arr);
    t_assert(popVal == 3.14f);
    t_assert(arr.len == 0);
    return 0;
}

int testPush_f64() {
    DArray_f64 arr = {0};
    arr_push(arr, 3.14);
    t_assert(arr.cap == 10);
    t_assert(arr.len == 1);
    t_assert(arr.data[0] == 3.14);

    arr_push(arr, 6.7);
    t_assert(arr.cap == 10);
    t_assert(arr.len == 2);
    t_assert(arr.data[0] == 3.14);
    t_assert(arr.data[1] == 6.7);
    return 0;
}

int testPop_f64() {
    DArray_f64 arr = {0};
    arr_push(arr, 3.14);
    t_assert(arr.cap == 10);
    t_assert(arr.len == 1);
    t_assert(arr.data[0] == 3.14);

    f64 popVal = arr_pop(arr);
    t_assert(popVal == 3.14);
    t_assert(arr.len == 0);
    return 0;
}

int testPush_u64() {
    DArray_u64 arr = {0};
    arr_push(arr, 42);
    t_assert(arr.cap == 10);
    t_assert(arr.len == 1);
    t_assert(arr.data[0] == 42);

    arr_push(arr, 99);
    t_assert(arr.cap == 10);
    t_assert(arr.len == 2);
    t_assert(arr.data[0] == 42);
    t_assert(arr.data[1] == 99);
    return 0;
}

int testPop_u64() {
    DArray_u64 arr = {0};
    arr_push(arr, 42);
    t_assert(arr.cap == 10);
    t_assert(arr.len == 1);
    t_assert(arr.data[0] == 42);

    u64 popVal = arr_pop(arr);
    t_assert(popVal == 42);
    t_assert(arr.len == 0);
    return 0;
}

int testPush_i64() {
    DArray_i64 arr = {0};
    arr_push(arr, -42);
    t_assert(arr.cap == 10);
    t_assert(arr.len == 1);
    t_assert(arr.data[0] == -42);

    arr_push(arr, 99);
    t_assert(arr.cap == 10);
    t_assert(arr.len == 2);
    t_assert(arr.data[0] == -42);
    t_assert(arr.data[1] == 99);
    return 0;
}

int testPop_i64() {
    DArray_i64 arr = {0};
    arr_push(arr, -42);
    t_assert(arr.cap == 10);
    t_assert(arr.len == 1);
    t_assert(arr.data[0] == -42);

    i64 popVal = arr_pop(arr);
    t_assert(popVal == -42);
    t_assert(arr.len == 0);
    return 0;
}

int main() {
    Tests_set ts = ts_init();

    reg_test(ts, testPush_f32);
    reg_test(ts, testPop_f32);

    reg_test(ts, testPush_f64);
    reg_test(ts, testPop_f64);

    reg_test(ts, testPush_u64);
    reg_test(ts, testPop_u64);

    reg_test(ts, testPush_i64);
    reg_test(ts, testPop_i64);

    reg_test(ts, testPush_String);
    reg_test(ts, testPop_String);

    run_tests(&ts);
}