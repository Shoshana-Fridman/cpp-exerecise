#include <cstdio>//for size_t

#include "memoryExplicit.h"


static void* init_memory();

void * const Person::s_pool = init_memory();
void * Person::s_firstFree = s_pool;

static const size_t BLOCK_SIZE = max();
static const size_t SIZE_HEAP = BLOCK_SIZE * 2;

/***************************HELP FUNCTION***************************/

static void* init_memory()
{
    void * memoryHeap = ::operator new (SIZE_HEAP);
std::cout<<"hello"<<std::endl;
    void * ptr = memoryHeap;

    for (; ptr < (char*)memoryHeap + SIZE_HEAP - BLOCK_SIZE; ptr=(char*)ptr + BLOCK_SIZE) {
        //force our block (from its beginning) to point the next block
        *(Person **)ptr = (Person *)ptr + BLOCK_SIZE;
    }

    *(Person**)((char*)ptr + BLOCK_SIZE) = NULL;
    return memoryHeap;
}
/**************************************************************/

void* Person::operator new (std::size_t size)
{
    if(s_firstFree == NULL)
    {
        throw std::bad_alloc();
    }

    void *tmp_firstFree = s_firstFree;
    s_firstFree = (char *)s_firstFree + BLOCK_SIZE;
    return tmp_firstFree;
return NULL;
}

void* Person::operator new (std::size_t size, const std::nothrow_t& nothrow_value)
{
    if(s_firstFree==NULL)
    {
        return  NULL;
    }

    void* tmp_firstFree = s_firstFree;
    s_firstFree = (char *)s_firstFree + BLOCK_SIZE;
    return tmp_firstFree;
}

void Person::operator delete (void* ptr)
{
    void * tmp_firstFree = s_firstFree;
    s_firstFree = (Person *)ptr;
    *(Person **)s_firstFree  = (Person *)tmp_firstFree;
}
