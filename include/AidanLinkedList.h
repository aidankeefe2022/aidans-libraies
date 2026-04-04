//
// Created by aidankeefe on 3/15/26.
//

#ifndef AIDAN_LINKED_LIST
#define AIDAN_LINKED_LIST
#include <AidanString.h>
#include <AidanArena.h>
#include <AidanCommon.h>

#ifdef AIDAN_SHORT_NAMES
    #define LinkedList LinkedList
    #define Node LLNode
    #define LLtype LLtype
#else
    #define LinkedList aid_LinkedList
    #define Node aid_LLNode
    #define LLtype aid_LLtype
#endif

typedef struct aid_LLNode Node;

typedef enum aid_LLtype{
    NOT_INIT = 0,
    STRING,
    U64,
    I64,
    F32,
    F64,
    VOIDPTR,
}LLtype;

typedef struct aid_LinkedList LinkedList;

bool aid_reserve(LinkedList* ll, u64 size);
bool aid_push(LinkedList* ll, void* val, LLtype type);
Node aid_pop(LinkedList* ll);
bool aid_free_LL(LinkedList* ll);
Node* aid_head(LinkedList* ll);
bool aid_collect_garbage(struct aid_LinkedList* ll);

#undef LinkedList
#undef Node 
#undef LLtype

#endif //HTTP_ASYNC_STRING_LINKED_LIST_H
