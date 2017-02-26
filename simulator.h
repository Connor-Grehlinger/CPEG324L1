#ifndef SIMULATOR_H_
#define SIMULATOR_H_

// Connor Grehlinger, CPEG324
// Header file for ISA simulator 

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// How to implement the simulator?
// need to take in a string of 0s and 1s, decode it and output based on it



struct Register
{
    int registerValue;
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
int targetReg(int instruction);

/* Identifies source1 register number  */
int source1Reg(int instruction);

/* Identifies source2 register number  */
int source2Reg(int instruction);

/* Identifies destination register number  */
int destReg(int instruction);

/* Identifies the immediate value,
immediate values for print operations
must be 0000        */
int immediateValue(int instruction);

#endif