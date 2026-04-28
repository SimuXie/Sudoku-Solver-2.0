#include <stdlib.h>
#include <stdio.h>

#define NO_MEMORY_ERROR "ERROR: Out of memory!\n"

static void errorCheck(void *ptr);

// Malloc wrapper that runs a memory error check.
// Returns a void pointer. Same useage as malloc().
void *myMalloc(size_t size) {
	void *ptr = malloc(size); 
	errorCheck(ptr);
	return ptr;
}

// Realloc wrapper that runs a memory error check.
// Returns a void pointer. Same useage as realloc().
void *myRealloc(void *ptr, size_t size) {
	ptr = realloc(ptr, size); 
	errorCheck(ptr);
	return ptr;
}

void *myCalloc(size_t elementNum, size_t elementSize) {
    void *ptr = calloc(elementNum, elementSize);
	errorCheck(ptr);
    return ptr;
}

static void errorCheck(void *ptr) {
	if (ptr == NULL) {
		fprintf(stderr, NO_MEMORY_ERROR);
		exit(EXIT_FAILURE);
	}
}