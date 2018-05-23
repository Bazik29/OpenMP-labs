#include "functions.h"

#include "condition.h"

#include <iostream>
#include <cmath>
#include <chrono>
#include <omp.h>


using std::fabs;
using std::cout;
using std::endl;

void benchmarkPrint(size_t dim, double initDuration, double mulDuration, double runtimeDuration) {
	std::cout.setf(std::ios::fixed);
	std::cout.precision(6);
	std::cout << "║ " << dim << "\t" << initDuration << "\t" << mulDuration << "\t" << runtimeDuration << "\t" << "║" << std::endl;
}

void printCSV(int threads, size_t dim, double initDuration, double mulDuration, double runtimeDuration) {
	cout << threads << "," << dim << "," << initDuration << "," << mulDuration << "," << runtimeDuration << endl;
}

void printCSV_dir(int threads, size_t dim, double eps, size_t IterCnt, double runtimeDuration) {
	cout << threads << "," << dim << "," << eps << "," << IterCnt << runtimeDuration << endl;
}

Matrix solveDirichletSerial(size_t N, double eps) {
	Matrix u_mat(N+2, N+2);
	Matrix f_mat(N, N);
	double h = 1.0 / (N + 1);

	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++)
			f_mat(i, j) = f((i + 1) * h, (j + 1) * h);
	}

	for (size_t i = 1; i < N + 1; i++) {
		u_mat(i, 0) = g(i * h, 0);
		u_mat(i, N + 1) = g(i * h, (N + 1) * h);
	}

	for (size_t j = 0; j < N + 2; j++) {
		u_mat(0, j) = g(0, j * h);
		u_mat(N + 1, j) = g((N + 1) * h, j * h);
	}

	double max = 0;
	size_t IterCnt = 0;
	do {
		IterCnt++;
		max = 0;
		for (size_t i = 1; i < N + 1; i++)
			for (size_t j = 1; j < N + 1; j++) {
				double u0 = u_mat(i, j);
				u_mat(i, j) = 0.25 * (u_mat(i-1, j) + u_mat(i+1, j) + u_mat(i, j-1) + u_mat(i, j+1) - h*h*f_mat(i - 1, j - 1));
				double d = fabs(u_mat(i, j) - u0);
				if (d >	max) max = d;
			}
	} while (max > eps);
	//cout << "IterCnt = " << IterCnt << endl;
	return u_mat;
}

DirichletResult solveDirichlet(size_t N,  double eps) {
	auto startTime = std::chrono::steady_clock::now();
	
	Matrix u_mat(N+2,  N+2);
	Matrix f_mat(N,  N);

	double h = 1.0 / (N + 1);

	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++)
			f_mat(i,  j) = f((i + 1) * h,  (j + 1) * h);
	}

	for (size_t i = 1; i < N + 1; i++) {
		u_mat(i,  0) = g(i * h,  0);
		u_mat(i,  N + 1) = g(i * h,  (N + 1) * h);
	}

	for (size_t j = 0; j < N + 2; j++) {
		u_mat(0,  j) = g(0,  j * h);
		u_mat(N + 1,  j) = g((N + 1) * h,  j * h);
	}

	double max, u0, d;
	size_t j, iterations = 0;
	std::vector<double> mx(N);
	do
	{
		iterations++;
		// нарастание волны (k - длина фронта волны)
		for (size_t k = 1; k < N+1; k++) {
			mx[k] = 0;
			#pragma omp parallel for shared(u_mat, N, max) private(j, u0, d) schedule(static, 1)
			for (size_t i = 1; i < k+1; i++) {
				j = k + 1 - i;
				u0 = u_mat(i, j);
				u_mat(i, j) = 0.25 * (u_mat(i-1, j) +u_mat(i+1, j) + u_mat(i, j-1) + u_mat(i, j+1) - h*h*f_mat(i-1, j-1));
				d = fabs(u_mat(i, j) - u0);
				if (d > mx[i]) mx[i] = d;
			}
		}
		for (size_t k = N-1; k > 0; k--) {
			#pragma omp parallel for shared(u_mat, N, max) private(j, u0, d) schedule(static, 1)
			for (size_t i = N-k+1; i < N+1; i++){
				j = 2*N - k - i + 1;
				u0 = u_mat(i, j);
				u_mat(i, j) = 0.25 * (u_mat(i-1, j) +u_mat(i+1, j) + u_mat(i, j-1) + u_mat(i, j+1) - h*h*f_mat(i-1, j-1));
				d = std::fabs(u_mat(i, j) - u0);
				if (d > mx[i]) mx[i] = d;				
			}
		}

		max = 0;
		for (size_t i = 1; i < N+1; i++) {
			if (mx[i] > max) max = mx[i];
		}
	} while (max > eps);

	auto runtime = std::chrono::steady_clock::now();
	auto runtimeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(runtime - startTime);

	DirichletResult result(omp_get_max_threads(), u_mat, iterations, runtimeDuration.count());
	return result;
}
