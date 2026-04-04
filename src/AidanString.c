//
// Created by aidankeefe on 3/15/26.
//
 #include <AidanString.h>

constexpr f64 default_incr_ammount = 0.1;

//specifially Strigns not allocated usign a stack allocator
#ifdef AIDAN_DYNAMIC_STRINGS
    #define StringBump(String) if(str_incrcease_cap((String), default_incr_ammount * (String)->cap) == STRING_INCREASE_FAIL){ return STRING_INCREASE_FAIL; }
    #define StringBumpSpec(String, size) if(str_incrcease_cap((String), size) == STRING_INCREASE_FAIL){ return STRING_INCREASE_FAIL; }
#else
    #define StringBump(String) return STRING_OVERFLOW;
    #define StringBumpSpec(String, size) return STRING_OVERFLOW;
#endif

enum aid_str_err aid_str_incrcease_cap(struct aid_string* s, u64 incr_size){
    s->cap = s->cap + incr_size;
    void* new_ptr;
    if((new_ptr = realloc(s->s, s->cap)) != nullptr){
        s->s = new_ptr;
        return STRING_SUCCESS;
    }
    return STRING_INCREASE_FAIL;
}

enum aid_str_err aid_str_append_char(struct aid_string* s, char character) {
    if (s->length == s->cap) {
        StringBump(s)
    }
    s->s[s->length-1] = character;
    s->length++;
    return STRING_SUCCESS;
}

enum aid_str_err aid_str_append_int(struct aid_string* s, i64 num) {
    char buffer[22];
    int length = snprintf(buffer, sizeof(buffer), "%ld", num);
    if (s->length + length > s->cap) {
        StringBumpSpec(s, length)
    }
    for (u16 i = 0; i < length; i++) {
        s->s[s->length-1 + i] = buffer[i];
    }
    s->length += length;

    return STRING_SUCCESS;
}


enum aid_str_err aid_str_append_string(struct aid_string* str1, struct aid_string* str2) {
    if (str1->length + str2->length > str1->cap) {
        StringBumpSpec(str1, str2->length)
    }
    for (int i = 0; i < str2->length; i++) {
        str1->s[str1->length-1 + i] = str2->s[i];
    }
    str1->length = str2->length + str1->length - 1;
    return STRING_SUCCESS;
}


/*
 * creates a new string in the arena provided and then replaces the final char with \0
 */
struct aid_string* aid_str_new(struct aid_arena* arena, u64 length, char str[length], u64 cap) {
    struct aid_string* result = aid_arena_alloc(arena, sizeof(struct aid_string), alignof(struct aid_string));
    if (!result) {
        printf("Could not allocate memory for new String.");
        return nullptr;
    }
    char* new_string = aid_arena_alloc(arena, cap, alignof(char));
    if (!new_string) {
        printf("Could not allocate memory for new String.");
        return nullptr;
    }
    for (i64 i = 0; i < length; i++) {
        new_string[i] = str[i];
    }


    new_string[length-1] = '\0';

    result->s = new_string;
    result->length = length;
    result->cap = cap;
    return result;
}

enum aid_str_err aid_str_substring(struct aid_string old[static 1], struct aid_string new[static 1], u64 start, u64 end) {
    if (old->length < end || end-start > new->cap) return STRING_OVERFLOW;
    if (start >= end) return STRING_ILLEGAL_ARGUMENT;
    int index = 0;
    while (start < end) {
        new->s[index++] = old->s[start++];
    }
    new->length = index;
    return STRING_SUCCESS;
}


bool aid_str_cmp(struct aid_string* str1, struct aid_string* str2) {
    if (str1->length != str2->length) return false;
    for (i64 i = 0; i < str1->length; i++) {
        if (str1->s[i] != str2->s[i]) {
            return false;
        }
    }
    return true;
}

struct aid_string* aid_str_concat(struct aid_arena* arena, struct aid_string* str1, struct aid_string* str2) {
    u64 new_cap = str2->cap + str1->cap;
    auto result = aid_str_new(arena, str1->length, str1->s, new_cap);
    if (!result) {
        printf("Could not allocate memory for string concat.");
        return nullptr;
    }
    u64 idx = str1->length-1;
    for (u64 i = 0; i < str2->length; i++) {
        result->s[idx++] = str2->s[i];
    }
    result->length += str2->length-1;
    return result;
}


int aid_str_replace_char(struct aid_string* old, char old_char, char new_char) {
    int num_replaced = 0;
    for (u64 i = 0; i < old->length; i++) {
        if (old->s[i] == old_char) {
            old->s[i] = new_char;
            num_replaced++;
        }
    }
    return num_replaced;
}

enum aid_str_err aid_str_clear(struct aid_string* str) {
    int i = 0;
    while (i < str->length) {
        str->s[i++] = '\0';
    }
    str->length = 0;
    return STRING_SUCCESS;
}

#undef StringBump
#undef StringBumpSpec
