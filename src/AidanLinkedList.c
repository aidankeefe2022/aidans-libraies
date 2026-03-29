//
// Created by aidankeefe on 3/15/26.
//
#include <AidanLinkedList.h>

#include <AidanString.h>
#include <AidanCommon.h>
#include <stdarg.h>
#include <assert.h>

struct aid_LinkedList{
    enum aid_LLtype type;
    u64 size;
    u64 cap;
    struct aid_LLNode* head;
    struct aid_LLNode* tail;
    u64 num_lost_nodes;
    struct aid_LLNode* LOST_NODES;
};

struct aid_LLNode{
    union{
        f32 F32;
        f64 F64;
        i64 I64;
        u64 U64;
        struct aid_String* STRING;
        void* VOIDPTR;
    }val;
    struct aid_LLNode* next;
    struct aid_LLNode* prev;
};

bool aid_reserve(struct aid_LinkedList* ll, u64 size){
    struct aid_LLNode* newNodeList = calloc(sizeof(*newNodeList), size);
    if (!newNodeList){
        return false;
    }
    ll->cap += size;
    while(size--){
        if (ll->size == 0) {
            ll->tail = newNodeList;
            ll->head = newNodeList;
        }else {
            ll->tail->next = newNodeList;
            ll->tail = newNodeList;
        }
        newNodeList++;
    }
    return true;
}

static void assign_value(struct aid_LLNode* node, void* val, enum aid_LLtype type){
    switch(type){
        case F32:
            node->val.F32 = *(f32*)val;
            break;
        case F64:
            node->val.F64 = *(f64*)val;
            break;
        case I64:
            node->val.I64 = *(i64*)val;
            break;
        case U64:
            node->val.U64 = *(u64*)val;
            break;
        case STRING:
            node->val.STRING = (struct aid_String*)val;
            break;
        case VOIDPTR:
            node->val.VOIDPTR = val;
            break;
        default:
            assert(false);
    }
}

bool aid_push(struct aid_LinkedList* ll, void* val, enum aid_LLtype type){
    if(ll->type == NOT_INIT){
        assert(type);
        ll->type = type;
    }
    if (ll->type != type && type){
        return false;
    }

    if (ll->cap > ll->size){
        assign_value(ll->tail->next, val, ll->type);
        ll->tail = ll->tail->next;
        ll->size++;
        return true;
    }
    if(ll->size){
        struct aid_LLNode* newNode = calloc(1, sizeof(*newNode));
        if (!newNode)
            return false;
        assign_value(newNode, val, ll->type);
        ll->tail->next = newNode;
        ll->tail = ll->tail->next;
        ll->size++;
        ll->cap++;
        return true;
    }
    if(ll->size == 0){
        struct aid_LLNode* newNode = calloc(1, sizeof(*newNode));
        if (!newNode)
            return false;
        assign_value(newNode, val, ll->type);
        ll->head = newNode;
        ll->tail = newNode;
        ll->head->next = ll->tail;
        ll->tail->prev = ll->head;
        ll->size++;
        ll->cap++;
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
    node.val = ll->tail->val;
    ll->tail->next = ll->LOST_NODES;
    ll->LOST_NODES = ll->tail;
    ll->size--;
    ll->cap--;
    if (ll->size == 0) {
        ll->head = nullptr;
        ll->tail = nullptr;
    }else {
        ll->tail = ll->tail->prev;
    }
    return node;
}

bool aid_collect_garbage(struct aid_LinkedList* ll) {
    while(ll->LOST_NODES){
        struct aid_LLNode* node = ll->LOST_NODES;
        ll->LOST_NODES = ll->LOST_NODES->next;
        free(node);
    }
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
