#pragma once

#include <stddef.h>

#define ALLOC_START (void *)0x1000

void *kmalloc(size_t size);
// TODO: void kfree(void *ptr);
void *kcalloc(size_t count, size_t size);
