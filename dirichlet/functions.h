#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "../matrix/Matrix.h"

#include <sstream>

void benchmarkPrint(size_t dim, double initDuration, double mulDuration, double runtimeDuration);
void printCSV(int threads, size_t dim, double initDuration, double mulDuration, double runtimeDuration);

struct DirichletResult {
	size_t num_threads;
	Matrix surface;
	size_t iterations;
	double runtime;


	DirichletResult(int n, Matrix s, size_t i, double r) : num_threads(n), surface(s), iterations(i), runtime(r) 
	{}

	std::string toStr() {
		std::stringstream ss;

		ss << toString(surface);
		ss << num_threads << "," << iterations << runtime << std::endl;
		return ss.str();
	}
};

Matrix solveDirichletSerial(size_t N=99, double eps=0.0001);
DirichletResult solveDirichlet(size_t N=99, double eps=0.0001);

#endif // __FUNCTIONS_H__
