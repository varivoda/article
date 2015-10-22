#include "nk4.h"

#define n 4 // число разбиений Ньютона - Котеса

    double NK4::f(double x){
        return x*x;
    }

NK4::NK4(int a, int b, unsigned N) : a(a), b(b), N(N)
{
}

// Newton_Cotes_Integral_Calculation_Simple.cpp : Defines the entry point for the console application.

void NK4::run(double & result){

    //Шаги составного ра-ия и Ньютона - Котеса
    double H = (double)(b - a) / N;
    double h = H / n;

    //Задаем узлы x_l_k
    double x[n + 1][N];
    for (int k = 0; k <= n; k++){
        for (int l = 0; l < N; l++){
            x[k][l] = a + H*l + h*k;
        }
    }

    //Вычисление первой суммы
    double sum_1 = 0.0;
    for (int l = 0; l < N; l++){
        sum_1 += f(x[0][l]) + f(x[n][l]);
    }
    sum_1 *= (7.0) / 90.0;


    //Вычисление второй суммы
    double sum_2 = 0.0;
    for (int l = 0; l < N; l++){
        sum_2 += f(x[1][l]) + f(x[n-1][l]);
    }
    sum_2 *= (32.0) / 90.0;

    //Вычисление третьей суммы
    double sum_3 = 0.0;
    for (int l = 0; l < N; l++){
        sum_3 += f(x[2][l]);
    }
    sum_3 *= 12.0 / 90.0;

    //Получение результата
    result = H*(sum_1 + sum_2 + sum_3);
}

