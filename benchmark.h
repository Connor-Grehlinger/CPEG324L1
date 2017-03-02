#ifndef BENCHMARK_H_
#define BENCHMARK_H_

/* Benchmars used to test the functionality 
and correctness of partners ISA simulator */

#include <sys/time.h>
#include <sys/resource.h>
#include "simulator.h"

/* Timer for benchmarking   */
double getTime();

bool initialValueAndPrintTest(Register* r0, Register* r1, Register* r2, Register* r3);

bool loadingImmediatesTest(Register* r0, Register* r1, Register* r2, Register* r3);

bool additionInstructionTest(Register* r0, Register* r1, Register* r2, Register* r3);

bool subtractionInstructionTest(Register* r0, Register* r1, Register* r2, Register* r3);

bool branchingInstructionTest(Register* r0, Register* r1, Register* r2, Register* r3);

#endif
