#include <stdlib.h>
#include "memlib.h"
#include "memory_pool.h"

Memory_pool *__main_pool = NULL;

int free_times = 0;
int malloc_times = 0;

void *mmy_malloc(u32 size){
malloc_times++;
    return malloc(size);
}

void *pool_malloc(u32 size){
    return Memory_pool_malloc(__main_pool,size);
}


void mmy_free(void *space){
    free(space);
    free_times ++;
}

char pool_free(void *space){
    Memory_pool_free(__main_pool,space);
}

void pool_init(void){
    __main_pool = (Memory_pool *)mmy_malloc(sizeof(Memory_pool));
    Memory_pool_init(__main_pool);
}
