#include "stack.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static void errorCheck(void *ptr);
static void *myMalloc(size_t size);
static void *myRealloc(void *ptr, size_t size);

static Stack stackExpand(Stack s);

struct stack {
    void **items;
    int top;
    int capacity;
};

Stack StackNew(void) {
    struct stack *s = myMalloc(sizeof(*s));
    s->items = myMalloc(sizeof(void*));
    s->top = -1;
    s->capacity = 1;

    return s;
}

void StackFree(Stack s) {
    free(s->items);
    free(s);
}

int StackGetSize(Stack s) {
    return s->top + 1;
}

bool StackIsEmpty(Stack s) {
    return s->top == -1;
}

void *StackPop(Stack s) {
    return s->items[s->top--];
}

void *StackPeek(Stack s) {
    return s->items[s->top];
}

void StackPush(Stack s, void *item) {
    if (s->top == s->capacity - 1) {
        s = stackExpand(s);
    }
    s->items[++s->top] = item;
}

static Stack stackExpand(Stack s) {
    int newCap = s->capacity * 2;
    s->items = myRealloc(s->items, sizeof(void*) * newCap);
    s->capacity = newCap;

    return s;
}

// Malloc wrapper that runs a memory error check.
// Returns a void pointer. Same useage as malloc(). 
static void *myMalloc(size_t size) {
	void *ptr = malloc(size); 
	errorCheck(ptr);
	return ptr;
}

// Realloc wrapper that runs a memory error check.
// Returns a void pointer. Same useage as realloc().
static void *myRealloc(void *ptr, size_t size) {
	ptr = realloc(ptr, size); 
	errorCheck(ptr);
	return ptr;
}

static void errorCheck(void *ptr) {
	if (ptr == NULL) {
		fprintf(stderr, "error: out of memory\n");
		exit(EXIT_FAILURE);
	}
}