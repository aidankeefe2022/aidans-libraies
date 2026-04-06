//
// Created by aidankeefe on 3/30/26.
//

#ifndef AIDAN_DYNAARRAY
#define AIDAN_DYNAARRAY
#include "AidanCommon.h"
#include "AidanString.h"
#include <stdlib.h>

#ifdef AIDAN_SHORT_NAMES
#define Array DArray
#else
#define Array aid_DArray
#endif

#define aid_CONCAT_INNER(a, b) a##_##b
#define aid_CONCAT(a, b) aid_CONCAT_INNER(a, b)

typedef struct aid_CONCAT(Array, f32) {
    u64 cap;
    u64 len;
    f32* data;
}aid_CONCAT(Array, f32);

typedef struct aid_CONCAT(Array, f64) {
    u64 cap;
    u64 len;
    f64* data;
}aid_CONCAT(Array, f64);

typedef struct aid_CONCAT(Array, u64) {
    u64 cap;
    u64 len;
    u64* data;
}aid_CONCAT(Array, u64);

typedef struct aid_CONCAT(Array, i64) {
    u64 cap;
    u64 len;
    i64* data;
}aid_CONCAT(Array, i64);

typedef struct aid_CONCAT(Array, string) {
    u64 cap;
    u64 len;
    struct aid_string** data;
}aid_CONCAT(Array, string);

typedef struct aid_CONCAT(Array, void) {
    u64 cap;
    u64 len;
    void** data;
}aid_CONCAT(Array, void);

#ifdef AIDAN_SHORT_NAMES
#define arr_incr_cap(arr, n) do{ \
    if ((&arr)->len >= (&arr)->cap) { \
        (&arr)->cap += n; \
        void* temp = realloc((&arr)->data, (&arr)->cap*sizeof(*((&arr)->data))); \
        if(temp){\
            (&arr)->data = temp; \
        }else{\
            (&arr)->cap -= n;\
        }\
    }\
}while(0);
#define arr_push(arr,v) do{\
    if (((&arr)->len+1) >= (&arr)->cap) { \
        arr_incr_cap((arr), 10); \
    }\
    (&arr)->data[(&arr)->len++] = v; \
    }while(0);
#define arr_pop(arr) (&arr)->data[(--((&arr)->len))]
#else
#define aid_arr_incr_cap(arr, n) do{ \
    if ((&arr)->len >= (&arr)->cap) { \
        (&arr)->cap += n; \
        void* temp = realloc((&arr)->data, (&arr)->cap*sizeof(*((&arr)->data))); \
        if(temp){\
            (&arr)->data = temp; \
        }else{\
            (&arr)->cap -= n;\
        }\
    }\
}while(0);
#define aid_arr_push(arr,v) do{\
    if (((&arr)->len+1) >= (&arr)->cap) { \
        aid_arr_incr_cap((arr), 10); \
    }\
    (&arr)->data[(&arr)->len++] = v; \
    }while(0);
#define aid_arr_pop(arr) (&(arr)->data[(--((&(arr)->len))]
#endif



#undef Array
#undef aid_CONCAT

#endif
