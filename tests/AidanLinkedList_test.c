#define AIDAN_SHORT_NAMES
#include <AidanLinkedList.h>

#include "../src/AidanLinkedList.c"
#include "../src/AidanArena.c"
#include "../src/AidanString.c"
#include "../include/AidanTesting.h"

int testPush(test_arg){
	LinkedList ll = {0};
	u64 i = 4;
	aid_push(&ll, &i, U64);
	t_assert(ll.size == 1)
	t_assert(ll.head->U64 == 4);
	t_assert(ll.tail->U64 == 4);
	t_assert(ll.head == ll.tail);

	aid_push(&ll, &i, U64);

	t_assert(ll.size == 2)
	t_assert(ll.head->U64 == 4);
	t_assert(ll.tail->U64 == 4);
	t_assert(ll.head != ll.tail);

    aid_free_LL(&ll);
	test_end
}

int testPop(test_arg) {
	LinkedList ll = {0};
	u64 i = 3;
	aid_push(&ll, &i, U64);
	u64 x = aid_pop(&ll).U64;
	t_assert(x == 3);
	t_assert(!ll.tail);
	t_assert(ll.size == 0);

    aid_free_LL(&ll);
	test_end
}

int test_u64_type(test_arg) {
    LinkedList ll = {0};

    u64 a = 10;
    u64 b = 20;

    t_assert(aid_push(&ll, &a, U64) == true);
    t_assert(aid_push(&ll, &b, U64) == true);
	t_assert(ll.size == 2);

    LLNode n1 = aid_pop(&ll);
    t_assert(n1.U64 == 20);

    LLNode n2 = aid_pop(&ll);
    t_assert(n2.U64 == 10);

    aid_free_LL(&ll);
    test_end
}

int test_i64_type(test_arg) {
    LinkedList ll = {0};

    i64 a = -10;
    i64 b = -20;

    t_assert(aid_push(&ll, &a, I64) == true);
    t_assert(aid_push(&ll, &b, I64) == true);

    LLNode n1 = aid_pop(&ll);
    t_assert(n1.I64 == -20);

    LLNode n2 = aid_pop(&ll);
    t_assert(n2.I64 == -10);

    aid_free_LL(&ll);
    test_end
}

int test_f32_type(test_arg) {
    LinkedList ll = {0};

    f32 a = 1.5f;
    f32 b = 2.5f;

    t_assert(aid_push(&ll, &a, F32) == true);
    t_assert(aid_push(&ll, &b, F32) == true);

    LLNode n1 = aid_pop(&ll);
    t_assert(n1.F32 == 2.5f);

    LLNode n2 = aid_pop(&ll);
    t_assert(n2.F32 == 1.5f);

    aid_free_LL(&ll);
    test_end
}

int test_f64_type(test_arg) {
    LinkedList ll = {0};

    f64 a = 1.25;
    f64 b = 2.75;

    t_assert(aid_push(&ll, &a, F64) == true);
    t_assert(aid_push(&ll, &b, F64) == true);

    LLNode n1 = aid_pop(&ll);
    t_assert(n1.F64 == 2.75);

    LLNode n2 = aid_pop(&ll);
    t_assert(n2.F64 == 1.25);

    aid_free_LL(&ll);
    test_end
}

int test_voidptr_type(test_arg) {
    LinkedList ll = {0};

    int a = 11;
    int b = 22;

    void *pa = &a;
    void *pb = &b;

    t_assert(aid_push(&ll, pa, VOIDPTR) == true);
    t_assert(aid_push(&ll, pb, VOIDPTR) == true);

    LLNode n1 = aid_pop(&ll);
    t_assert(n1.VOIDPTR == pb);

    LLNode n2 = aid_pop(&ll);
    t_assert(n2.VOIDPTR == pa);

    aid_free_LL(&ll);
    test_end
}

int test_string_type(test_arg) {
    LinkedList ll = {0};

    struct aid_string s1 = {0};
    struct aid_string s2 = {0};

    t_assert(aid_push(&ll, &s1, STRING) == true);
    t_assert(aid_push(&ll, &s2, STRING) == true);

    LLNode n1 = aid_pop(&ll);
    t_assert(n1.STRING == &s2);

    LLNode n2 = aid_pop(&ll);
    t_assert(n2.STRING == &s1);

    aid_free_LL(&ll);
    test_end
}

int test_mixed_types_fail(test_arg) {
    LinkedList ll = {0};

    u64 x = 5;
    i64 y = -5;

    t_assert(aid_push(&ll, &x, U64) == true);
    t_assert(aid_push(&ll, &y, I64) == true);

    aid_free_LL(&ll);
    test_end
}

int testCollectGarbage(test_arg) {
	LinkedList ll = {0};
	u64 i = 3;
	aid_push(&ll, &i, U64);
	u64 x = aid_pop(&ll).U64;
	t_assert(x == 3);
	t_assert(!ll.tail);
	t_assert(ll.size == 0);


	t_assert(ll.LOST_NODES);
	t_assert(aid_collect_garbage(&ll));
	t_assert(!ll.LOST_NODES);
	aid_free_LL(&ll);
	test_end
}

int testIterate(test_arg){
	LinkedList ll = {0};
	u64 i = 3;
	aid_push(&ll, &i, U64);
	aid_push(&ll, &i, U64);
	aid_push(&ll, &i, U64);

	LLNode* node = ll.head;

	while (node) {
		t_assert(node->U64 == 3);
		node = node->next;
	}

	aid_free_LL(&ll);
	test_end
}

int main(test_arg){
	Tests_set ts = ts_init();
	reg_test(ts, testPush);
	reg_test(ts, testPop);
	reg_test(ts, testCollectGarbage);
	reg_test(ts, testIterate);
    reg_test(ts, test_u64_type);
    reg_test(ts, test_i64_type);
    reg_test(ts, test_f32_type);
    reg_test(ts, test_f64_type);
    reg_test(ts, test_voidptr_type);
    reg_test(ts, test_string_type);
    reg_test(ts, test_mixed_types_fail);
	return run_tests(&ts);
}
