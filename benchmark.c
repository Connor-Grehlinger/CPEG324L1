/* Benchmars used to test the functionality 
and correctness of partners ISA simulator */

#include "benchmark.h"

// Testing functions:


// Timer implementation

double getTime()
{
    struct timeval timeValue;
    struct timezone timeZone;
    gettimeofday(&timeValue, &timeZone);
    return timeValue.tv_sec + timeValue.tv_usec*1e-6;
    
}

bool initialValueAndPrintTest(Register* r0, Register* r1, Register* r2, Register* r3)
{
    if((!r0->registerValue) && (!r1->registerValue) && (!r2->registerValue) && (!r3->registerValue))
    {
        return true;
    }
    return false;
    // Print instruction functionality determined by viewing console output
}

bool loadingImmediatesTest(Register* r0, Register* r1, Register* r2, Register* r3)
{
    if ((r0->registerValue == -2) &&  (r1->registerValue == 4) && (r2->registerValue == -6) && (r3->registerValue == 3))
    {
        return true;
    }
    return false;
}

bool additionInstructionTest(Register* r0, Register* r1, Register* r2, Register* r3)
{
    return false;
}

bool subtractionInstructionTest(Register* r0, Register* r1, Register* r2, Register* r3)
{
    return false;
}

bool branchingInstructionTest(Register* r0, Register* r1, Register* r2, Register* r3)
{
    if ((r0->registerValue == -8) &&  (r1->registerValue == 7) && (r2->registerValue == -14) && (r3->registerValue == 0))
    {
        return true;
    }
    return false;
}
