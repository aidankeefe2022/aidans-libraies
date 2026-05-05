# AidanArena Interface

## Types
- `Arena`: linear allocator state (`buffer`, `currentPointer`, `size`)
- `ARENA_STATUS`: `ARENA_OK`, `ARENA_ALLOCATION_ERROR`, `ARENA_CREATION_ERROR`

## API
- `Arena* aid_create_arena(size_t size_in_bytes)`
- `void* aid_arena_alloc(Arena arena[static 1], size_t size, const size_t alignment)`
- `ARENA_STATUS aid_arena_clear(Arena arena[static 1])`
- `ARENA_STATUS aid_arena_free(Arena* arena)`
