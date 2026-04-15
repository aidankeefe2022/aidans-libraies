//
// Created by aidankeefe on 3/15/26.
//

#ifndef AIDAN_LINKED_LIST
#define AIDAN_LINKED_LIST
#include "AidanString.h"
#include "AidanArena.h"
#include "AidanCommon.h"

#ifdef AIDAN_SHORT_NAMES
    #define LinkedList LinkedList
    #define Node LLNode
    #define LLtype LLtype
#else
    #define LinkedList aid_LinkedList
    #define Node aid_LLNode
    #define LLtype aid_LLtype
#endif


typedef enum aid_LLtype{
    NOT_INIT = 0,
    STRING,
    U64,
    I64,
    F32,
    F64,
    VOIDPTR,
}LLtype;

typedef struct aid_LLNode{
    enum aid_LLtype type;
    union {
        f32 F32;
        f64 F64;
        i64 I64;
        u64 U64;
        struct aid_string* STRING;
        void* VOIDPTR;
    };
    struct aid_LLNode* next;
    struct aid_LLNode* prev;
}Node;

typedef struct aid_LinkedList{
    u64 size;
    struct aid_LLNode* head;
    struct aid_LLNode* tail;
    u64 num_lost_nodes;
    struct aid_LLNode* LOST_NODES;
}LinkedList;

bool aid_push(LinkedList* ll, void* val, LLtype type);
Node aid_pop(LinkedList* ll);
Node aid_remove_index(LinkedList* ll, i32 idx);
struct aid_LLNode aid_pop_first(struct aid_LinkedList* ll);
bool aid_free_LL(LinkedList* ll);
bool aid_collect_garbage(struct aid_LinkedList* ll);

#undef LinkedList
#undef Node 
#undef LLtype

#endif
