#include <iostream>
#include <omp.h>
#include <math.h>
#include <time.h>
#include <cstdio>
#include <fstream>	

using namespace std;

#define _CRT_SECURE_NO_WARNINGS

//Задаем число потоков
#define THREAD_AMOUNT 4

//using namespace std;

inline double f(double x){
    return sin(x) + pow(x,5);
}

double counting_4_simple(int a, int b, int N){
	// Число разбиений Ньютона - Котеса
	unsigned const n = 4;

	//Шаги составного ра-ия и Ньютона - Котеса
	double const H = (double)(b - a) / N;
	double const h = H / n;

	double sum_1 = 0.0;
	double sum_2 = 0.0;
	double sum_3 = 0.0;

	//Вычисление первой суммы
	for (int l = 0; l < N; l++){
		sum_1 += f(a + l*H) + f(a + H + l*H);
	}

	//Вычисление второй суммы
	for (int l = 0; l < N; l++){
		sum_2 += f(a + h + l*H) + f(a + (n - 1)*h + l*H);
	}

	//Вычисление третьей суммы
	for (int l = 0; l < N; l++){
		sum_3 += f(a + 2 * h + l*H);
	}
	sum_1 *= 7.0 / 90.0;
	sum_2 *= 32.0 / 90.0;
	sum_3 *= 12.0 / 90.0;

	//Получение результата
	return H*(sum_1 + sum_2 + sum_3);
}


double counting_4_parallel(int a, int b, int N){
	// Число разбиений Ньютона - Котеса
	unsigned const n = 4;

	//Шаги составного ра-ия и Ньютона - Котеса
	double const H = (double)(b - a) / N;
	double const h = H / n;

	double sum_1 = 0.0;
	double sum_2 = 0.0;
	double sum_3 = 0.0;

	#pragma omp parallel reduction(+: sum_1,sum_2,sum_3) num_threads(THREAD_AMOUNT)
	{
		//Вычисление первой суммы
		#pragma omp for
		for (int l = 0; l < N; l++){
			sum_1 += f(a + l*H) + f(a + H + l*H);
		}

		//Вычисление второй суммы

		#pragma omp for
		for (int l = 0; l < N; l++){
			sum_2 += f(a + h + l*H) + f(a + (n - 1)*h + l*H);
		}

		//Вычисление третьей суммы

		#pragma omp for
		for (int l = 0; l < N; l++){
			sum_3 += f(a + 2 * h + l*H);
		}
	}

	sum_1 *= 7.0 / 90.0;
	sum_2 *= 32.0 / 90.0;
	sum_3 *= 12.0 / 90.0;

	//Получение результата
	return H*(sum_1 + sum_2 + sum_3);
}

double counting_5_simple(int a, int b, int N){
	// Число разбиений Ньютона - Котеса
	unsigned n = 5;

	//Шаги составного ра-ия и Ньютона - Котеса
	double H = (double)(b - a) / N;
	double h = H / n;

	double sum_1 = 0.0;
	double sum_2 = 0.0;
	double sum_3 = 0.0;

	//Вычисление первой суммы
	for (int l = 0; l < N; l++){
		sum_1 += f(a + H*l) + f(a + 5 * h + l*H);
		//sum_1 += f(x[0][l]) + f(x[5][l]);
	}

	//Вычисление второй суммы
	for (int l = 0; l < N; l++){
		sum_2 += f(a + h + l*H) + f(a + 4 * h + l*H);
		//sum_2 += f(x[1][l]) + f(x[4][l]);
	}

	//Вычисление третьей суммы
	for (int l = 0; l < N; l++){
		sum_3 += f(a + 2 * h + l * H) + f(a + 3 * h + l*H);
		//sum_3 += f(x[2][l]) + f(x[3][l]);
	}
	
	sum_1 *= 19.0 / 288.0;
	sum_2 *= 75.0 / 288.0;
	sum_3 *= 50.0 / 288.0;

	//Получение результата
	return H*(sum_1 + sum_2 + sum_3);
}

