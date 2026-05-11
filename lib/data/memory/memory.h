#ifndef MEMORY_H
#define MEMORY_H
#include "types/data_types.h"

void *memset(void *dest, int value, uint32_t count);
void *memcpy(void *dest, const void *src, uint32_t count);

#endif // MEMORY_H
