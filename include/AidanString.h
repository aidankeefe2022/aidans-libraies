//
// Created by aidankeefe on 3/15/26.
//

#ifndef AIDAN_STRING_H
#define AIDAN_STRING_H
#include "AidanCommon.h"
#include "AidanArena.h"
#include <stdio.h>



#ifdef AIDAN_SHORT_NAMES
    #define String String
    #define str_err str_err 
#else
    #define String aid_String
    #define str_err aid_str_err
#endif

typedef enum aid_str_err {
    STRING_SUCCESS = 0,
    STRING_OVERFLOW,
    STRING_ILLEGAL_ARGUMENT,
    STRING_INCREASE_FAIL,
}str_err;



typedef struct aid_string {
    u64 cap;//must be the size of the s char array;
    u64 length;
    char* s;
}String;

#define STR_LIT(STR) (String){sizeof(STR), sizeof(STR), STR}
#define Q_STR(Arena,STR) str_new(Arena, sizeof(STR), STR, sizeof(STR))

str_err aid_str_incrcease_cap(String* s, u64 incr_size);
str_err aid_str_append_char(String* s, char character);
str_err aid_str_append_int(String* s, i64 num);
String* aid_str_new(struct aid_arena* arena, u64 length, char str[length], u64 cap);
str_err aid_str_append_string(String* str1, String* str2);
str_err aid_str_substring(String old[static 1], String new[static 1], u64 start, u64 end);
String* aid_str_concat(struct aid_arena* arena, String* str1, String* str2);
int aid_str_replace_char(String* old, char old_char, char new_char);
bool aid_str_cmp(String* str1, String* str2);
str_err aid_str_clear(String* str);

#ifdef AIDAN_SHORT_NAMES

str_err (*str_incrcease_cap)(String*, u64) = aid_str_incrcease_cap;
str_err(*str_append_char)(String*, char) = aid_str_append_char;
str_err(*str_append_int)(String*, i64) = aid_str_append_int;
String*(*str_new)(struct aid_arena*, u64, char*, u64) = aid_str_new;
str_err(*str_append_string)(String*, String*) = aid_str_append_string;
str_err(*str_substring)(String*, String*, u64, u64) = aid_str_substring;
String*(*str_concat)(struct aid_arena*, String*, String*) = aid_str_concat;
int (*str_replace_char)(String*, char, char) = aid_str_replace_char;
bool(*str_cmp)(String*, String*) = aid_str_cmp;
str_err(*str_clear)(String*) = aid_str_clear;
#endif

#undef String
#undef str_err

#endif 
