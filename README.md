*This project has been created as part of the 42 curriculum by salegari.*

# ft_printf

## Description

**ft_printf** is a recreation of the standard C library function `printf()`.

The goal of this project is to understand how formatted output works internally by implementing a simplified version of `printf` from scratch. The project introduces several important C concepts, including:

* Variadic functions and `va_list`.
* Format string parsing.
* Type-specific argument handling.
* Integer-to-string conversion.
* Number representation in different bases.
* Pointer representation.
* Recursion.
* Static libraries.
* Low-level output using `write()`.

Unlike the original `printf`, this implementation focuses on the conversions required by the 42 `ft_printf` project and does not implement flags, field width, precision, or length modifiers.

The final result of the project is the static library:

```text
libftprintf.a
```

The main function exposed by the library is:

```c
int	ft_printf(const char *format, ...);
```

Like the standard `printf`, `ft_printf` writes formatted output to the standard output and returns the total number of characters printed.

---

## Supported Conversions

The implementation supports the following format specifiers:

| Specifier | Description |
|-----------|-------------|
| `%c` | Prints a single character. |
| `%s` | Prints a string. |
| `%p` | Prints a pointer address in hexadecimal notation. |
| `%d` | Prints a signed decimal integer. |
| `%i` | Prints a signed integer. |
| `%u` | Prints an unsigned decimal integer. |
| `%x` | Prints an unsigned integer in lowercase hexadecimal. |
| `%X` | Prints an unsigned integer in uppercase hexadecimal. |
| `%%` | Prints a literal `%` character. |

Example:

```c
ft_printf("Hello %s! The answer is %d.\n", "world", 42);
```

Output:

```text
Hello world! The answer is 42.
```

---

## Instructions

### Requirements

To compile the project, the following tools are required:

* A C compiler such as `gcc` or `cc`.
* `make`.
* `ar` for creating the static library.
* A Unix/Linux environment or equivalent.

The project is compiled using:

```text
-Wall -Wextra -Werror
```

### Clone the Repository

```bash
git clone https://github.com/sanlega/ft_printf2.git
cd ft_printf2
```

### Compile

Run:

```bash
make
```

This generates:

```text
libftprintf.a
```

and the corresponding object files.

### Remove Object Files

```bash
make clean
```

### Remove Object Files and the Library

```bash
make fclean
```

### Rebuild the Project

```bash
make re
```

This removes all generated files and rebuilds `libftprintf.a` from scratch.

---

## Using ft_printf

To use the library from another C program, include:

```c
#include "ft_printf.h"
```

Example:

```c
#include "ft_printf.h"

int	main(void)
{
	ft_printf("Hello, %s!\n", "42");
	ft_printf("Decimal: %d\n", 42);
	ft_printf("Unsigned: %u\n", 42);
	ft_printf("Hexadecimal: %x\n", 42);
	ft_printf("Uppercase hexadecimal: %X\n", 42);
	return (0);
}
```

First compile the library:

```bash
make
```

Then compile your program and link it with the library:

```bash
cc main.c libftprintf.a -o test_printf
```

Run the executable:

```bash
./test_printf
```

Expected output:

```text
Hello, 42!
Decimal: 42
Unsigned: 42
Hexadecimal: 2a
Uppercase hexadecimal: 2A
```

---

## Project Structure

```text
ft_printf2/
├── Makefile
├── ft_printf.c
├── ft_printf.h
├── ft_intpchar.c
├── ft_intpstr.c
├── ft_intputnbr.c
├── ft_putnbr_base.c
├── ft_putnbr_unsg.c
├── ft_putptr.c
└── utils.c
```

### `ft_printf.c`

Contains the main `ft_printf()` function and the format-string parser.

It is responsible for:

* Initializing the variadic argument list.
* Traversing the format string.
* Detecting `%` conversion sequences.
* Dispatching each conversion to the corresponding helper function.
* Accumulating the number of printed characters.
* Cleaning up the variadic argument list.

### `ft_printf.h`

Contains the function prototypes and the required system headers.

### `ft_intpchar.c`

Prints one character using `write()` and returns the number of characters written.

### `ft_intpstr.c`

Prints a string character by character.

A `NULL` string is represented as:

```text
(null)
```

### `ft_intputnbr.c`

Prints signed decimal integers recursively.

The minimum 32-bit signed integer:

```text
-2147483648
```

is handled explicitly because its positive equivalent cannot be represented by a signed `int`.

### `ft_putnbr_unsg.c`

Prints an unsigned decimal integer using recursive decomposition.

