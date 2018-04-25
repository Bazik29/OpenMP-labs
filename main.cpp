#include <iostream>
#include <sstream>
#include <chrono>
#include <stdexcept>
#include <omp.h>

#include "Matrix.h"
#include "functions.h"
#include <iomanip>
#include <cstdlib>
#include <cmath>


double f(double x, double y) {
	return 0;
}

double g(double x, double y) {
	if	(x == 0)
		return 1 - 2 * y;
	if	(x == 1)
		return -1 + 2 * y;
	if	(y == 0)
		return 1 - 2 * x;
	if 	(y == 1)
		return -1 + 2 * x;
	return 0;
}

Matrix calcDirichlet(int N=99, double eps=0.0001) {
	Matrix u_mat(N+2, N+2);
	Matrix f_mat(N, N);
	double h = 1.0 / (N + 1);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			f_mat(i, j) = f((i + 1) * h, (j + 1) * h);
	}

	for (int i = 1; i < N + 1; i++) {
		u_mat(i, 0) = g(i * h, 0);
		u_mat(i, N + 1) = g(i * h, (N + 1) * h);
	}

	for (int j = 0; j < N + 2; j++) {
		u_mat(0, j) = g(0, j * h);
		u_mat(N + 1, j) = g((N + 1) * h, j * h);
	}

	double max;
	int IterCnt = 0;
	do {
		IterCnt++;
		max = 0;
		for (int i = 1; i < N + 1; i++)
			for (int j = 1; j < N + 1; j++) {
				double u0 = u_mat(i, j);
				double t = 0.25 * (u_mat(i-1, j) + u_mat(i+1, j) + u_mat(i, j-1) + u_mat(i, j+1) - h*h*f_mat(i - 1, j - 1));
				u_mat(i, j) = t;
				double d = std::fabs(t - u0);
				if (d >	max) max = d;
			}
	} while (max > eps);
	std::cout << "IterCnt = " << IterCnt << std::endl;
	return u_mat;
}

int main(int argc, char* argv[]) {

	auto startTime = std::chrono::steady_clock::now();

	size_t rows = 100;
	size_t cols = 100;
	if (argc > 1) {
		std::istringstream ss(argv[1]);
		int dim;
		if (!(ss >> dim)) throw std::invalid_argument("Wrong ARGV");
		else {
			rows = dim;
			cols = dim;
		}
	}


	//Matrix A = Matrix::rand(rows, cols);
	//Matrix B = Matrix::eye(rows, cols);
	//Matrix C(rows, cols);

	auto initTime = std::chrono::steady_clock::now();


	Matrix A = calcDirichlet();


	//std::cout << toString(A);




	auto mulTime = std::chrono::steady_clock::now();

	auto initDuration = std::chrono::duration_cast<std::chrono::duration<double>>(initTime - startTime);
	auto mulDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - initTime);
	auto runtimeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - startTime);

	printCSV(omp_get_max_threads(), rows, initDuration.count(), mulDuration.count(), runtimeDuration.count());

	return 0;
}
