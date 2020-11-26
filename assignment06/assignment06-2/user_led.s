/*******************************************************************************
File name       : user_led.s
Description     : Assembly language function for controlling the user LED
*******************************************************************************/   

    EXTERN delay                    // delay() is defined outside this file

    PUBLIC control_user_led1        // Exports symbols to other modules

// Code is split into logical sections using the SECTION directive.
// Source: http://ftp.iar.se/WWWfiles/arm/webic/doc/EWARM_AssemblerReference.ENU.pdf
// SECTION  section  :type [:flag] [(align)]
//      The data section is used for declaring initialized data or constants. This data does not change at runtime
//      The bss section is used for declaring variables. The syntax for declaring bss section is -
//      The text section is used for keeping the actual code.

// CODE: Interprets subsequent instructions as Arm or Thumb instructions, 
// depending on the setting of related assembler options.

// NOREORDER (the default mode) starts a new fragment in the section
// with the given name, or a new section if no such section exists.
// REORDER starts a new section with the given name.

// NOROOT means that the section fragment is discarded by the linker if
// no symbols in this section fragment are referred to. Normally, all
// section fragments except startup code and interrupt vectors should
// set this flag.

// The (2) is for the (align)
// The power of two to which the address should be aligned.
// The permitted range is 0 to 8. 
// Code aligned at 4 Bytes.

    SECTION .text:CODE:REORDER:NOROOT(2)
    
    THUMB               // Indicates THUMB code is used
                        // Subsequent instructions are assembled as THUMB instructions
    
/*******************************************************************************
Function Name   : control_user_led1
Description     : - Uses Peripheral registers at base 0x4800.0000
                    to set GPIOA Output Data Register.
                  - Calls another assembly function delay to insert
                    delay loop

C Prototype     : void control_user_led(uint8_t state, uint32_t duration)
                : Where state indicates if LED should be on or off.
Parameters      : R0: uint8_t state
                : R1: uint32_t duration
Return value    : None
*******************************************************************************/  

GPIOA_BASE  EQU 0x48000000
GPIOA_ODR   EQU 0x14
GPIOA_BIT_5 EQU 0x20

control_user_led1    
    MOVS      R2, R0                   // assign state to R2
    CMP       R2, #0                   // R2 -> state == 0
    BNE       .ON                      // if state is not equal to 0, JUMP to ON
    
.OFF:                                  // Turn off LED1
    MOVS      R3, #GPIOA_BASE          // assign  GPIOA_BASE to R3
    ADDS      R3, #GPIOA_ODR           // add     GPIOA_ODR  to R3              
    LDR       R4, [R3]                 // Assign address of R3 to R4
    BICS      R4, R4, #GPIOA_BIT_5     // R4 &= ~GPIOA_BIT_5
    STR       R4, [R3]                 // Store R4 to R3
    CMP       R2, #1                   // setup to jump
    BNE       .DELAY                   // JUMP to DELAY
 
 .ON:                                  // Turn on LED1
    MOVS      R3, #GPIOA_BASE          // assign  GPIOA_BASE to R3
    ADDS      R3, #GPIOA_ODR           // add     GPIOA_ODR  to R3
    LDR       R4, [R3]                 // Load R3 into R4
    ORRS      R4, R4, #GPIOA_BIT_5     // R4 |= GPIOA_BIT_5
    STR       R4, [R3]                 // Store R4 to R3
    CMP       R2, #0                   // setup to jump
    BNE       .DELAY                   // JUMP to DELAY
  
.DELAY:                                // delay branch
    PUSH      {R0, LR}                 // save return R0 and address
    MOVS      R0, R1                   // assign R1 to R0
    BL        delay                    // call delay()   
    MOVS      R4, R1                   // move R1 to R4 // solve the problem of R4 assigns to R1 in main's while loop
    POP       {R0, LR}                 // restore R0 and LR
    
    BX        LR
   
    END