### `ft_putnbr_base.c`

Converts and prints a number using a custom base.

In this project it is used for hexadecimal output with:

```text
0123456789abcdef
```

and:

```text
0123456789ABCDEF
```

### `ft_putptr.c`

Prints memory addresses using hexadecimal representation prefixed with:

```text
0x
```

A null pointer is represented as:

```text
(nil)
```

### `utils.c`

Contains small reusable utility functions required by the project, including `ft_strlen()`.

---

## Algorithm and Data Structure Choices

### Sequential Format String Parsing

The core algorithm scans the format string from left to right.

Conceptually:

```text
while current character exists:
    if it is a normal character:
        print it

    if it is '%':
        inspect the following character
        call the corresponding conversion function
```

This approach was chosen because format strings are inherently sequential.

For a format string containing `n` characters, each character is inspected at most a constant number of times, resulting in a parsing complexity of approximately:

```text
O(n)
```

A more complex parser or intermediate representation would add unnecessary complexity for the limited set of conversions required by the project.

---

### Conversion Dispatch

When the parser encounters `%`, the next character determines which conversion function must be called.

For example:

```c
if (c == 'c')
	return (ft_intpchar(va_arg(args, int)));
if (c == 's')
	return (ft_intpstr(va_arg(args, char *)));
```

Each conversion is handled by a dedicated helper function.

This design separates responsibilities:

```text
ft_printf
    |
    └── format parsing

conversion dispatcher
    |
    └── determines the conversion type

printing functions
    |
    └── convert and output the value
```

Since the number of supported conversion specifiers is small and fixed, a simple sequence of comparisons is appropriate.

The lookup cost can therefore be treated as constant:

```text
O(1)
```

---

### Recursive Integer Conversion

Numeric conversions use recursion.

For example, printing:

```text
1234
```

can be reduced recursively as:

```text
1234
 |
 ├── 123
 |    ├── 12
 |    |    ├── 1
 |    |    └── 2
 |    └── 3
 └── 4
```

At each step:

```c
number / base
```

provides the remaining higher-order digits, while:

```c
number % base
```

provides the current digit.

For decimal representation, the base is `10`.

For hexadecimal representation, the base is `16`.

This algorithm avoids the need for:

* Dynamically allocated strings.
* Temporary buffers.
* Array reversal.
* Additional conversion passes.

For a number `n` represented in base `b`, the recursion depth is:

```text
O(log_b(n))
```

The number of output operations is proportional to the number of digits printed.

---

### Generic Base Conversion

Hexadecimal output uses a string to represent the available digits.

For lowercase hexadecimal:

```c
"0123456789abcdef"
```

For uppercase hexadecimal:

```c
"0123456789ABCDEF"
```

The remainder of a division determines the corresponding character:

```c
base[number % base_length]
```

For example:

```text
42 / 16 = 2 remainder 10
```

Using:

```text
0123456789abcdef
```

index `10` corresponds to:

```text
a
```

Therefore:

```text
42 -> 2a
```

Using a base string allows the same conversion algorithm to be reused for `%x` and `%X`.

Only the character set changes.

---

### Pointer Conversion

Pointers require a wider integer representation than a standard `int`.

The pointer is therefore converted to:

```c
unsigned long
```

before being processed as a hexadecimal number.

The result is prefixed with:

```text
0x
```

For example:

```text
0x7ffee123abcd
```

Using a separate pointer-conversion function keeps pointer handling independent from regular integer hexadecimal conversion.

---

## Data Structure Choices

This project deliberately uses very few data structures.

Formatted output can be processed as a stream, so creating complex intermediate structures would add unnecessary memory usage and implementation complexity.

### `va_list`

The main data structure used by the project is:

```c
va_list
```

provided by `<stdarg.h>`.

`ft_printf()` receives a variable number of arguments:

```c
ft_printf("%s: %d", "value", 42);
```

The function cannot know in advance how many additional arguments will be supplied or what their types will be.

`va_list` provides access to those arguments sequentially.

The standard workflow is:

```c
va_list	args;

va_start(args, format);
...
va_arg(args, type);
...
va_end(args);
```

For example:

```c
va_arg(args, int)
```

retrieves an integer argument, while:

```c
va_arg(args, char *)
```

retrieves a string pointer.

This is the appropriate structure for implementing a variadic function such as `printf`.

---

### Format String as Sequential Input

The format string itself acts as the primary input structure.

Rather than copying or tokenizing the string into another structure, the implementation traverses it directly using an index.

This has several advantages:

