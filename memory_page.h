//
// Created by lsy on 16-7-1.
//

#ifndef MEMORY_PAGE_H
#define MEMORY_PAGE_H

#include "data_type.h"

typedef struct Memory_block{
    u16 size;
    u16 next_index;
}Memory_block;

typedef struct Memory_page{
    u16 size;
    u16 free_index;
    u16 use_index;
}Memory_page;


Memory_page *Memory_page_init(void *memory,u16 size);
void *Memory_page_malloc(Memory_page *page,u16 size);
char Memory_page_free(Memory_page *page,void *space);


#endif //MEMORY_PAGE_H
