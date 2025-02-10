# Week 1

## Lecture

- source code
- machine code
- complier

### hello world

```sh
code hello.c
make hello
./hello
```

- C and python are line-based.
- so we can use `\n` to separate lines.

### header file

- `#include <stdio.h>`: standard i-o library
- library: code that someone else wrote.
- Manual Pages: [manual.cs50.io](https://manual.cs50.io/)

### Format codes

- `%s` for strings
- `%i` for integers
- `%f` for floating point values
- `%c` for characters
- `%lf` for double values
- `%li` for long integers

### Types of variables

- bool
- char
- double
- float: floating point values
- int: integers
- long: long integers
- string

### Conditionals

- a way of making decisions in code.

- Boolean Expression
- if & else

### Variables

- int;
- string;
- char;

- `or`: `||`
- `and`: `&&`

### Loops

- while
- for

### Function

### scope

### Linux

- cd
- cp
- ls
- mkdir
- mv
- rm
- rmdir

### constants

### Type casting

- floating point imprecision

## Shorts

### 1. Data Types and Variables

Unlike many modern languages, C requires that you specify the data type of every variable you create, the first time you use that variable.

- int
    - store integers
    - always take up 4 bytes (32 bits), so limited to 32 bits worth of information.
    - range from $-2^{31} \to 0 \to 2^{31}-1$ (half for negative, half for positive)
- unsigned int: only positive integers. A qualifier. Range from $0 \to 2^{32}-1$.
- char
    - store single characters
    - always take up 1 byte (8 bits)
    - range from $-128 \to 127$
- float
    - store floating point numbers (real numbers)
    - always take up 4 bytes (32 bits)
- double
    - store floating point numbers (real numbers)
    - always take up 8 bytes (64 bits)
    - double precision
- void: like a placeholder for nothing.

Create a variable:

```c
[data type] [variable name];
```

Create multiple variable of the same type:

```c
[data type] [variable name], [variable name], [variable name];
```

This process is called **declaration**.

Assignment:

```c
[variable name] = [value];
```

declaration and assignment together is sometimes called **initialization**.

```c
[data type] [variable name] = [value];
```

### 2. Operators

Arithmetic operators:

- `+`
- `-`
- `*`
- `/`
- `%`, modulus

Boolean expressions:

- every non-zero value is true, zero is false.
- Logical operators:
    - `||`, or
    - `&&`, and
    - `!`, not
- Relational operators:
    - `==`, equal (not assignment `=`)
    - `!=`, not equal
    - `<`, less than
    - `>`, greater than
    - `<=`, less than or equal to
    - `>=`, greater than or equal to

### 3. Conditionals

1. If

```c
if (boolean expression)
{
    // Statement
}
```

2. If-else

```c
if (boolean expression)
{
    // Statement
}
else
{
    // Statement
}
```

3. If-else if-else

```c
if (boolean expression)
{
    // Branch 1
}
else if (boolean expression)
{
    // Branch 2
}
else
{
    // Branch 3
}
```

4. Switch

```c
switch(x)
{
    case 1:
        // Statement 1
        break;
    case 2:
        // Statement 2
        break;
    default:
        // Default Statement
}
```

It's important to use `break` to prevent fallthrough.

5. `?:`

```c
int x = (expression) ? (statement if true) : (statement if false);
```

### 4. Loops

1. `while`

```c
while (boolean expression)
{
    // Statement
}
```

Use when you want a loop to repeat an unknown number of times, and possibly not at all.

2. `do-while`

```c
do
{
    // Statement
} while (boolean expression);
```

This loop will always execute at least once. Use when you want a loop to repeat an unknown number of times, but at least once.

3. `for`

```c
for (start; boolean expression; update)
{
    // Statement
}
```

Use when you want a loop to repeat a discrete number of times.

### 5. Command Line

- `ls`: list
- `pwd`: present working directory
- `cd`: change directory
- `mkdir`: make directory
- `cp <source> <destination>`: copy
- `rm <file>`: remove file
- `mv <source> <destination>`: move
- `chmod`: change mode
- `ln`: create links
- `touch`: create file
- `rmdir`: remove directory
- `man`: manual
- `diff`: compare files
- `clear`: clear the terminal
- `telnet`: check for open ports

### 6. Magic Numbers

Preprocessor directives (macro)

```c
#define NAME REPLACEMENT
```

`#define` is like find and replace.
