#ifndef __MEMORYALLOCTION_H__
#define __MEMORYALLOCTION_H__

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct MemoryAllocator MemoryAllocator;

MemoryAllocator* MemoryAllocatorInit(void* memoryPool, size_t size);
void * MemoryAllocatorRelase(MemoryAllocator* allocator);
void * MemoryAllocatorAllocate(MemoryAllocator* allocator, size_t size);
void MemoryAllocatorFree(MemoryAllocator* allocator, void *ptr);
size_t MemoryAllocatorOptimize(MemoryAllocator* allocator);

#endif
