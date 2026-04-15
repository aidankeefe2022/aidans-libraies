# AidanTesting

`AidanTesting.h` is a small single-header test runner for C. It gives you:

- a standard test function signature
- a simple assertion macro
- a linked-list based test registry with no dynamic allocations
- a runner that prints pass/fail output and a summary

The intended usage is shown in [tests/AidanLinkedList_test.c](/home/aidankeefe/Coding/c-projects/aidans-libraies/tests/AidanLinkedList_test.c:1).

## Include It

Include the header in the test file that defines and runs your tests:

```c
#include <LibAidan/AidanTesting.h>
```

This header contains both declarations and implementation, so it is meant to be included in the test translation unit that uses it.

## Test Function Shape

Each test should use the `test_arg` macro in its parameter list:

```c
int testPush(test_arg) {
    <test logic>
    <clean up>
    test_end
}
```

These macros when used with t_assert allows for test fall through and any clean up code to be hit as long as there is 
no crash!

## Assertions

Use `t_assert(expr)` for checks:

```c
t_assert(ll.size == 1)
t_assert(ll.head == ll.tail)
```

If the expression is false:

- the test prints a red `failed` message
- `result` is set to `1`
- execution continues unless you return early yourself

To finish a test, use:

```c
test_end
```

`test_end` expands to:

```c
return result;
```

If no assertions failed, the test returns `0`.

## Registering Tests

Create a `Tests_set` and register each test with `reg_test`:

```c
int main(test_arg) {
    Tests_set ts = {__FILE__};
    reg_test(ts, test1);
    reg_test(ts, test2);
    return run_tests(&ts);
}
```

`Tests_set` stores:

- `file`: label printed by the runner
- `size`: number of registered tests
- `head` / `tail`: internal linked-list pointers

`reg_test(ts, func)` wraps `register_test(&ts, &(Test){func});`.

## Running Tests

Run the entire set with:

```c
return run_tests(&ts);
```

`run_tests`:

- prints a header with the source file name
- runs each registered test
- counts tests that returned `0`
- prints total passed vs total registered
- prints elapsed runtime
- returns `EXIT_SUCCESS` if all tests passed
- returns `EXIT_FAILURE` if any test failed

## Example

This is the same overall pattern used in [tests/AidanLinkedList_test.c](/home/aidankeefe/Coding/c-projects/aidans-libraies/tests/AidanLinkedList_test.c:7):

```c
#include "../include/AidanTesting.h"

int testPush(test_arg) {
    int value = 42;
    t_assert(value == 42)
    test_end
}

int testPop(test_arg) {
    int value = 5;
    t_assert(value != 0)
    test_end
}

int main(test_arg) {
    Tests_set ts = {__FILE__};

    reg_test(ts, testPush);
    reg_test(ts, testPop);

    return run_tests(&ts);
}
```

## Output

A failing assertion prints something like:

```text
failed: testPush : tests/example_test.c : 12
```

The full run ends with a summary similar to:

```text
Running tests... for tests/example_test.c
2 of 2 have passed
Tests Ran In: 0.000123 seconds
```

## Notes

- `t_assert(...)` does not stop the test immediately. Multiple assertions in the same test can fail before `test_end` returns.
- `reg_test(...)` assumes the `Tests_set` variable is passed by name, not by pointer.
- `run_tests(...)` consumes the internal `head` pointer while iterating, so the same `Tests_set` should not be reused for another run without rebuilding it.
- The header currently defines implementation directly after the declaration section, so it behaves like a header-only utility.
