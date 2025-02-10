# Week 2

Four steps underneath 'compiling' technically:

- preprocessing: preprocessor directives (e.g. `#include <stdio.h>`, including prototypes of functions), converting those hash lines & prototypes into equivalent lines of code
- compiling: c (after preprocessing header files) => assembly language
- assembling: assembly code => machine code (0 and 1) (that's why Clang names output files 'a.out' by default, for 'assembler output')
- linking: linking the output of assembling of multiple `.c` files (e.g. `hello.c`, `stdio.c`) into a single executable file

decompiling: **reverse engineering** the executable file (machine code) back to the original source code

debugging

- `printf` is your friend, quick but dirty
- debugger: debug50.
  - set breakpoint.
- AI: cs50.ai

Each of types has a finite amount of space allocated to it.

- `int` is 4 bytes, 32bits.
- `float` is 4 bytes.
- `char` is 1 byte.
- `double` is 8 bytes.
- `long` is 8 bytes.
- `bool` is 1 byte. (sort of wasting space!)
- `string` ? byte.

Random Access Memory (RAM).
Memories => Addresses / Locations
Storing information in memory: unit of memory is byte.

integral math vs floating point math: if one float number is included in the calculation, the result will be casted to floating point number.

Array: a sequence of values back to back to back in memory.

If you declare something as a constant, it's commonplace to capitalize it to draw attention to it.

The length of an array in memory is the real length of the array plus one, because the end of the array is always marked by `\0` (`NUL`).

Manipulating memory:

```c

string words[2];
words[0] = "HI!";
words[1] = "BYE!";

printf("%i %i %i %i %i\n", words[0][0], words[0][1], words[0][1], words[0][2], words[0][3], words[0][4]);
```

and the output will be:

```c
72 73 33 0 66
```

The numbers are the ASCII codes of the characters, and `66` is the ASCII code of `B`. So we access the second word by words[0] *illegally* .

## Shorts

### 1. Functions

A black box with a set of 0+ inputs and a single output.

Declaration:

```c
return_type name(argument-list);
```
