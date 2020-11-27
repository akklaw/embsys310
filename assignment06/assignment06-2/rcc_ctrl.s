/*******************************************************************************
File name       : rcc_ctrl.s
Description     : Assembly language function for controlling the user LED
*******************************************************************************/   

    PUBLIC enable_rcc        // Exports symbols to other modules

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
Function Name   : enable_rcc
Description     : - Uses Bit-Band registers at base 0x4200.0000
                    to set GPIOA Output Data Register.
                  - Calls another assembly function delay to insert
                    delay loop

C Prototype     : void enable_rcc(uint32_t port)
                : Where port indicates wich port to enable the clock for
Parameters      : R0: uint32_t port

Return value    : None
*******************************************************************************/  

// Bitband address calculation formula
// (0x42000000+(0x2104C *32) + (port*4))) = 0x1; 
BASE_ADDRESS   EQU 0x42000000
BYTE_OFFSET    EQU 0x2104C

enable_rcc    
    
    MOV     R1, R0               // R1 = R0
    
    MOV     R5, #4               // R5 = 4
    MUL     R2, R1, R5           // R2 = R1 * R5
        
    MOV     R5, #32              // R5 = 32
    LDR     R6, =BYTE_OFFSET     // R6 = 0x2104C 
    MUL     R3, R5, R6           // R3 = 0x420980 = 0x2104C * 32
    
    ADD     R4, R3, #BASE_ADDRESS// R4 = R3 + 0x42000000
    ADD     R4, R4, R2           // R4 = R4 + R2        
    
    LDR     R1, [R4]             // load address of R4 to R1
    MOV     R1, #0x1             // Assign 0x1 to R4
    STR     R1, [R4]             // store address of R1 to R4
        
    BX      LR
    END
