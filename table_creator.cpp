#include <ctime>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include "nk4.h"
#include "nk5.h"
#include "nk4_parallel.h"
#include "nk5_parallel.h"
#include <fstream>
using namespace std;

int main()
{
    const int N = 100000; // максимальное количество разбиений
    const int M = 1; // сколько поторов для усреднения
    const int a = 0;
    const int b = 100;
    const int THREAD_AMOUNT = 4;



    double result = 0.0;
    unsigned start_time = 0;
    unsigned end_time = 0;
    unsigned full_time = 0; // полное время за M повторов в послед
    unsigned full_time_parallel = 0;  // полное воемя за M повторов в паралл


    // Ньютон_Котес для 4

    //у меня файл создает в своей хитрой дир, поэтому не знаю где он у тебя появится
    ofstream fout;
    fout.open("nk4.txt");

    fout << "amount of threads: " << THREAD_AMOUNT << endl;
    fout << "N \t" << "coef" << endl;

    // конечно каждый раз содавать новый экземляр, но некогда переписывать)
    for (int n = 100000; n <= N; n += 10000)
    {
        NK4 * nk4 = new NK4(a,b,n);
        NK4_parallel * nk4_parallel = new NK4_parallel(a,b,n);

        // блок для послед вычисл
        start_time = clock();
        for(int i = 0; i < M; i++)
        {
            nk4->run(result);
        }
        end_time = clock();
        full_time = (end_time - start_time);

        //блок ля паралл вычисления
        start_time = clock();
        for(int i = 0; i < M; i++)
        {
            nk4_parallel->run(result);
        }
        end_time = clock();
        full_time_parallel = (end_time - start_time);

        fout << n << "\t" << (double)full_time/(double)full_time_parallel << endl;

        delete nk4;
        delete nk4_parallel;
    }

    fout.close();

    // Ньютон_Котес для 5


    fout.open("nk5.txt");

    fout << "amount of threads: " << THREAD_AMOUNT << endl;
    fout << "N \t" << "coef" << endl;

    // конечно пизд каждый раз содавать новый экземляр, но некогда переписывать)
    for (int n = 100000; n <= N; n += 50)
    {
        NK5 * nk5 = new NK5(a,b,n);
        NK5_parallel * nk5_parallel = new NK5_parallel(a,b,n);

        // блок для послед вычисл
        start_time = clock();
        for(int i = 0; i < M; i++)
        {
            nk5->run(result);
        }
        end_time = clock();
        full_time = (end_time - start_time);

        //блок ля паралл вычисления
        start_time = clock();
        for(int i = 0; i < M; i++)
        {
            nk5_parallel->run(result);
        }
        end_time = clock();
        full_time_parallel = (end_time - start_time);

        fout << n << "\t" << (double)full_time/(double)full_time_parallel << endl;

        delete nk5;
        delete nk5_parallel;
    }

    fout.close();

    return 0;
}
