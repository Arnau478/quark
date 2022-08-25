# Code styling guide

This document describes the code styling conventions to use for any contribution to this project

## Global

Some conventions are applied to all languages (unless otherwise indicated)
 - 4 space indentation
 - Comments should have a space between the symbol designating it and the comment itself

## C

```c
// Pre-processor directives should generally go in the following order:
// 1. #pragma
// 2. #include
// 3. #define

// Includes with <> should go before includes with ""
#include <stdint.h>
#include "vga.h"

// Pre-processor definitions should be in UPPER_SNAKE_CASE
#define SOME_DEFINE

// All function and variable names should be in lower_snake_case
int add(int a, int b);

// Opening curly brackets ('{') should NOT go in a separate line
int add(int a, int b){
    return a + b;
}

// Asterisks denoting a pointer should be separated from the
// type definition but NOT from the variable/function name
// Examples:
// - char *str    <- This is ok
// - char* str    <- This is NOT ok
// - char * str   <- This is NOT ok
// - char*str     <- This is NOT ok
// This also applies to casts:
// - (char *)str  <- This is ok
// - (char*)str  <- This is NOT ok
void say(char *str){
    printf("You said: %s\n", str);
}

int main(){
    say("Hello");
    // Switch statement should be as shown below
    switch(add(1, 1)){
        case 0:
            // ...
            break;
        case 1:
            // ...
            break;
        case 2:
            // ...
            break;
        default:
            // ...
    }

    return add(3, 4);
}
```

## x86 nasm assembly

```assembly
; Directives such as "bits 32" should be encapsulated with []
[bits 32]

; Everything is written in lowercase
start:
    ; Instructions should be 1-level indented
    mov eax, ebx
```
