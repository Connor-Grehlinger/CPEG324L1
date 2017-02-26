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
    return 0;
}

/* Identifies destination register number  */
int destReg(int instruction)
{
    return 0;
}


