#define AIDAN_SHORT_NAMES
	#include <AidanLinkedList.h>

	#include "../src/AidanLinkedList.c"
	#include "../src/AidanArena.c"
	#include "../src/AidanString.c"
	#include "Testing.h"

	int testPush(){
		LinkedList ll = {0};
		u64 i = 0;
		aid_push(&ll, &i, U64);
		t_assert(ll.size == 1)
		t_assert(ll.cap == 1)
		t_assert(ll.head->val.U64 == 0);
		t_assert(ll.tail->val.U64 == 0);
		t_assert(ll.head == ll.tail);

		aid_push(&ll, &i, 0);

		t_assert(ll.size == 2)
		t_assert(ll.cap == 2)
		t_assert(ll.head->val.U64 == 0);
		t_assert(ll.tail->val.U64 == 0);
		t_assert(ll.head != ll.tail);

		return 0;
	}

	int testReserve(){
		LinkedList ll = {0};
		aid_reserve(&ll, 6);
		t_assert(ll.cap == 6);
		t_assert(ll.head);
		t_assert(ll.tail);
		return 0;
	}

	int testPop() {
		LinkedList ll = {0};
		u64 i = 3;
		aid_push(&ll, &i, U64);
		u64 x = aid_pop(&ll).val.U64;
		t_assert(x == 3);
		t_assert(!ll.tail);
		t_assert(ll.size == 0);
		t_assert(ll.cap == 0);
		return 0;
	}


	int testCollectGarbage() {
		LinkedList ll = {0};
		u64 i = 3;
		aid_push(&ll, &i, U64);
		u64 x = aid_pop(&ll).val.U64;
		t_assert(x == 3);
		t_assert(!ll.tail);
		t_assert(ll.size == 0);
		t_assert(ll.cap == 0);

		t_assert(ll.LOST_NODES);
		t_assert(aid_collect_garbage(&ll));
		t_assert(!ll.LOST_NODES);

		return 0;
	}

	int testIterate() {
		LinkedList ll = {0};
		u64 i = 3;
		aid_push(&ll, &i, U64);
		aid_push(&ll, &i, U64);
		aid_push(&ll, &i, U64);

		LLNode* node = aid_head(&ll);

		while (node) {
			t_assert(node->val.U64 == 3);
			node = node->next;
		}
	return 0;
}
int main(){
	Tests_set ts = {__FILE__};
	register_test(&ts, &(Test){testPush});
	register_test(&ts, &(Test){testReserve});
	register_test(&ts, &(Test){testPop});
	register_test(&ts, &(Test){testCollectGarbage});
	register_test(&ts, &(Test){testIterate});
	run_tests(&ts);
	return EXIT_SUCCESS;
}
