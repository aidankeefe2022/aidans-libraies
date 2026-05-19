# AidanLinkedList Interface

## Options

```c++
#define AIDAN_SHORT_NAMES 
#include <LibAidan/AidanAidAllocator.h>
```

this provides Api macros with our aid_ prefix.

## Types
- `LLtype`: `NOT_INIT`, `STRING`, `U64`, `I64`, `F32`, `F64`, `VOIDPTR`
- `Node` (`aid_LLNode`): value union + type + `next`
- `LinkedList` (`aid_LinkedList`): `head`, `tail`, `size`, and internal arena

## API
- `bool aid_push(LinkedList* ll, void* val, LLtype type)`
- `Node aid_pop(LinkedList* ll)`
- `Node aid_remove_index(LinkedList* ll, i32 idx)`
- `Node aid_pop_first(LinkedList* ll)`
- `bool aid_free_LL(LinkedList* ll)`
- `bool aid_collect_garbage(LinkedList* ll)`
