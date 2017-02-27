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
    
    simulator_input = fopen("input.txt", "r");
    
    unsigned int currentInstruction = 0;    // this is the instruction as a number value
    unsigned int instructionNumber = 0;
    if (simulator_input == 0)
    {
        perror("Cannot open simulator input file \n");
        exit(-1);
    }
    else
    {
        
        while ((c = fgetc(simulator_input)) != EOF)
        {
            
            currentInstruction <<= 1;                   // shift left by 1 is multiplying by 2
            if (c == '1') 
            {
                currentInstruction ^= 1;
            }
            
            if (c == '\n' || feof(simulator_input))     // end of the instruction line
            {
                currentInstruction >>= 1;               // bring back the correct value
                binaryInstructions[instructionNumber] = currentInstruction;
                currentInstruction = 0;
                instructionNumber++;
            }
        }
        binaryInstructions[instructionNumber] = currentInstruction;     // take care of the last instruction 
    }
    
    unsigned int totalNumberOfInstructions = instructionNumber + 1;
    
    /*
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
    */
    
    unsigned int instruction_index;
    
    for (instruction_index = 0; instruction_index < totalNumberOfInstructions; instruction_index++)
    {
        if (isAType(binaryInstructions[instruction_index]))
        {
            if (isAddition(binaryInstructions[instruction_index]))
            {
                // decode registers for addition operation
                printf("Hit addition\n");
                unsigned int source1 = source1Reg(binaryInstructions[instruction_index]);
                unsigned int source2 = source2Reg(binaryInstructions[instruction_index]);
                unsigned int dest = destReg(binaryInstructions[instruction_index]);
                
                printf("1st reg# = r%i, 2nd reg# = r%i, dest reg# = r%i \n", source1, source2, dest);
                int firstOp = getRegisterContent(source1, r0, r1, r2, r3);
                int secondOp = getRegisterContent(source2, r0, r1, r2, r3);
                int sum = firstOp + secondOp;
                printf("Sum = %i \n", sum);
                setRegisterContent(dest, sum, r0, r1, r2, r3);
            }
            else
            {
                // decode registers for subtraction operation 
                printf("Hit subtraction\n");
                unsigned int source1 = source1Reg(binaryInstructions[instruction_index]);
                unsigned int source2 = source2Reg(binaryInstructions[instruction_index]);
                unsigned int dest = destReg(binaryInstructions[instruction_index]);
                
                printf("1st reg# = r%i, 2nd reg# = r%i, dest reg# = r%i \n", source1, source2, dest);
                int firstOp = getRegisterContent(source1, r0, r1, r2, r3);
                int secondOp = getRegisterContent(source2, r0, r1, r2, r3);
                int diff = firstOp - secondOp;
                printf("Diff = %i \n", diff);
                setRegisterContent(dest, diff, r0, r1, r2, r3);
            }
        }
        else
        {
            // must be I-type instruction
            if (isLoadI(binaryInstructions[instruction_index]))
            {
                unsigned int targetRegNum = targetReg(binaryInstructions[instruction_index]);
                int immediateVal = signExtensionConvert(getImmediateValue(binaryInstructions[instruction_index]));
                printf("Loading immediate value = %i into r%i \n", immediateVal, targetRegNum);
                setRegisterContent(targetRegNum, immediateVal, r0, r1, r2, r3);
            }
            else
            {
                // must be print or branch instruction 
                if (!isPrintInstruction(binaryInstructions[instruction_index]))
                {
                    // branch instruction
                    unsigned int targetRegNum = targetReg(binaryInstructions[instruction_index]);
                    int registerValue = getRegisterContent(targetRegNum, r0, r1, r2, r3);
                    
                    printf("Branching based on r%i, whose value is: %i \n", targetRegNum, registerValue);
                    
                    if (registerValue == 0)
                    {
                        if (getImmediateValue(binaryInstructions[instruction_index]) == 1)
                        {
                            printf("Branch1, should be no r0 printout. \n");
                            instruction_index++;        // skip the next instruction
                        }
                        else if (getImmediateValue(binaryInstructions[instruction_index]) == 2)
                        {
                            printf("Branch2, should be no r0 or r1 printout. \n");
                            instruction_index+=2;     // skip the next two instructions 
                        }
                        else
                        {
                            perror("Invalid Instruction");
                            exit(-2);
                        }
                    }
                    else
                    {
                        printf("Target register value != 0 \n");
                        continue;
                    }
                }
                
                else
                {
                    // print instruction 
                    unsigned int targetRegNum = targetReg(binaryInstructions[instruction_index]);
                    int printValue = getRegisterContent(targetRegNum, r0, r1, r2, r3);
                    printf("Print executed. Register $r%i content: %i \n", targetRegNum, printValue);
                }
            }
        }
    }
    
    printf("End, register values: r0 = %i, r1 = %i, r2 = %i, r3 = %i \n", r0.registerValue,
    r1.registerValue, r2.registerValue, r3.registerValue);
    
    return 0;
    
}