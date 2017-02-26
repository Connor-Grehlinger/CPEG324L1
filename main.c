/* Connor Grehlinger, CPEG324
main.c for ISA simulator 

Task 2: (Individual Work) Implement the ISA in a simulator written in C 
(or in another programming language of choice). The simulator must accept 
a file that encodes instructions of your ISA in binary (you can use a 
textual representation of the binary code, e.g., “00110010” in the file, 
or use the true binary file format), and print out the result. 
The simulator shouldn’t accept any other input.
*/

#include "simulator.h"




// Four addressable registers for simualtor, initial value of 0
Register r0 = {.registerValue = 0};
Register r1 = {.registerValue = 0};
Register r2 = {.registerValue = 0};
Register r3 = {.registerValue = 0};

int binaryInstructions[1000];


int main(int argc, char **argv)
{
    
    int c;
    char *input = argv[1];
    FILE *simulator_input;
    
    simulator_input = fopen("test_input.txt", "r");
    
    unsigned int currentInstruction = 0;    // this is the instruction as a number value
    
    if (simulator_input == 0)
    {
        perror("Cannot open simulator input file \n");
        exit(-1);
    }
    else
    {
        
        unsigned int instructionNumber = 0;
        while ((c = fgetc(simulator_input)) != EOF)
        {
            // check if its the end of the instruction 
            // end of line detection condition: line[len-1] == '\n' || feof(fp)
            
            currentInstruction <<= 1;           // shift by 1 is multiplying by 2
            if (c == '1') 
            {
                currentInstruction ^= 1;
                //printf("Loop test instruction value %i \n", currentInstruction);
            }
            
            if (c == '\n' || feof(simulator_input))    // end of the instruction line
            {
                currentInstruction >>= 1;               // bring back the correct value
                //printf("Hit: currentInstruction = %i \n", currentInstruction);
                //printf("Instruction number = %i \n", instructionNumber);
                binaryInstructions[instructionNumber] = currentInstruction;
                currentInstruction = 0;
                instructionNumber++;
            }
        }
        binaryInstructions[instructionNumber] = currentInstruction;     // take care of the last instruction 
    }
    
    unsigned int totalNumberOfInstructions = instructionNumber;
    
    printf("Test instruction value %i \n", binaryInstructions[0]);
    printf("Test instruction value %i \n", binaryInstructions[1]);
    printf("Test instruction value %i \n", binaryInstructions[2]);
    printf("Test instruction value %i \n", binaryInstructions[3]);
    printf("Test instruction value %i \n", binaryInstructions[4]);

    bool iCodeTest = isAType(binaryInstructions[0]);
    bool iCodeTest2 = isAType(binaryInstructions[2]);
    
    bool opCodeTest = isAddition(binaryInstructions[0]);
    bool opCodeTestN = isAddition(binaryInstructions[1]);
    
    printf("iCodeTest = %i \n", iCodeTest);
    printf("iCodeTest2 = %i \n", iCodeTest2);
    
    printf("opCodeTest = %i \n", opCodeTest);
    printf("opCodeTestN = %i \n", opCodeTestN);

    int reg1Value = destReg(binaryInstructions[0]);
    int reg1Value2 = destReg(binaryInstructions[1]);
    
    printf("source1 register = %i \n", reg1Value);
    printf("source1 register2 = %i \n", reg1Value2);
    
    int imm = immediateValue(binaryInstructions[4]);
    printf("Immediate value = %i \n", imm);
    
    // Have a loop to iterate through all the newly created 
    // instructions in the array of instructions 
    
    unsigned int i;
    for (i = 0; i < totalNumberOfInstructions; i++)
    {
        if (isAType(binaryInstructions[i]))
        {
            
        }
            
    }
    
    return 0;
    
}