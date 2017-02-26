/* Connor Grehlinger, CPEG324
C source file for ISA simulator 

Task 2: (Individual Work) Implement the ISA in a simulator written in C 
(or in another programming language of choice). The simulator must accept 
a file that encodes instructions of your ISA in binary (you can use a 
textual representation of the binary code, e.g., “00110010” in the file, 
or use the true binary file format), and print out the result. 
The simulator shouldn’t accept any other input.
*/

#include "simulator.h"

/* Identifies instruction-type, 
returns true for A-type instructions,
false for I-type instructions    */
bool isAType(int instruction)
{
    return !((instruction >> 7) & 1);
}

/* Identifies A-type operation, 
returns true for addition,
false for subtraction    */
bool isAddition(int instruction)
{
    return !((instruction >> 6) % 2);
}

/* Identifies I-type operation,
returns true for load immediate,
false for print or branch   */
bool isLoadI(int instruction)
{
    return !((instruction >> 6) % 2);
}

/* Identifies the target register number    */
int targetReg(int instruction)
{
    int reg1 = (instruction >> 4);
    reg1 &= 0b0011;
    return reg1;
}

/* Identifies source1 register number  */
int source1Reg(int instruction)
{
    int reg1 = (instruction >> 4);
    reg1 &= 0b0011;
    return reg1;
}

/* Identifies source2 register number  */
int source2Reg(int instruction)
{
    int reg2 = (instruction >> 2);
    reg2 &= 0b0011;
    return reg2;
}

/* Identifies destination register number  */
int destReg(int instruction)
{
    int dstReg = instruction;
    dstReg &= 0b0011;
    return dstReg;
}

/* Identifies the immediate value,
immediate values for print operations
must be 0000        */
int immediateValue(int instruction)
{
    return (instruction & 0b1111);
}