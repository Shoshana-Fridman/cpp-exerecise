#include "memoryAllocation.h"

#include <stdio.h>

int main()
{
    size_t size=10000;
    void * heap=malloc(size);
    MemoryAllocator* m=MemoryAllocatorInit(heap, size);
    void * tmp=MemoryAllocatorAllocate(m, 100);
    printf("%ld\n", *((size_t*)tmp-1)^1);
    void * tmp1=MemoryAllocatorAllocate(m, 12);
    printf("%ld\n", *((size_t*)tmp1-1)^1);
    void * tmp2=MemoryAllocatorAllocate(m, 14);
    printf("%ld\n", *((size_t*)tmp2-1)^1);
    void * tmp3=MemoryAllocatorAllocate(m,78);
    printf("%ld\n", *((size_t*)tmp3-1)^1);
    MemoryAllocatorFree(m, heap);
    MemoryAllocatorFree(m, heap);
    size_t max=MemoryAllocatorOptimize(m);
    free(heap);
    return 1;
}