* No additional memory allocation.
* No duplicated format string.
* No token array.
* No preprocessing stage.
* Immediate output.
* Simple control flow.

The additional memory complexity of the parser is therefore:

```text
O(1)
```

excluding the recursive call stack used for numeric conversion.

---

### Base Strings

Number systems are represented using strings.

For example:

```c
"0123456789abcdef"
```

This single string defines both:

* The size of the base.
* The mapping between numeric values and output characters.

For hexadecimal:

```text
index:      0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
character:  0 1 2 3 4 5 6 7 8 9 a  b  c  d  e  f
```

This representation makes the base-conversion algorithm generic and reusable.

---

### No Dynamic Memory Allocation

The implementation does not require `malloc()`.

Values are converted directly to output instead of being converted first into dynamically allocated strings.

This has several advantages:

* No allocation failures.
* No memory leaks.
* No ownership issues.
* No cleanup logic.
* Lower memory overhead.
* Simpler execution flow.

The trade-off is that output is written directly and cannot easily be modified afterward.

For the requirements of `ft_printf`, this is an appropriate design.

---

## Complexity

Let:

* `F` be the number of characters in the format string.
* `D` be the total number of characters produced by all conversions.

The overall execution time is approximately:

```text
O(F + D)
```

Normal format characters are processed once, and converted values require work proportional to the number of characters they produce.

The parser itself uses:

```text
O(1)
```

additional memory.

Recursive numeric conversion requires:

```text
O(log_b(n))
```

stack space for a number `n` represented in base `b`.

Since C integer types have a fixed maximum size, the actual recursion depth remains small.

---

## Technical Decisions

### Direct Output Instead of Building Strings

The implementation writes characters directly using:

```c
write(1, &c, 1);
```

instead of first building the final formatted string in memory.

This reduces the need for temporary buffers and avoids dynamic memory allocation.

It also fits the main purpose of the function: producing formatted output directly on standard output.

---

### Helper Functions Return Printed Length

Each output helper returns the number of characters it prints.

For example:

```c
int	ft_intpchar(char c);
```

returns:

```text
1
```

after printing one character.

Recursive functions accumulate these return values:

```c
len += ft_intpnbr(n / 10);
len += ft_intpnbr(n % 10);
```

This allows `ft_printf()` to calculate its final return value naturally while printing the output.

---

### Recursion Instead of Temporary Buffers

Numbers could also be converted by storing digits inside a temporary array and reversing them afterward.

Recursion was chosen instead because it naturally prints the most significant digit first.

For example:

```text
123
```

can be processed conceptually as:

```text
print(12)
print(3)
```

and:

```text
print(12)
```

becomes:

```text
print(1)
print(2)
```

The final output is therefore produced in the correct order without requiring an additional reversal step.

---

### Static Library

The project generates a static library using `ar`.

The final library is:

```text
libftprintf.a
```

This allows `ft_printf` to be linked into other projects without manually compiling every source file each time.

For example:

```bash
cc main.c libftprintf.a -o program
```

---

## Resources

The following documentation and references were useful during the development of the project.

### Documentation

* Linux / POSIX manual pages:
  * https://man7.org/linux/man-pages/

* `printf`:
  * https://man7.org/linux/man-pages/man3/printf.3.html

* Variadic functions and `<stdarg.h>`:
  * https://en.cppreference.com/w/c/variadic
  * https://en.cppreference.com/w/c/variadic/va_start
  * https://en.cppreference.com/w/c/variadic/va_arg
  * https://en.cppreference.com/w/c/variadic/va_end

* `write`:
  * https://man7.org/linux/man-pages/man2/write.2.html

* C reference:
  * https://en.cppreference.com/w/c

* GNU Make:
  * https://www.gnu.org/software/make/manual/

* GNU `ar`:
  * https://sourceware.org/binutils/docs/binutils/ar.html

Manual pages can also be consulted directly from the terminal, for example:

```bash
man 3 printf
man 3 stdarg
man 2 write
man ar
```

These references were used to understand the expected behavior of `printf`, the handling of variadic arguments, and the mechanisms required to build a static library.

### Use of Artificial Intelligence

Artificial intelligence was used as a support tool during the development of the project, mainly for:

* Analyzing error messages produced by testing tools.
* Clarifying the behavior of variadic functions and `va_list`.
* Explaining specific aspects of integer, hexadecimal, and pointer conversion.
* Organizing and writing the documentation in this `README.md`.

AI was used as a learning and debugging support tool. The project implementation was reviewed and understood during the development process.

---

## Author

**salegari**

42 Madrid
