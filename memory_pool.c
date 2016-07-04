#include "memlib.h"
#include "memory_pool.h"
#include "node_lib.h"
#include "memory_page.h"

#define PAGE_SIZE 20000




#define MEMORY_IN_PAGE(page,space) \
    ((char *)space > (char *)page && (char *)space < ((char *)page + page->size))

Memory_pool *Memory_pool_init(Memory_pool *pool){
    pool->page_block_max_size = PAGE_SIZE / 2;

    pool->pages = mmy_malloc(sizeof(Memory_page_node));
    pool->pages->next = NULL;
    pool->pages->page = NULL;

    pool->overflow = mmy_malloc(sizeof(Memory_overflow_node));
    pool->overflow->space = NULL;
    pool->overflow->next = NULL;
    pool->overflow->size = 0;
    return pool;
}


void *Memory_pool_malloc(Memory_pool *pool, u32 size){
    if (size <= pool->page_block_max_size){
        Memory_page_node *temp;
        void *space;
        LIB_NODE_FOR_EACH(pool->pages,temp){
            if((space = Memory_page_malloc(temp->next->page,size)) != NULL){
                return space;
            }
        }
        temp = (Memory_page_node *)mmy_malloc(sizeof(Memory_page_node));
        temp->page = mmy_malloc(PAGE_SIZE);
        Memory_page_init(temp->page,PAGE_SIZE);
        LIB_NODE_ADD_NODE_NEXT(pool->pages,temp);
        return Memory_page_malloc(temp->page,size);
    }else{
        Memory_overflow_node *otemp;
        otemp = (Memory_overflow_node *)mmy_malloc(sizeof(Memory_overflow_node));
        otemp->size = size;
        otemp->space = mmy_malloc(size);
        LIB_NODE_ADD_NODE_NEXT(pool->overflow,otemp);
        return otemp->space;
    }
}


char Memory_pool_free(Memory_pool *pool,void *space){
    Memory_page_node *temp;
    u16 lenth;
    Memory_page_node *temp1;
    char flag;
    LIB_NODE_FOR_EACH(pool->pages,temp){
        if(MEMORY_IN_PAGE(temp->next->page,space)){
            flag = Memory_page_free(temp->next->page,space);
            if (((Memory_block *)((char *)temp->next->page + temp->next->page->use_index))->next_index == 0){
                mmy_free(temp->next->page);
                LIB_NODE_GET_NODE_NEXT(temp,temp1);
                mmy_free(temp1);
            }
            return flag;
        }
    }
    Memory_overflow_node *otemp;
    Memory_overflow_node *otemp1;
    LIB_NODE_FOR_EACH(pool->overflow,otemp){
        if(otemp->next->space == space){
            LIB_NODE_GET_NODE_NEXT(otemp,otemp1);
            mmy_free(otemp1->space);
            mmy_free(otemp1);
            return 0;
        }
    }
    return 1;
}

void Memory_pool_print(Memory_pool *pool){
#include <stdio.h>
    printf("+++++++++++Memory_pool_print+++++++++++\n");
    Memory_page_node *temp;
    int lenth;
    LIB_NODE_LENTH(pool->pages,temp,lenth);
    printf("pages num:%d\n",lenth);
    LIB_NODE_FOR_EACH(pool->pages,temp){
        printf("%d ",temp->next->page->size);
    }
    Memory_overflow_node *otemp;
    LIB_NODE_LENTH(pool->overflow,otemp,lenth);
    printf("\noverflow num:%d\n",lenth);
    LIB_NODE_FOR_EACH(pool->overflow,otemp){
        printf("%d ",otemp->next->size);
    }
    printf("\n-----------Memory_pool_print-----------\n");
}


















