// stack.c

#include "stack.h"


int stackStore[STACK_SIZE+1];

int* topPtr;
int* stackPtr;
int* bottomPtr;

void stack_init()
{
    // the first one do not use and indicates empty stack.
    bottomPtr = &stackStore[0];
    // the last one is the top of the stack.
    topPtr    = &stackStore[STACK_SIZE];
    // stack pointer points to the bottom one to indicate it is empty.
    stackPtr  = bottomPtr;
}

int stack_push(int input)
{
    // Stack is full
    if(stackPtr == topPtr)
        return -1;

    stackPtr++;
    *stackPtr = input;
    
    return 0;
}

int stack_pop(int* output)
{
    // Stack is empty
    if(stackPtr == bottomPtr)
        return -1;
    
    *output = *stackPtr;
    stackPtr--;
    
    return 0;
}

//#endif