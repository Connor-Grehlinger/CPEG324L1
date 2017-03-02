/* Connor Grehlinger, CPEG324 ISA simulator */
#include <stdbool.h>
#include "simulator.h"
#include "benchmark.h"

// Four addressable registers for simualtor, initial value of 0

// Declare pointers to register structs 
static struct Register *r0 = &(struct Register) {.registerValue = 0};
static struct Register *r1 = &(struct Register) {.registerValue = 0};
static struct Register *r2 = &(struct Register) {.registerValue = 0};
static struct Register *r3 = &(struct Register) {.registerValue = 0};

int binaryInstructions[10000];

int main(int argc, char **argv)
{
    /* Test modes:
    0 --> initial value and print test
    1 --> loading immediates test
    2 --> addition instruction test
    3 --> subtraction instruction test
    4 --> register compare and branching test
    */
    
    unsigned int testMode = 4;
    const char* inFile;
    
    switch(testMode)
    {
        case 0:
        inFile = "initial_value_and_print_test.txt";
        break;
        
        case 1:
        inFile = "loading_immediates_test.txt";
        break;
        
        case 2:
        inFile = "addition_instruction_test.txt";
        break;
        
        case 3:
        inFile = "subtraction_instruction_test.txt";
        break;
        
        default:
        inFile = "branching_instruction_test.txt";
        
    }
    
    double startTime = getTime();           // Start simulator timer
    
    int c;
    char *input = argv[1];
    FILE *simulator_input;

    // Get instruction file 
    simulator_input = fopen(inFile, "r");     
    
    unsigned int currentInstruction = 0;    // Instruction as a numerical value
    unsigned int instructionNumber = 0;     // Current instruction number
    
    if (simulator_input == 0)
    {
        perror("Cannot open simulator input file \n");
        exit(-1);
    }
    else
    {
        while ((c = fgetc(simulator_input)) != EOF)     // While input file is valid
        {
            currentInstruction <<= 1;                   // Shift left by 1 is multiplying by 2
            if (c == '1') 
            {
                currentInstruction ^= 1;
            }
            
            if (c == '\n' || feof(simulator_input))     // End of the instruction line
            {
                currentInstruction >>= 1;               // Bring back the correct value
                binaryInstructions[instructionNumber] = currentInstruction;
                currentInstruction = 0;
                instructionNumber++;
            }
        }
        binaryInstructions[instructionNumber] = currentInstruction; // Take care of the last instruction 
    }
    
    unsigned int totalNumberOfInstructions = instructionNumber + 1;
    
    unsigned int instruction_index;
    
    for (instruction_index = 0; instruction_index < totalNumberOfInstructions; instruction_index++)
    {
        if (isAType(binaryInstructions[instruction_index]))
        {
            // A-type instruction 
            if (isAddition(binaryInstructions[instruction_index]))
            {
                // Decode registers for addition operation
                printf("Addition\n");
                unsigned int source1 = source1Reg(binaryInstructions[instruction_index]);
                unsigned int source2 = source2Reg(binaryInstructions[instruction_index]);
                unsigned int dest = destReg(binaryInstructions[instruction_index]);
                
                signed char firstOp = getRegisterContent(source1, r0, r1, r2, r3);
                signed char secondOp = getRegisterContent(source2, r0, r1, r2, r3);
                signed char sum = firstOp + secondOp;
                printf("(r%i: %i) + (r%i: %i) = (r%i: %i) \n", source1, firstOp, source2, secondOp, dest, sum);
                setRegisterContent(dest, sum, r0, r1, r2, r3);
            }
            else
            {
                // Decode registers for subtraction operation 
                printf("Subtraction\n");
                unsigned int source1 = source1Reg(binaryInstructions[instruction_index]);
                unsigned int source2 = source2Reg(binaryInstructions[instruction_index]);
                unsigned int dest = destReg(binaryInstructions[instruction_index]);
                
                signed char firstOp = getRegisterContent(source1, r0, r1, r2, r3);
                signed char secondOp = getRegisterContent(source2, r0, r1, r2, r3);
                signed char diff = firstOp - secondOp;
                printf("(r%i: %i) - (r%i: %i) = (r%i: %i) \n", source1, firstOp, source2, secondOp, dest, diff);
                setRegisterContent(dest, diff, r0, r1, r2, r3);
            }
        }
        else
        {
            // I-type instruction
            if (isLoadI(binaryInstructions[instruction_index]))
            {
                unsigned int targetRegNum = targetReg(binaryInstructions[instruction_index]);
                signed char immediateVal = signExtensionConvert(getImmediateValue(binaryInstructions[instruction_index]));
                printf("Loading immediate value: %i into r%i \n", immediateVal, targetRegNum);
                setRegisterContent(targetRegNum, immediateVal, r0, r1, r2, r3);
            }
            else
            {
                // Branch or print instruction 
                if (!isPrintInstruction(binaryInstructions[instruction_index]))
                {
                    // Branch instruction
                    unsigned int targetRegNum = targetReg(binaryInstructions[instruction_index]);
                    signed char registerValue = getRegisterContent(targetRegNum, r0, r1, r2, r3);
                    
                    printf("Branching based on r%i, whose value is: %i \n", targetRegNum, registerValue);
                    
                    if (registerValue == 0)
                    {
                        if (getImmediateValue(binaryInstructions[instruction_index]) == 1)
                        {
                            printf("Next instruction skipped. \n");
                            instruction_index++;        // skip the next instruction
                        }
                        else if (getImmediateValue(binaryInstructions[instruction_index]) == 2)
                        {
                            printf("Next two instructions skipped. \n");
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
                        printf("Target register value != 0. Branch not taken. \n");
                        continue;
                    }
                }
                
                else
                {
                    // Print instruction 
                    unsigned int targetRegNum = targetReg(binaryInstructions[instruction_index]);
                    signed char printValue = getRegisterContent(targetRegNum, r0, r1, r2, r3);
                    printf("Register $r%i content: %i \n", targetRegNum, printValue);
                }
            }
        }
    }
    
    
    bool testOutcome = false;
    
    switch(testMode)
    {
        case 0:
        testOutcome = initialValueAndPrintTest(r0,r1,r2,r3);
        break;
        
        case 1:
        testOutcome = loadingImmediatesTest(r0,r1,r2,r3);
        break;
        
        case 2:
        testOutcome = additionInstructionTest(r0,r1,r2,r3);
        break;
        
        case 3:
        testOutcome = subtractionInstructionTest(r0,r1,r2,r3);
        break;
        
        default:
        testOutcome = branchingInstructionTest(r0,r1,r2,r3);
        
    }
    
    double endTime = getTime();
    double totalSimTime = startTime - endTime;
    
    printf("Running in test mode %i. Test outcome: %i (1 = pass, 0 = fail).\n", testMode, testOutcome);
    printf("End. Simulator time: %f . Register values: r0 = %i, r1 = %i, r2 = %i, r3 = %i \n", totalSimTime, r0->registerValue,
    r1->registerValue, r2->registerValue, r3->registerValue);
    
    
    return 0;
    
}
