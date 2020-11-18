/*******************************************************************************
File name       : swapCharsAsm.s
Description     : swap two chars
*******************************************************************************/   

    EXTERN PrintString  // PrintString is defined outside this file.
    EXTERN myCstr       // myCstr defined outside this file.
    
    PUBLIC swapCharsAsm // Exports symbols to other modules
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
Function Name   : swapCharsAsm
Description     : Take two chars and swap them
C Prototype     : int swapCharsAsm(charPtr,charPtr)
                : Where charPtr is the pointer to char
Parameters      : R0: charPtrX
                  R1: charPtrY
Return value    : R0
*******************************************************************************/  
  
swapCharsAsm    
    
    MOVS R2, R0         // copy charPtrs X address to R2
    LDRB R3, [R2]       // Assign R2 value (charPtrs X value) to R3 for temporary local variable
    LDRB R0, [R1]       // Assign (CharPtr Y value) to R0 
    STRB R0, [R2]       // Store R0 to Address in R2
    STRB R3, [R1]       // Store R3 tempoary local variable value to address R1    
    MOVS R0, #0         // Set return value to 0 and return R0
    BX LR               // return (with function result in R0)

    END
