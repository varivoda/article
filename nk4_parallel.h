#ifndef NK4_PARALLEL_H
#define NK4_PARALLEL_H

class NK4_parallel
{
int a;
int b;
unsigned N;
double f(double x);

public:
    NK4_parallel(int a, int b, unsigned N);
    void run(double & result);
};

#endif // NK4_PARALLEL_H
