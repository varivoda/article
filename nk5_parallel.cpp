#include "nk5.h"
#include <omp.h>

NK5::NK5(int a, int b, unsigned N) : a(a), b(b), N(N)
{
}

double NK5::f(double x){
    return x*x;
}

void NK5::run(double & result){
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

    //Вычисление первой суммы
    double sum_1 = 0.0;
    for (unsigned l = 0; l < N; l++){
        sum_1 += f(x[0][l]) + f(x[5][l]);
    }
    sum_1 *= (19.0) / 288;


    //Вычисление второй суммы
    double sum_2 = 0.0;
    for (unsigned l = 0; l < N; l++){
        sum_2 += f(x[1][l]) + f(x[4][l]);
    }
    sum_2 *= (75.0) / 288;

    //Вычисление третьей суммы
    double sum_3 = 0.0;
    for (unsigned l = 0; l < N; l++){
        sum_3 += f(x[2][l]) + f(x[3][l]);
    }
    sum_3 *= (50.0) / 288;

    //Получение результата
    result = H*(sum_1 + sum_2 + sum_3);
}
