// blinking LED1 as Morse code to present my first name "Andrew"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////
// INPUT STRING CONTROL
////////////////////////////////////////////////////////////////
// Modify this string and size to print any combination of alphbets and digitals 
#define MORSE_CODE_STRING "Andrew" // MORSE CODE STRING
#define MORSE_CODE_SIZE    6       // MORSE CODE SIZE
///////////////////////////////////////////////////////////////

#define RCC_BASE           0x40021000    // RCC Base address: 0x40021000
#define RCC_OFFSET         0x4c

#define GPIOA_BASE         0x48000000    // GPIOA Base address: 0x48000000
#define GPIOA_MODER_OFFSET 0x0
#define GPIOA_ODR_OFFSET   0x14

#define RCC_AHB2ENR        (*((unsigned int*)(RCC_BASE   + RCC_OFFSET         ))) 
#define GPIOA_MODER        (*((unsigned int*)(GPIOA_BASE + GPIOA_MODER_OFFSET )))
#define GPIOA_ODR          (*((unsigned int*)(GPIOA_BASE + GPIOA_ODR_OFFSET   )))

//(PA5)
#define ORD5               (1 << 5) 

#define GPIOA_CLOCK_BIT    0x1
#define GPIOA_OUTPUT_BIT   (1 << 11)      // ~GPIOA_OUTPUT_BIT = 0xFFFFF7FF

#define SPACING            180000         // spacing for each unit
#define PART_UNIT          1              // spacing for part unit
#define LETTER_UNIT        3              // spacing for letter unit
#define WORD_UNIT          7              // spacing for word unit

// WARNING: DO NOT CHANGE THESE VALUES
#define DOT                1              // dot
#define DASH               0              // dash
#define DOT_UNIT           1              // dot unit
#define DASH_UNIT          3              // dash unit
// END OF WARNING SECTION

// flag to indicate the LED1 is initialized
volatile int init = 0;

// Enable clock to GPIOA
void enable_clock_to_GPIOA()
{
    RCC_AHB2ENR |= GPIOA_CLOCK_BIT;  // RCC_AHB2ENR: Enable clock to GPIOA
}

// Set GPIOA to output
void set_GPIOA_to_output()
{
    GPIOA_MODER &= ~GPIOA_OUTPUT_BIT; // GPIOA_MODER: Set GPIOA to output
}

// initialize the board to enable LED1 to perform morse code
void init_led1()
{
    enable_clock_to_GPIOA();
    set_GPIOA_to_output();
    
    // set init to 1
    init = 1;
}

// doing unit
// int unit - how many unit for this spacing
void do_unit(int unit)
{
    int unit_count = 0;
    while (unit_count < unit)
    {
        // start the unit
        int counter = 0;
        while (counter < SPACING)
        {
            counter++;
        }
        
        unit_count++;
    }
}

// doing space between part
void part()
{
    do_unit(PART_UNIT);
}

// doing space between letters
void letter()
{
    do_unit(LETTER_UNIT);
}

// doing space between words
void word()
{
    do_unit(WORD_UNIT);
}

// turn led1 on for how many unit
// int dot  - is this a dot? dot = 1, dot = 0 is dash
// int unit - how many unit of the dot or dash
// int last - is this the last part in the letter
void do_led1(int dot, int unit, int last)
{
    // if led1 is not initialize, initialize led1
    if(!init) init_led1();
    
    int unit_count = 0;
    do
    {
        GPIOA_ODR ^= ORD5;      // GPIOB_ODR: Turn LED1 (PA5) on
        // if this is a dot
        if(dot)
        {            
           do_unit(DOT_UNIT);   // one unit
        }
        // if this is a dash
        else
        {
           do_unit(DASH_UNIT);  // three units
        }
        GPIOA_ODR ^= ORD5;      // GPIOB_ODR: Turn LED1 (PA5) off
        
        // increment unit count
        unit_count++;
        
        // add part if necessary        
        if(    (unit_count <  unit)              // add part between dot part
           || ((unit_count == unit) && !last)    // add part if this is not the last part in the letter
          )
        {
            part();
        }
    }
    while(unit_count < unit);
}

