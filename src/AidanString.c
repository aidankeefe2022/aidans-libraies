//
// Created by aidankeefe on 3/15/26.
//
 #include <AidanString.h>

constexpr f64 default_incr_amount = 0.1;

#define resize(string, additionalSpace) do{\
        if (string->options & AID_STR_AUTO_RESIZE){\
            if(aid_str_incrcease_cap(string, additionalSpace) == STRING_INCREASE_FAIL)   \
                return STRING_INCREASE_FAIL;\
        }else{\
            return STRING_OVERFLOW;\
        }\
    }while (0)

enum aid_str_err aid_str_incrcease_cap(struct aid_string* s, u64 incr_size){
    s->cap = s->cap + incr_size;
    char* new_ptr;
    if((new_ptr = realloc(s->s, s->cap)) != nullptr){
        s->s = new_ptr;
        return STRING_SUCCESS;
    }
    return STRING_INCREASE_FAIL;
}

enum aid_str_err aid_str_append_char(struct aid_string* s, char character) {
    if (s->length == s->cap) {
        resize(s, 10);
    }
    s->s[s->length] = character;
    s->length++;
    return STRING_SUCCESS;
}

enum aid_str_err aid_str_append_int(struct aid_string* s, i64 num) {
    char buffer[22];
    int length = snprintf(buffer, sizeof(buffer), "%ld", num);
    bool resize = s->options & AID_STR_AUTO_RESIZE;
    if (s->length + length > s->cap && resize) {
        resize(s, length+2);
    }
    for (u16 i = 0; i < length; i++) {
        s->s[s->length-1 + i] = buffer[i];
    }
    s->length += length;

    return STRING_SUCCESS;
}


enum aid_str_err aid_str_append_string(struct aid_string* str1, struct aid_string* str2) {
    if (str1->length + str2->length > str1->cap) {
        resize(str1, str2->length);
    }
    for (int i = 0; i < str2->length; i++) {
        str1->s[str1->length + i] = str2->s[i];
    }
    str1->length = str2->length + str1->length;
    return STRING_SUCCESS;
}


/*
 * creates a new string in the arena provided this is not a null terminated array
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

    result->s = new_string;
    result->length = length;
    result->options = 0;
    result->cap = cap;
    return result;
}

enum aid_str_err aid_str_substring(struct aid_string old[static 1], struct aid_string new[static 1], u64 start, u64 end) {
    if (old->length < end || end-start > new->cap) return STRING_OVERFLOW;
    if (start >= end) return STRING_ILLEGAL_ARGUMENT;
    int index = 0;
    while (start <= end) {
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
    u64 idx = str1->length;
    for (u64 i = 0; i <= str2->length; i++) {
        result->s[idx++] = str2->s[i];
    }
    result->length += str2->length;
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
