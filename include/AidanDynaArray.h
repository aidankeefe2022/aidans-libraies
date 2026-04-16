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

#define ArrayCreateInner(Array, type, typeName) typedef struct aid_CONCAT(aid_DArray, typeName){ \
    u64 cap;\
    u64 len;\
    type* data;\
}aid_CONCAT(Array, typeName)
#define ArrayCreate(type, typeName) ArrayCreateInner(Array, type, typeName)

ArrayCreate(u64, u64);
ArrayCreate(f64, f64);
ArrayCreate(f32, f32);
ArrayCreate(i64, i64);
ArrayCreate(struct aid_string*, string);
ArrayCreate(void*, void);

#ifdef AIDAN_SHORT_NAMES
#define arr_incr_cap_cust(arr, n, reallocator) do{ \
    if ((&arr)->len >= (&arr)->cap) { \
        (&arr)->cap += n; \
        void* temp = reallocator((&arr)->data, (&arr)->cap*sizeof(*((&arr)->data))); \
        if(temp){\
            (&arr)->data = temp; \
        }else{\
            (&arr)->cap -= n;\
        }\
    }\
}while(0);
#define arr_push_cust(arr,v, reallocator) do{\
    if (((&arr)->len+1) >= (&arr)->cap) { \
        arr_incr_cap((arr), 10, reallocator); \
    }\
    (&arr)->data[(&arr)->len++] = v; \
    }while(0);
#define arr_incr_cap(arr, n) do{ \
    if ((&arr)->len >= (&arr)->cap) { \
        (&arr)->cap += n; \
        void* temp = realloc((&arr)->data, (&arr)->cap*sizeof(*((&arr)->data)));\
        if(temp){\
            (&arr)->data = temp;\
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
#endif


#define aid_arr_incr_cap_cust(arr, n, reallocator) do{ \
    if ((&arr)->len >= (&arr)->cap) { \
        (&arr)->cap += n; \
        void* temp = reallocator((&arr)->data, (&arr)->cap*sizeof(*((&arr)->data))); \
        if(temp){\
            (&arr)->data = temp; \
        }else{\
            (&arr)->cap -= n;\
        }\
    }\
}while(0);

#define aid_arr_push_cust(arr,v, reallocator) do{\
    if (((&arr)->len+1) >= (&arr)->cap) { \
        aid_arr_incr_cap((arr), 10, reallocator); \
    }\
    (&arr)->data[(&arr)->len++] = v; \
    }while(0);

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



#undef Array

#endif
