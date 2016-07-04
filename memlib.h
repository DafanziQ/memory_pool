
#ifndef MEMLIB_H
#define MEMLIB_H

#include "data_type.h"

void pool_init(void);
void *mmy_malloc(u32 size);
void *pool_malloc(u32 size);
void mmy_free(void *space);
char pool_free(void *space);


#endif //MEMLIB_H
