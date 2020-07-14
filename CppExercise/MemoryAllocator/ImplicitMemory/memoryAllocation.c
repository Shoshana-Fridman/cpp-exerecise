#include "memoryAllocation.h"

static const size_t ALIGNMENT = 16;
static const size_t LSD = 1;

struct MemoryAllocator
{
    size_t m_meta_data;
    void *m_memory_pool;
};

/*********************************HELP FUNCTION*********************************************/
static bool IsFinish(MemoryAllocator* allocator,void* start_block)
{
    return ((char*)start_block >=  (char *)allocator->m_memory_pool+allocator->m_meta_data) ? true: false;
}

static bool IsFree(void * block)
{
    return (*(size_t*)block)&LSD?false:true;
}

static bool BlockEnough(MemoryAllocator* allocator, void* start_block, size_t size) {

    if (IsFinish(allocator, (char*)start_block + size + sizeof(size_t)))
    {
        return false;
    }

    if ((*(size_t *) start_block) >= size) {
        return true;
    }

    if(IsFree((char*)start_block+*(size_t*)start_block)){
        (*(size_t *) start_block) = *(size_t *)((char*)start_block + (*(size_t *) start_block));
        BlockEnough(allocator, start_block, size);
    }
    return false;
}

static void AllocateBlock(size_t * block,size_t size)
{
    size_t save = *block;
    *block = size;
    if (save != size)
    {
        *(block + size) = save - size;
    }
    (*block)++;
}

static void FreeBlock(void * ptr)
{
    *(size_t*)ptr^=LSD;
}

static void MergeBloock(void * ptr)
{
    *(size_t*)ptr+=*((char*)ptr+*(size_t*)ptr);
}
/*********************************************************************************/

MemoryAllocator* MemoryAllocatorInit(void* memoryPool, size_t size)
{
    size+=sizeof(size_t);
    MemoryAllocator* heap=(MemoryAllocator*)malloc(sizeof(MemoryAllocator));
    heap->m_meta_data=size;
    *(size_t*)memoryPool=size;
    heap->m_memory_pool=memoryPool;
    return heap;
}

void * MemoryAllocatorRelase(MemoryAllocator* allocator)
{
    MemoryAllocator *keep_alloctor = allocator;
    free(allocator);
    return keep_alloctor->m_memory_pool;
}

void * MemoryAllocatorAllocate(MemoryAllocator* allocator, size_t size)
{
    size_t* cur_block=(size_t*)allocator->m_memory_pool;
    size +=(ALIGNMENT-(size %  ALIGNMENT))%ALIGNMENT;

    while(!IsFinish(allocator, (char *)cur_block + size))
    {
        if(IsFree(cur_block))
        {
            if(BlockEnough(allocator, cur_block, size))
            {
                AllocateBlock(cur_block, size);
                return cur_block+1;
            }
        }
        cur_block+=(*cur_block|LSD)-1;
    }
    return NULL;
}

void MemoryAllocatorFree(MemoryAllocator* allocator, void *ptr)
{
    FreeBlock(ptr);
    if(IsFree((char*)ptr+*(size_t*)ptr))
    {
        MergeBloock(ptr);
    }
}

size_t MemoryAllocatorOptimize(MemoryAllocator* allocator)
{
    size_t* cur_block=(size_t*)allocator->m_memory_pool;
    size_t max=0;

    while(!(IsFinish(allocator, cur_block)))
    {
        BlockEnough(allocator, cur_block, allocator->m_meta_data);

        if(max<*(size_t*)cur_block)
        {
            max=*(size_t*)cur_block;
        }
        cur_block+=(*cur_block|LSD)-1;
    }
    return max;
}
