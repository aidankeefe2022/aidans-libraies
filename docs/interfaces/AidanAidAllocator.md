# AidanAidAllocator Interface

## Options

```c++
#define AIDAN_SHORT_NAMES 
#include <LibAidan/AidanAidAllocator.h>
```

this provides Api macros with our aid_ prefix.

## Types
- `AidAllocator_t` (`aid_AidAllocator`): tracked allocations + free-list backed allocator

## API
- `void* aid_AidAlloc(AidAllocator_t* a, size_t size)`
- `bool aid_AidFreePtr(AidAllocator_t* a, void* ptr)`
- `void aid_AidReleaseAll(AidAllocator_t* a)`
- `void* aid_AidRealloc(AidAllocator_t* a, void* ptr, size_t size)`
