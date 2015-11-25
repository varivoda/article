#include <ctime>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include "nk4.h"
#include "nk4_parallel.h"
#include "nk5.h"

int main()
{
    NK4 * nk4 = new NK4(0,1,1);
    double result = 0.0;
    unsigned start_time = clock();
    nk4->run(result);
    unsigned end_time = clock();
    unsigned full_time = end_time - start_time;

    printf("Result : %0.8f \n", result);

    NK4_parallel * nk4_ = new NK4_parallel(0,1,1);
    result = 0.0;
    start_time = clock();
    nk4_->run(result);
    end_time = clock();
    unsigned full_time_par = end_time - start_time;

    
    printf("Result : %0.8f \n", result);
    printf("Time : %0.8f \n", full_time_par/full_time);


//    NK5 * nk5 = new NK5(0,1,1);
//    result = 0.0;
//    start_time = clock();
//    nk5->run(result);
//    end_time = clock();
    
//    printf("Result : %0.8f \n", result);
//    printf("Time : %0.8f \n", double (end_time - start_time)/CLOCKS_PER_SEC);
}
