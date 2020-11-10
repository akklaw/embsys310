#include <stdio.h>

int main()
{
    // Set a 4 bytes integer to 1
    unsigned int i = 1;
    
    // typecast the 4 bytes integer with a 1 byte pointer
    char *c = (char *)&i;
    
    // check the first byte and dereferencing the 1 byte char pointer
    // if it is positive value in the first byte, system is Little Endian
    // otherwise the system is Big Endian
    if (*c) {
        printf("Little Endian\n");
    } else {
        printf("Big Endian\n");
    }
    
    return 0;
}
