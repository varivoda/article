#ifndef NK5_PARALLEL_H
#define NK5_PARALLEL_H

class NK5_parallel

{
int a;
int b;
unsigned N;
double f(double x);

public:
    NK5_parallel(int a, int b, unsigned N);
    void run(double & result);
};


#endif // NK5_PARALLEL_H
