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

