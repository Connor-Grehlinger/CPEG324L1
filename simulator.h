#ifndef SIMULATOR_H_
#define SIMULATOR_H_

// Connor Grehlinger, CPEG324
// Header file for ISA simulator 

#include <stdio.h>
#include <stdlib.h>


struct Register
{
    signed char registerValue;
};


// now you have actual integer binary instructions, you can just (number >> 7) & 1, etc.

/* Identifies instruction-type, 
returns true for A-type instructions,
false for I-type instrctions    */
bool isAType(int instruction);     

/* Identifies A-type operation, 
returns true for addition,
false for subtraction    */
bool isAddition(int instruction);

/* Identifies I-type operation,
returns true for load immediate,
false for print or branch   */
bool isLoadI(int instruction);

/* Identifies the target register number    */
unsigned int targetReg(int instruction);

/* Identifies source1 register number  */
unsigned int source1Reg(int instruction);

/* Identifies source2 register number  */
unsigned int source2Reg(int instruction);

/* Identifies destination register number  */
unsigned int destReg(int instruction);

/* Identifies the immediate value,
immediate values for print operations
must be 0000        */
signed char getImmediateValue(int instruction);

/* Return the content of a specified register */
signed char getRegisterContent(unsigned int registerNumber, Register& r0, Register& r1,
                        Register& r2, Register& r3);

/* Set the content of a specified register    */
void setRegisterContent(unsigned int registerNumber, int result, Register& r0, 
Register& r1, Register& r2, Register& r3);

/* Handles sign-extended immediate values     */
int signExtensionConvert(int immediate);

/* Determines whether an I-type instruction 
with opcode 1 is a print instructon   */
bool isPrintInstruction(int instruction);

#endif