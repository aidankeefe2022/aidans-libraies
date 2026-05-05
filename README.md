# Aidan's Libraries (C)

Small C utility library collection.

## Includes
- Arena allocator ([`AidanArena`](docs/interfaces/AidanArena.md))
- Dynamic arrays ([`AidanDynaArray`](docs/interfaces/AidanDynaArray.md))
- Linked list ([`AidanLinkedList`](docs/interfaces/AidanLinkedList.md))
- String utilities ([`AidanString`](docs/interfaces/AidanString.md))
- Aid allocator ([`AidanAidAllocator`](docs/interfaces/AidanAidAllocator.md))
- Common types/macros (`AidanCommon`)

## Run
From repo root:

```bash
./scripts/test_fast.sh
./scripts/build.sh   # installs libAidan.so + headers (uses sudo)
```
