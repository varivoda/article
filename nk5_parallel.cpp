#include "nk5_parallel.h"
#include <omp.h>
#include <math.h>

//Задаем число потоков
#define THREAD_AMOUNT 2

NK5_parallel::NK5_parallel(int a, int b, unsigned N) : a(a), b(b), N(N)
{
}

double NK5_parallel::f(double x){
	return 1.0/(sqrt(cos(x)*cos(x)) + 1.0/(pow(sin(x),3)));
//	return sin(x) + pow(sqrt(pow(x,2)),3);
//    return sin(x) + pow(x,5);
//    return x*x;
}

void NK5_parallel::run(double & result){
    // Число разбиений Ньютона - Котеса
    unsigned n = 5;
		
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
    #pragma omp parallel reduction(+: sum_1,sum_2,sum_3) num_threads(THREAD_AMOUNT)
    {
		//Вычисление первой суммы
		#pragma omp for
        for (unsigned l = 0; l < N; l++){
			sum_1 += f(x[0][l]) + f(x[5][l]);
		}
			
		//Вычисление второй суммы
		#pragma omp for
		for (unsigned l = 0; l < N; l++){
			sum_2 += f(x[1][l]) + f(x[4][l]);
		}
		
		//Вычисление третьей суммы
		#pragma omp for
		for (unsigned l = 0; l < N; l++){
			sum_3 += f(x[2][l]) + f(x[3][l]);
		}
	}
	sum_1 *= 19.0 / 288.0;
	sum_2 *= 75.0 / 288.0;
	sum_3 *= 50.0 / 288.0;
	
	//Получение результата
	result = H*(sum_1 + sum_2 + sum_3);
}
