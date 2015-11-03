#include "nk4_parallel.h"
#include <omp.h>
#include <math.h>

//Задаем число потоков
#define THREAD_AMOUNT 4

NK4_parallel::NK4_parallel(int a, int b, unsigned N) : a(a), b(b), N(N)
{
}

double NK4_parallel::f(double x){
    return sin(x) + pow(x,5);
//    return x*x;
}

void NK4_parallel::run(double & result){
    // Число разбиений Ньютона - Котеса
    unsigned n = 4;
	
    //Шаги составного ра-ия и Ньютона - Котеса
    double H = (double)(b - a) / N;
    double h = H / n;

    //Задаем узлы x_l_k
    double x[n + 1][N];
    for (unsigned k = 0; k <= n; k++){
        for (unsigned l = 0; l < N; l++){
            x[k][l] = a + H*l + h*k;
        }
    }
    
    double sum_1 = 0.0;
    double sum_2 = 0.0;
    double sum_3 = 0.0;
    
    //Начало параллельной области
    #pragma omp parallel num_threads(THREAD_AMOUNT)
    {
        //Вычисление первой суммы
        #pragma omp for
        for (unsigned l = 0; l < N; l++){
            sum_1 += f(x[0][l]) + f(x[n][l]);
        }
	
        //Вычисление второй суммы
        #pragma omp for
        for (unsigned l = 0; l < N; l++){
            sum_2 += f(x[1][l]) + f(x[n-1][l]);
        }
	
        //Вычисление третьей суммы
        #pragma omp for
        for (unsigned l = 0; l < N; l++){
            sum_3 += f(x[2][l]);
        }
    }
    sum_1 *= 7.0 / 90.0;
    sum_2 *= 32.0 / 90.0;
    sum_3 *= 12.0 / 90.0;
	
    //Получение результата
    result = H*(sum_1 + sum_2 + sum_3);
}

