#include <ctime>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include "nk4_parallel.h"
#include "nk5_parallel.h"

int main()
{
    NK4_parallel * nk4_parallel = new NK4_parallel(0,10,1000);
    double result = 0.0;
    unsigned start_time = clock();
    nk4_parallel->run(result);
    unsigned end_time = clock();
    
    printf("Result : %0.8f \n", result);
    printf("Time : %0.8f \n", double(end_time - start_time)/CLOCKS_PER_SEC);

    NK5_parallel * nk5_parallel = new NK5_parallel(0,10,1000);
    result = 0.0;
    start_time = clock();
    nk5_parallel->run(result);
    end_time = clock();
    
    printf("Result : %0.8f \n", result);
    printf("Time : %0.8f \n", double (end_time - start_time)/CLOCKS_PER_SEC);
}
