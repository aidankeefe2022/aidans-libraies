//
// Created by aidankeefe on 1/23/26.
//

#ifndef WOLFHTTPS_TESTING_H
#define WOLFHTTPS_TESTING_H
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m" // Resets to default color

#define Fail() printf(ANSI_COLOR_RED"failed: %s : %s : %d\n"ANSI_COLOR_RESET, __func__, __FILE__, __LINE__); result = 1;
#define t_assert(expr) if (!(expr)) {Fail()}
#define test_arg int result
#define test_end return result;


typedef enum test_err {
    SUCCESS,
    UNABLE_TO_REGISTER,
}test_err;


typedef struct test {
    int(*test)(int);
    struct test *next;
}Test;

typedef struct Tests {
    char* file;
    int size;
    Test* head;
    Test* tail;
}Tests_set;

test_err register_test(Tests_set* ts ,Test* test);
test_err run_tests(Tests_set *ts);


#endif //WOLFHTTPS_TESTING_H

#ifndef TESTING_IMPLIMENTED
#define TESTING_IMPLIMENTED

#define ts_init() {__FILE__}
#define reg_test(ts, func) register_test(&ts, &(Test){func});

test_err register_test(Tests_set* ts ,Test* test) {
    if (!ts)
        return UNABLE_TO_REGISTER;
    if (!ts->head) {
        ts->head = test;
        ts->tail = test;
        ts->size = 1;
        return SUCCESS;
    }else {
        ts->tail->next = test;
        ts->tail = test;
        ts->size++;
        return SUCCESS;
    }
}

test_err run_tests(Tests_set *ts) {

    int num_pass = 0;
    printf("####################################################################\n\nRunning tests... for %s\n\n", ts->file);
    clock_t start_t, end_t;

    start_t = clock();

    while (ts->head) {
        if (!ts->head->test(0)) {
            num_pass++;
        }
        ts->head = ts->head->next;
    }

    end_t = clock();

    double time = (double)(end_t - start_t)/CLOCKS_PER_SEC;

    printf(ANSI_COLOR_GREEN"%d of %d have passed \n"ANSI_COLOR_RESET, num_pass, ts->size);
    printf("Tests Ran In: %f seconds\n\n", time);
    if (ts->size > num_pass) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


#endif