// doing dot or mulitple dots
// int unit - how many dot to generate
// bool last - is this the last part in the letter
void dot(int unit, int last)
{
    // this is a dot
    do_led1(DOT, unit, last);
}

// doing dash or mulitple dashs
// int unit - how many dash to generate
// bool last - is this the last part in the letter
void dash(int unit, int last)
{
    // this is a dash
    do_led1(DASH, unit, last);
}


// doing morse code letter
// char c - what morse code to generate for a given letter
void morse_code_letter(char c)
{
    switch(c)
    {
       // alphbets
       case 'A': case 'a': dot(1,0); dash(1,1);                      break;
       case 'B': case 'b': dash(1,0); dot(3,1);                      break;
       case 'C': case 'c': dash(1,0); dot(1,0); dash(1,0); dot(1,1); break;
       case 'D': case 'd': dash(1,0); dot(2,1);                      break;
       case 'E': case 'e': dot(1,1);                                 break;
       case 'F': case 'f': dot(2,0); dash(1,0); dot(1,1);            break;
       case 'G': case 'g': dash(2,0); dot(1,1);                      break;
       case 'H': case 'h': dot(4,1);                                 break;
       case 'I': case 'i': dot(2,1);                                 break;
       case 'J': case 'j': dot(1,0); dash(3,1);                      break;
       case 'K': case 'k': dash(1,0); dot(1,0); dash(1,1);           break;
       case 'L': case 'l': dot(1,0); dash(1,0); dot(2,1);            break;
       case 'M': case 'm': dash(2,1);                                break;
       case 'N': case 'n': dash(1,0); dot(1,1);                      break;
       case 'O': case 'o': dash(3,1);                                break;
       case 'P': case 'p': dot(1,0); dash(2,0); dot(1,1);            break;
       case 'Q': case 'q': dash(2,0); dot(1,0); dash(1,1);           break;
       case 'R': case 'r': dot(1,0); dash(1,0); dot(1,1);            break;
       case 'S': case 's': dot(3,1);                                 break;
       case 'T': case 't': dash(1,1);                                break;
       case 'U': case 'u': dot(2,0); dash(1,1);                      break;
       case 'V': case 'v': dot(3,0); dash(1,1);                      break;
       case 'W': case 'w': dot(1,0); dash(2,1);                      break;
       case 'X': case 'x': dash(1,0); dot(2,0); dash(1,1);           break;
       case 'Y': case 'y': dash(1,0); dot(1,0); dash(2,1);           break;
       case 'Z': case 'z': dash(2,0); dot(2,1);                      break;
       
       // digits
       case '1': dot(1,0); dash(4,1);                      break;
       case '2': dot(2,0); dash(3,1);                      break;
       case '3': dot(3,0); dash(2,1);                      break;
       case '4': dot(4,0); dash(1,1);                      break;
       case '5': dot(5,1);                                 break;
       case '6': dash(1,0); dot(4,1);                      break;
       case '7': dash(2,0); dot(3,1);                      break;
       case '8': dash(3,0); dot(2,1);                      break;
       case '9': dash(4,1); dot(1,1);                      break;
       case '0': dash(5,1);                                break;       
    }
}

// do the Morse Code
// char* s - char pointer to a string
void do_morse_code(char* s)
{
   // loop through the characters
   for(int i = 0; s[i] != '\0' ; i++)
   {
       // if this is a space character, do a word spacing
       if(s[i] == ' ')
       {
           // do word spacing
           word();
       }
       else
       {
          // perform Morse code for a character
          morse_code_letter(s[i]);
          
          // do letter spacing
          letter();
       }
       
   }
}

// initialize my first name to the character array
char* initialize_first_name()
{
    // allocate memory to hold a string
    char* s = (char*) malloc(sizeof(char) * MORSE_CODE_SIZE+1);
    
    // reset all to 0
    memset(s,0,MORSE_CODE_SIZE+1);

    // the last character is null terminated character
    snprintf(s,MORSE_CODE_SIZE+1,"%s",MORSE_CODE_STRING);
    
    return s;
}

int main()
{   
    // allocate memory to initialzie my_first_name
    char* my_first_name = initialize_first_name();
    
    // do Morse Code for my first name
    do_morse_code(my_first_name);
    
    // free up memory before exit
    free(my_first_name);
    
    return 0;    
}
