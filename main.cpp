// Newton_Cotes_Integral_Calculation_Simple.cpp : Defines the entry point for the console application.
//
#include <ctime>
#include <iostream>

#define N 5 //Составное разбиение
#define n 5 // число разбиений Ньютона - Котеса

int a = 0;
int b = 1;

inline double f(double x){
    return x * x;
}

//для n = 5 и n = 4;

void run(double & result){

    //Шаги составного ра-ия и Ньютона - Котеса
    double H = (double)(b - a) / N;
    double h = H / n;

    //Задаем узлы x_l_k
    double x[n + 1][N + 1];
    for (int k = 0; k <= n; k++){
        for (int l = 0; l <= N; l++){
            x[k][l] = a + H*l + h*k;
        }
    }

    //Вычисление первой суммы
    double sum_1 = 0.0;
    for (int l = 0; l <= N; l++){
        sum_1 += f(x[0][l]) + f(x[5][l]);
    }
    sum_1 *= (19.0) / 288;


    //Вычисление второй суммы
    double sum_2 = 0.0;
    for (int l = 0; l <= N; l++){
        sum_2 += f(x[1][l]) + f(x[4][l]);
    }
    sum_2 *= (75.0) / 288;

    //Вычисление третьей суммы
    double sum_3 = 0.0;
    for (int l = 0; l <= N; l++){
        sum_3 += f(x[2][l]) + f(x[3][l]);
    }
    sum_3 *= (50.0) / 288;

    //Получение результата
    result = H*(sum_1 + sum_2 + sum_3);
}


int main(){
    unsigned start_time = clock();
    double result = 0.0;
    run(result);
    unsigned end_time = clock();
    //Можно переписать через printf
    std::cout << "Result : " << result <<  std::endl;
    std::cout << "Time : " << start_time - end_time << std::endl;
}
