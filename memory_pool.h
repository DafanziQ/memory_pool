
#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include "data_type.h"
#include "memory_page.h"

typedef struct Memory_page_node{
    Memory_page *page;
    struct Memory_page_node *next;
}Memory_page_node;

typedef struct Memory_overflow_node{
    u32 size;
    void *space;
    struct Memory_overflow_node *next;
}Memory_overflow_node;

typedef struct Memory_pool{
    u16 page_block_max_size;
    Memory_page_node *pages;
    Memory_overflow_node *overflow;
}Memory_pool;


Memory_pool *Memory_pool_init(Memory_pool *pool);
void *Memory_pool_malloc(Memory_pool *pool,u32 size);
char Memory_pool_free(Memory_pool *pool,void *space);

//--------------------------------- test code ------------------------------

void Memory_pool_print(Memory_pool *pool);

#endif //MEMORY_POOL_H