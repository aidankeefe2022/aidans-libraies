# AidanString Interface
## Options

```c++
#define AIDAN_SHORT_NAMES 
#include <LibAidan/AidanAidAllocator.h>
```

this provides Api macros with our aid_ prefix.

## Types
- `String` (`aid_String`): `cap`, `length`, `char* chars`
- `str_err`: `STRING_SUCCESS`, `STRING_OVERFLOW`, `STRING_ILLEGAL_ARGUMENT`, `STRING_INCREASE_FAIL`

## API
- `str_err aid_str_incrcease_cap(String* s, u64 incr_size)`
- `str_err aid_str_append_char(String* s, char character)`
- `str_err aid_str_append_int(String* s, i64 num)`
- `String* aid_str_new(Arena* arena, u64 length, char str[length], u64 cap)`
- `str_err aid_str_append_string(String* str1, String* str2)`
- `str_err aid_str_substring(String old[static 1], String new[static 1], u64 start, u64 end)`
- `String* aid_str_concat(Arena* arena, String* str1, String* str2)`
- `int aid_str_replace_char(String* old, char old_char, char new_char)`
- `bool aid_str_cmp(String* str1, String* str2)`
- `str_err aid_str_clear(String* str)`

## Helpers
- `STR_LIT("...")`
- `Q_STR(arena, "...")`
