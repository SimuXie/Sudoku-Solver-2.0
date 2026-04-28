#ifndef MYSTDLIB_H
#define MYSTDLIB_H

#include <stdlib.h>

void *myMalloc(size_t size);
void *myRealloc(void *ptr, size_t size);
void *myCalloc(size_t elementNum, size_t elementSize);

#endif