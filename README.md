*This project has been created as part of the 42 curriculum by ragliga.*

# ft_printf

## Description

**ft_printf** is a re-implementation of the C standard library function `printf()`. The goal of the project is to learn how **variadic functions** work in C, that is, functions that accept a variable number of arguments, through the `<stdarg.h>` macros (`va_list`, `va_start`, `va_arg`, `va_end`).

The project builds a static library, `libftprintf.a`, exposing a single function:

```c
int ft_printf(const char *format, ...);
```

Like the original, it writes to the standard output and returns the number of characters printed (or `-1` if a `write` fails).

### Supported conversions

| Conversion | Description                                        |
|:----------:|----------------------------------------------------|
| `%c`       | A single character                                 |
| `%s`       | A string (prints `(null)` if the pointer is NULL)  |
| `%p`       | A `void *` pointer in hexadecimal (`0x...`, or `(nil)` if NULL) |
| `%d`       | A signed decimal (base 10) number                  |
| `%i`       | A signed integer in base 10                        |
| `%u`       | An unsigned decimal (base 10) number               |
| `%x`       | A number in lowercase hexadecimal (base 16)        |
| `%X`       | A number in uppercase hexadecimal (base 16)        |
| `%%`       | A percent sign                                     |

As required by the subject, the buffer management of the original `printf()` is **not** implemented: each piece of output is written directly with `write(1, ...)`.

### Project structure

```
.
├── Makefile
├── README.md
├── ft_printf.h          # Prototypes and includes
├── ft_printf.c          # Format string parsing and dispatch
├── formats/
│   ├── string.c         # %c, %s
│   ├── integer.c        # %d, %i, %u
│   └── hexadecimal.c    # %p, %x, %X
└── libft/
    ├── Makefile
    └── ft_putnbr.c      # Number printing helpers (signed / unsigned)
```

## Instructions

### Compilation

The `Makefile` compiles everything with `cc -Wall -Wextra -Werror`. It first builds the `libft` sub-library through its own Makefile, then compiles the project and creates `libftprintf.a` at the root of the repository using `ar`.

```bash
make          # Build libftprintf.a
make clean    # Remove object files (project and libft)
make fclean   # Remove object files and libftprintf.a
make re       # Rebuild everything from scratch
```

### Usage

Include the header and link against the library:

```c
#include "ft_printf.h"

int main(void)
{
    int count;

    count = ft_printf("Hello %s! %d + %d = %i, 0x%x, %p, 100%%\n",
            "42", 40, 2, 42, 255, "ptr");
    ft_printf("%d characters printed\n", count);
    return (0);
}
```

```bash
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o test
./test
```

### Testing

The output of `ft_printf` can be compared with the original `printf` by checking both the printed text and the returned value for the same format strings (including edge cases such as `INT_MIN`, `UINT_MAX`, `0`, `NULL` strings and `NULL` pointers).

## Algorithm and data structure

### Overview

`ft_printf` makes a **single pass** over the format string, character by character. No intermediate buffer and no dynamic allocation are needed, so there is nothing to free and no risk of memory leaks.

```
ft_printf
 ├─ va_start
 ├─ while (*format)
 │    └─ print_one
 │         ├─ "%" + valid conversion  → print_next → format_x(va_arg(...))
 │         └─ any other character     → write(1, c, 1)
 └─ va_end
```

### Step by step

1. **Initialization.** `va_start` initializes the `va_list` using the last named parameter (the format string). If the format is `NULL`, the function returns `-1`.
2. **Parsing.** `print_one` looks at the current character. If it is a `%` followed by one of the characters in `"cspdiuxX%"` (checked by `valid_format`), it handles a conversion and advances by two characters. Otherwise it prints the character as is and advances by one.
3. **Dispatch.** `print_next` selects the right handler according to the conversion character, and retrieves the matching argument with `va_arg` using the correct type (`int` for `%c`, `%d`, `%i`; `char *` for `%s`; `void *` for `%p`; `unsigned int` for `%u`, `%x`, `%X`).
4. **Counting.** Each handler returns the number of characters it wrote, or `-1` on error. `ft_printf` accumulates these values and stops immediately (after calling `va_end`) if one of them is `-1`.
5. **Cleanup.** `va_end` is called before returning the total.

### Design choices and justification

- **A `va_list` passed by pointer (`va_list *`).** The same `va_list` has to be advanced by the helper functions (`print_one` → `print_next`). Passing a pointer ensures that every `va_arg` call updates the state shared by the whole parsing, instead of working on a copy.
- **A dispatch function plus one function per conversion family.** Parsing (`ft_printf.c`) is separated from printing (`formats/`). Adding a new conversion only requires adding a handler and one line in `valid_format` and `print_next`, which keeps the code well-structured and extensible (the key advice given in the subject, especially useful if bonuses are added later).
- **Recursion for number printing.** Numbers are printed digit by digit by recursively printing `n / base` before printing `n % base`. Digits are therefore naturally output in the right order, without having to allocate a buffer or reverse a string. The depth of the recursion is bounded by the number of digits (at most 20 for a 64-bit value), so the stack usage is negligible.
- **`ft_putnbr` takes a `long`.** A signed `int` cannot represent `-INT_MIN`. Promoting to `long` before negating handles `INT_MIN` correctly without special-casing it.
- **`%p` uses `unsigned long long`.** A pointer is converted to an unsigned 64-bit integer, printed in base 16 and prefixed with `0x`. A `NULL` pointer prints `(nil)` and a `NULL` string prints `(null)`, which matches the behavior of the glibc `printf` that the project is compared against.
- **Error propagation.** Every `write` result is checked and `-1` is propagated up the call chain, like the original `printf` which returns a negative value on output error.
- **Return value.** The count of printed characters is the sum of the values returned by each `write`, which is exactly what `printf` returns.
- **The library is built with `ar`.** The `libft` objects are first archived into `libft.a`, which is copied to `libftprintf.a`; the `ft_printf` objects are then added with `ar rcs`. The final library therefore contains both parts, and `libtool` is never used. The Makefile only relinks when a source or the header changes.

## Resources

### References

- [Variadic functions in C – GeeksforGeeks](https://www.geeksforgeeks.org/c/variadic-functions-in-c/): explanation of variadic functions, the `<stdarg.h>` macros (`va_list`, `va_start`, `va_arg`, `va_end`) and how to use them.
- `man 3 printf`: reference for the behavior of the original function.
- `man 3 stdarg`: documentation of the variable argument list macros.
- `man 2 write`: documentation of the `write` system call.
- `man 1 ar`: documentation of the archiver used to build the static library.

### Use of AI

AI (Claude) was used in the following ways:

- **Understanding the subject:** to clarify the requirements of the exercise and the concepts involved (variadic functions, how `va_list` works).
- **Tutoring:** as a tutor to explain concepts and guide the reasoning. The implementation of `ft_printf` and of every function of the project was written by the author.
- **Documentation:** to help write and structure this `README.md`.
