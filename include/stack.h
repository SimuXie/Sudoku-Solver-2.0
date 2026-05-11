#ifndef STACK_H
#define STACK_H

#include "stdbool.h"

typedef struct stack *Stack;

Stack StackNew(void);

void StackFree(Stack s);

int StackGetSize(Stack s);

bool StackIsEmpty(Stack s);

void *StackPop(Stack s);

void *StackPeek(Stack s);

void StackPush(Stack s, void *item);

#endif