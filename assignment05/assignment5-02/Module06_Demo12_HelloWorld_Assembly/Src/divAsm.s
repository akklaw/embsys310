/*******************************************************************************
File name       : divAsm.s
Description     : Assembly language function for divide by 2
*******************************************************************************/   

    EXTERN PrintString  // PrintString is defined outside this file.
    EXTERN myCstr       // myCstr defined outside this file.
    
    PUBLIC divAsm       // Exports symbols to other modules
                        // Making sqrAsm available to other modules.

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
Function Name   : divAsm
Description     : Take an input argument and divide it by 2
                  and return the result
C Prototype     : int divAsm(val)
                : Where val is the value to be divided by 2
Parameters      : R0: integer val
Return value    : R0
*******************************************************************************/  
  
divAsm
    PUSH {R0,LR}        // save the input argument and return address
    LDR R0,=myCstr      // load (global) address of address of string into R0
    LDR R0,[R0]         // load address of string into R0
    BL  PrintString     // call PrintString to print the string
    POP {R0,LR}         // Restore R0 and LR
    MOV R1, R0          // Copy R0 value to R1
    ASR R0, R1, #1      // R0 = R1 >> 1, shift right by 1 is divided by 2
    BX LR               // return (with function result in R0)

    END
