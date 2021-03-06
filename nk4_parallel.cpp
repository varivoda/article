#include "nk4_parallel.h"
#include <omp.h>
#include <math.h>

#include <cstdio>

//Задаем число потоков
#define THREAD_AMOUNT 2

NK4_parallel::NK4_parallel(int a, int b, unsigned const N) : a(a), b(b), N(N)
{
}

inline double NK4_parallel::f(double x){
	return 1.0/(sqrt(cos(x)*cos(x)) + 1.0/(pow(sin(x),3)));
//	return sin(1.0/pow(1.0/sin(x),5)) + 1.0/pow(1.0/sin(x),3);
//	return sin(x) + pow(sqrt(pow(x,2)),3);
//    return sin(x) + pow(x,5);
//    return x*x;
}

void NK4_parallel::run(double & result){
    // Число разбиений Ньютона - Котеса
    unsigned const n = 4;
	
    //Шаги составного ра-ия и Ньютона - Котеса
    double const H = (double)(b - a) / N;
    double const h = H / n;

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
 //    #pragma omp parallel shared(x) reduction(+: sum_1) num_threads(THREAD_AMOUNT)
 //    {
 //        //Вычисление первой суммы

 //        #pragma omp for
 //        for (unsigned l = 0; l < N; l++){
	// 		sum_1 += f(x[0][l]) + f(x[n][l]);
 //        }
	// }
 //        //Вычисление второй суммы
 //     //   #pragma omp for
 //        for (unsigned l = 0; l < N; l++){
 //            sum_2 += f(x[1][l]) + f(x[n-1][l]);
 //        }
	
 //        //Вычисление третьей суммы
 //      //  #pragma omp for
 //        for (unsigned l = 0; l < N; l++){
 //            sum_3 += f(x[2][l]);
 //        }
 //    //}

    #pragma omp parallel shared(x) reduction(+: sum_1, sum_2, sum_3) num_threads(THREAD_AMOUNT)
    {
        //Вычисление первой суммы
        double x_0 = a;
<<<<<<< HEAD
        double x_n = H + a;
        #pragma omp for
        for (unsigned l = 0; l < N; l++){
            sum_1 += f(x_0) + f(x_n);
            x_0 += H;
            x_n += H;
=======
    	double x_n = H + a;
        #pragma omp for
        for (unsigned l = 0; l < N; l++){
			sum_1 += f(x_0) + f(x_n);
        	x_0 += H;
        	x_n += H;
>>>>>>> 247961238fbe168b2ea1d70fddc70e99b4ebff99
        }
	
        //Вычисление второй суммы
        double x_1 = a + h;
<<<<<<< HEAD
        double x_n1 = (n-1)*h + a;
        #pragma omp for
        for (unsigned l = 0; l < N; l++){
            sum_2 += f(x_1) + f(x_n1);
            x_1 += H;
            x_n1 += H;
        }
	
        //Вычисление третьей суммы

        double x_2 = a + 2*h;
        #pragma omp for
        for (unsigned l = 0; l < N; l++){
            sum_3 += f(x_2);
            x_2 += H;
=======
    double x_n1 = (n-1)*h + a;
       #pragma omp for
        for (unsigned l = 0; l < N; l++){
            sum_2 += f(x_1) + f(x_n1);
        	x_1 += H;
        	x_n1 += H;
        }
	
        //Вычисление третьей суммы
            double x_2 = a + 2*h;
       #pragma omp for
        for (unsigned l = 0; l < N; l++){
           sum_3 += f(x_2);
        x_2 += H;
>>>>>>> 247961238fbe168b2ea1d70fddc70e99b4ebff99
        }
    }
    

    sum_1 *= 7.0 / 90.0;
    sum_2 *= 32.0 / 90.0;
    sum_3 *= 12.0 / 90.0;
	
    //Получение результата
    result = H*(sum_1 + sum_2 + sum_3);
}

