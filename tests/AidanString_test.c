//
// Created by aidankeefe on 1/18/26.
//
#include "../include/AidanTesting.h"
#define AIDAN_SHORT_NAMES
#include <AidanString.h>
#include "../src/AidanString.c"
#include "../src/AidanArena.c"

int test_str_append_string(test_arg) {
    Arena* a = arena_create(MiB(1));
    String* str = str_new(a,  2, "x", 10);
    String str1 = STR_LIT("hello");
    str_append_string(str, &str1);
    t_assert(str->length == 1 + str1.length);
    t_assert(str->s[1] == 'h');
    t_assert(str->s[2] == 'e');

    String test_str2 = STR_LIT("hello");
    String test_str3 = STR_LIT("hello");
    t_assert(str_append_string(&test_str2, &test_str3) == STRING_OVERFLOW);
    arena_free(a);
    test_end
}

int test_str_append_int(test_arg) {
    Arena* a = arena_create(MiB(1));
    String* str = str_new(a,  1, "h", 10);
    str_append_int(str, 70);
    t_assert(str->length == 3);
    t_assert(str->s[1] == '7');
    t_assert(str->s[2] == '0');


    String str1 = STR_LIT("hello");
    t_assert(str_append_int(&str1, 4) == STRING_OVERFLOW);

    arena_free(a);
    test_end
}

int test_str_append(test_arg) {
    Arena* a = arena_create(MiB(1));
    String* str = str_new(a,  2, "h", 10);
    str_append_char(str, 'i');
    t_assert(str->length == 3);
    t_assert(str->s[1] == 'i');

    //test overflow is caught

    String str1 = STR_LIT("hello");
    t_assert(str_append_char(&str1, 'l') == STRING_OVERFLOW);




    arena_free(a);
    test_end
}

int test_str_substring(test_arg) {
    Arena* a = arena_create(MiB(1));
    String str = STR_LIT("hello");
    String* new = str_new(a, sizeof(""), "", 40);

    t_assert(str_substring(&str, new, 0, 2) == STRING_SUCCESS);
    t_assert(new->length == 3);
    t_assert(new->s[0] == 'h');
    t_assert(new->s[1] == 'e');
    t_assert(new->s[2] == 'l');

    str_clear(new);
    t_assert(str_substring(&str, new, -1, -4) == STRING_OVERFLOW);

    arena_free(a);
    test_end
}


int test_str_concat(test_arg) {
    Arena* a = arena_create(MiB(1));\
    t_assert_exit(a)
    String str1 = STR_LIT("hello");
    String str2 = STR_LIT("hello");
    String* str3 = str_concat(a, &str1, &str2);

    t_assert(str3->length == 11);
    t_assert(str3->s[9] == 'o');
    t_assert(str3->s[0] == 'h');
    arena_free(a);

    test_end
}

int test_str_replace_char(test_arg) {
    Arena* a = arena_create(MiB(1));
    String *str = Q_STR(a, "Hello");
    int count = str_replace_char(str, 'e', 'l');
    t_assert(count == 1);
    t_assert(str->s[1] == 'l');
    arena_free(a);
    test_end
}

int test_str_clear(test_arg) {
    Arena* a = arena_create(MiB(1));
    String *str = Q_STR(a, "hello");
    str_clear(str);
    t_assert(str->length == 0);
    arena_free(a);
    test_end
}

int test_str_cmp(test_arg) {
    String str1 = STR_LIT("hello");
    String str2 = STR_LIT("hello");
    String str3 = STR_LIT("hetlo");
    String str4 = STR_LIT("hello4");
    t_assert(str_cmp(&str1, &str2));
    t_assert(!str_cmp(&str1, &str3));
    t_assert(!str_cmp(&str1, &str4));
    test_end
}

int main() {
    Tests_set ts = {__FILE__};
    reg_test(ts, test_str_append_string);
    reg_test(ts, test_str_clear);
    reg_test(ts, test_str_append);
    reg_test(ts, test_str_substring);
    reg_test(ts, test_str_concat);
    reg_test(ts, test_str_replace_char);
    reg_test(ts, test_str_cmp);
    return run_tests(&ts);
}
