all:
	g++ -fopenmp runner.cpp nk4.h nk5.h nk4_parallel.cpp nk5_parallel.cpp -o Program
