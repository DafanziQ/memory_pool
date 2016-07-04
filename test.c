
#include "data_type.h"
#include "memlib.h"

#include "memory_pool.h"
#include "stdio.h"

extern Memory_pool *__main_pool;


int main(void){
    void *point[10];
    int len = 10;
    pool_init();

    len --;
    point[len] = pool_malloc(7000);
    Memory_pool_print(__main_pool);

    len --;
    point[len] = pool_malloc(7000);
    Memory_pool_print(__main_pool);

    len --;
    point[len] = pool_malloc(7000);
    Memory_pool_print(__main_pool);

    len --;
    point[len] = pool_malloc(7000);
    Memory_pool_print(__main_pool);

    len --;
    point[len] = pool_malloc(12000);
    Memory_pool_print(__main_pool);

    len --;
    point[len] = pool_malloc(7000);
    Memory_pool_print(__main_pool);

    len --;
    point[len] = pool_malloc(7000);
    Memory_pool_print(__main_pool);

    len --;
    point[len] = pool_malloc(7000);
    Memory_pool_print(__main_pool);

    len --;
    point[len] = pool_malloc(7000);
    Memory_pool_print(__main_pool);


    len --;
    point[len] = pool_malloc(12000);
    Memory_pool_print(__main_pool);

    printf("___________+++++++++++++++++++++++++++++++_______\n");
    len = 0;
    while (len < 10){
        if (point[len] == NULL) printf("pointer %d is empty\n",len);
        len ++;
    }

    len = 10;
    while (len --){
        Memory_pool_print(__main_pool);
        printf("start free %d:\n",len);
        if (pool_free(point[len])) printf("free %d error\n",len);
    }
    Memory_pool_print(__main_pool);

extern int free_times;
extern int malloc_times;
    printf("malloc times:%d free times:%d\n",malloc_times,free_times);

    return 0;
}

