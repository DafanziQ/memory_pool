//
// Created by lsy on 16-7-1.
//

#include "memory_page.h"

#define ADDR(id) ((Memory_block *)((char *)page + id))
#define ID(addr) ((u16)((char *)addr - (char *)page))

Memory_page *Memory_page_init(void *memory,u16 size){
    Memory_page *page = (Memory_page *)memory;
    Memory_block *free_head = (Memory_block *)((char *)page + sizeof(Memory_page));
    Memory_block *use_head = (Memory_block *)((char *)free_head + sizeof(Memory_block));
    Memory_block *first_block = (Memory_block *)((char *)use_head + sizeof(Memory_block));

    if (size < sizeof(Memory_page) + 3 * sizeof(Memory_block)) return NULL;

    page->size = size;
    page->free_index = ID(free_head);
    page->use_index = ID(use_head);

    free_head->size = 0;
    free_head->next_index = ID(first_block);

    use_head->size = 0;
    use_head->next_index = 0;

    first_block->size = size - (sizeof(Memory_page) + 3 * sizeof(Memory_block));
    first_block->next_index = 0;

    return page;
}


void *Memory_page_malloc(Memory_page *page,u16 size){
    Memory_block *temp = ADDR(page->free_index);
    Memory_block *wait_to_use;
    Memory_block *next_free_block;
    while(temp->next_index != 0){
        if ((ADDR(temp->next_index))->size >= size){
            wait_to_use = ADDR(temp->next_index);
            if ((ADDR(temp->next_index))->size > size + sizeof(Memory_block)){
                // divide the block
                next_free_block = (Memory_block *)((char *)wait_to_use + sizeof(Memory_block) + size);
                next_free_block->next_index = wait_to_use->next_index;
                next_free_block->size = wait_to_use->size - (size + sizeof(Memory_block));
                temp->next_index = ID(next_free_block);
                wait_to_use->size = size;
            }else{
                temp->next_index = wait_to_use->next_index;
            }
            // put it into use
            wait_to_use->next_index = (ADDR(page->use_index))->next_index;
            (ADDR(page->use_index))->next_index = ID(wait_to_use);
            return (void *)((char *)wait_to_use + sizeof(Memory_block));
        }else temp = ADDR(temp->next_index);
    }
    return NULL;
}


char Memory_page_free(Memory_page *page,void *space){
    Memory_block *temp = ADDR(page->use_index);
    Memory_block *wait_to_free;
    while(temp->next_index != 0){
        if ((char *)ADDR(temp->next_index) + sizeof(Memory_block) == (char *)space){
            wait_to_free = ADDR(temp->next_index);
            temp->next_index = wait_to_free->next_index;
            // put wait_to_free to free
            temp = ADDR(page->free_index);
            while(temp->next_index != 0){
                if (temp < wait_to_free && wait_to_free < ADDR(temp->next_index)){
                    wait_to_free->next_index = temp->next_index;
                    temp->next_index = ID(wait_to_free);
                    // bind two next block
                    if (((char *)temp) + sizeof(Memory_block) + temp->size == (char *)wait_to_free){
                        temp->size += wait_to_free->size + sizeof(Memory_block);
                        temp->next_index = wait_to_free->next_index;
                    }
                    if (((char *)wait_to_free) + sizeof(Memory_block) + wait_to_free->size == (char *)(ADDR(wait_to_free->next_index))){
                        wait_to_free->size += (ADDR(wait_to_free->next_index))->size + sizeof(Memory_block);
                        wait_to_free->next_index = (ADDR(wait_to_free->next_index))->next_index;
                    }
                    return 0;
                }else temp = ADDR(temp->next_index);
            }
        }else temp = ADDR(temp->next_index);
    }
    return 1;
}







