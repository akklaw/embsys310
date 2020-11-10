// main.c
#include <assert.h>
#include "stack.h"

int main()
{
    int output;
    int ret = 0;
    
    // case #1 if the stack is empty and pop from the stack
    //
    //Arrange
    stack_init();
    //Act
    ret = stack_pop(&output);
    //Assert
    assert(ret == -1);
    
    // case #2 if the stack is full and push to the stack
    //
    //Arrange
    stack_init();
    //Act
    for(int i = 0; i < STACK_SIZE; i++)
    {
        ret = stack_push(i);
        assert(ret == 0);
    }
    // stack is full now
    ret = stack_push(0); 
    //Assert
    assert(ret == -1);
    
    // case #3 push to and pop from stack, then check for the value.
    //
    //Arrage
    stack_init();
    //Act
    //Push values into the stack up to STACK_SIZE
    for(int i = 0; i < STACK_SIZE; i++)
    {
        ret = stack_push(i);
        // Assert
        assert(ret == 0);
    }
    // #case 4, push when stack is full.
    //Act
    //Push one more, it should be full
    ret = stack_push(99);
    // Assert
    assert(ret == -1);
    
    //POP values from the stack for STACK_SIZE number of times.
    for(int i = STACK_SIZE-1; i >= 0; i--)
    {
        ret = stack_pop(&output);
        // Assert
        assert(ret == 0);
        assert(output == i);
    }
    // #case 5, pop when stack is empty.
    //Act
    //Pop one more, it should be empty
    ret = stack_pop(&output);
    assert(ret == -1);
    
    return 0;
}