double counting_5_parallel(int a, int b, int N){
	// Число разбиений Ньютона - Котеса
	unsigned n = 5;

	//Шаги составного ра-ия и Ньютона - Котеса
	double H = (double)(b - a) / N;
	double h = H / n;
		
	double sum_1 = 0.0;
	double sum_2 = 0.0;
	double sum_3 = 0.0;

	//Начало параллельной области
	#pragma omp parallel reduction(+: sum_1,sum_2,sum_3) num_threads(THREAD_AMOUNT)
	{
		//Вычисление первой суммы
		#pragma omp for
		for (int l = 0; l < N; l++){
			sum_1 += f(a + H*l) + f(a + 5 * h + l*H);
			//sum_1 += f(x[0][l]) + f(x[5][l]);
		}

		//Вычисление второй суммы
		#pragma omp for
		for (int l = 0; l < N; l++){
			sum_2 += f(a + h + l*H) + f(a + 4 * h + l*H);
			//sum_2 += f(x[1][l]) + f(x[4][l]);
		}

		//Вычисление третьей суммы
		#pragma omp for
		for (int l = 0; l < N; l++){
			sum_3 += f(a + 2 * h + l * H) + f(a + 3 * h + l*H);
			//sum_3 += f(x[2][l]) + f(x[3][l]);
		}
	}

	sum_1 *= 19.0 / 288.0;
	sum_2 *= 75.0 / 288.0;
	sum_3 *= 50.0 / 288.0;

	//Получение результата
	return H*(sum_1 + sum_2 + sum_3);
}

int main()
{
	double start_time = 0;
	double end_time = 0;
	double result = 0;
	int N = 10;
	int a = 0;
	int b = 1;

    ofstream fout_nk4;
    fout_nk4.open("nk4_threads_4.txt");
    ofstream fout_nk5;
    fout_nk5.open("nk5_threads_4.txt");

    fout_nk4 << "amount of threads: " << THREAD_AMOUNT << endl;
    fout_nk4 << "N \t" << "coef" << endl;
    fout_nk5 << "amount of threads: " << THREAD_AMOUNT << endl;
    fout_nk5 << "N \t" << "coef" << endl;
	//Counting times in different N
	for (int N = 10; N <= 1000000; N *= 10){
		double repetitions = 100;
		double sum = 0.0;
		for (int i = 0; i < repetitions; ++i){
			start_time = omp_get_wtime();
			result = counting_4_simple(a, b, N);
			end_time = omp_get_wtime();
			sum += end_time - start_time;
		}
		double averageSimple_4_Time = sum / repetitions;

		

		printf("N = %d :\n\n", N);
		printf("n = %d :\n", 4);
		printf("Threads = 1 : %0.8f \n", averageSimple_4_Time);

		sum = 0.0;
		for (int i = 0; i < repetitions; ++i){
			start_time = omp_get_wtime();
			result = counting_4_parallel(a, b, N);
			end_time = omp_get_wtime();
			sum += end_time - start_time;
		}
		double averageParallel_4_Time = sum / repetitions;
		

		printf("Threads = 4 : %0.8f \n", averageParallel_4_Time);
		printf("Coefficient : %0.8f \n\n", averageSimple_4_Time / averageParallel_4_Time);
		fout_nk4 << N << "\t" << averageSimple_4_Time / averageParallel_4_Time << endl;

		sum = 0.0;
		for (int i = 0; i < repetitions; ++i){
			start_time = omp_get_wtime();
			result = counting_5_simple(a, b, N);
			end_time = omp_get_wtime();
			sum += end_time - start_time;
		}
		double averageSimple_5_Time = sum / repetitions;

		printf("n = %d :\n", 5);
		printf("Threads = 1 : %0.8f \n", averageSimple_5_Time);

		sum = 0.0;
		for (int i = 0; i < repetitions; ++i){
			start_time = omp_get_wtime();
			result = counting_5_parallel(0, 1, N);
			end_time = omp_get_wtime();
			sum += end_time - start_time;
		}
		double averageParallel_5_Time = sum / repetitions;

		printf("Threads = 4 : %0.8f \n", averageParallel_5_Time);
		printf("Coefficient : %0.8f \n\n", averageSimple_5_Time / averageParallel_5_Time);
		fout_nk5 << N << "\t" << averageSimple_5_Time / averageParallel_5_Time << endl;
	}
	fout_nk4.close();
	fout_nk5.close();
}



