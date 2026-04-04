//
// Created by aidankeefe on 3/15/26.
//
#include <AidanArena.h>
#include <AidanLinkedList.h>

#include <AidanString.h>
#include <AidanCommon.h>
#include <stdarg.h>
#include <assert.h>


static void assign_value(struct aid_LLNode* node, void* val, enum aid_LLtype type){
    node->type = type;
    switch(type){
        case F32:
            node->F32 = *(f32*)val;
            break;
        case F64:
            node->F64 = *(f64*)val;
            break;
        case I64:
            node->I64 = *(i64*)val;
            break;
        case U64:
            node->U64 = *(u64*)val;
            break;
        case STRING:
            node->STRING = (struct aid_string*)val;
            break;
        case VOIDPTR:
            node->VOIDPTR = val;
            break;
        default:
            assert(false);
    }
}

bool aid_push(struct aid_LinkedList* ll, void* val, enum aid_LLtype type){
    if(ll->size){
        struct aid_LLNode* newNode = calloc(1, sizeof(*newNode));
        if (!newNode)
            return false;
        assign_value(newNode, val, type);
        ll->tail->next = newNode;
        newNode->prev = ll->tail;
        ll->tail = ll->tail->next;
        ll->size++;
        return true;
    }
    if(ll->size == 0){
        struct aid_LLNode* newNode = calloc(1, sizeof(*newNode));
        if (!newNode)
            return false;
        assign_value(newNode, val, type);
        ll->head = newNode;
        ll->tail = newNode;
        ll->size++;
        return true;
    }
    return false;
}

struct aid_LLNode* aid_head(struct aid_LinkedList* ll) {
    return ll->head;
}

struct aid_LLNode aid_pop(struct aid_LinkedList* ll){
    struct aid_LLNode node = {0};
    if (!ll->size){
        return node;
    }
    node = *ll->tail;
    node.next = nullptr;
    node.prev = nullptr;
    ll->tail->next = ll->LOST_NODES;
    ll->LOST_NODES = ll->tail;
    ll->num_lost_nodes++;
    ll->size--;
    if (ll->size == 0) {
        ll->head = nullptr;
        ll->tail = nullptr;
    }else {
        ll->tail = ll->tail->prev;
        ll->tail->next = nullptr;
    }

    
#if !defined(MANUAL_COLLECT_LL_GARBAGE)
    if(ll->num_lost_nodes > 30){
        aid_collect_garbage(ll);
    }
#endif

    return node;
}

bool aid_collect_garbage(struct aid_LinkedList* ll) {
    while(ll->LOST_NODES){
        struct aid_LLNode* node = ll->LOST_NODES;
        ll->LOST_NODES = ll->LOST_NODES->next;
        free(node);
    }
    ll->num_lost_nodes = 0;
    return true;
}

bool aid_free_LL(struct aid_LinkedList* ll){
    while(ll->LOST_NODES){
        struct aid_LLNode* node = ll->LOST_NODES;
        ll->LOST_NODES = ll->LOST_NODES->next;
        free(node);
    }
    while(ll->head){
        struct aid_LLNode* node = ll->head;
        ll->head= ll->head->next;
        free(node);
    }

    *ll = (struct aid_LinkedList){0};

    return true;
}
