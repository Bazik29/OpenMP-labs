#include "Matrix.h"

#include <omp.h>
#include <random>
#include <chrono>
#include <stdexcept>
#include <sstream>


std::vector<double> randVector(size_t size) {
	std::vector<double> result(size);
	#pragma omp parallel shared(result)
	{
		std::random_device rd;
		std::mt19937_64 gen(rd());
		std::uniform_real_distribution<double> dis(1.0, 2.0);

		#pragma omp for schedule(static)
		for (size_t i = 0; i < size; i++)
			result[i] = dis(gen);
	}
	return result;
}

Matrix mulSerial(const Matrix& first, const Matrix& second) {
	Matrix result(first.rows(), second.cols());

	if (first.cols() == second.rows())
		for (size_t i = 0; i < result.rows(); ++i)
			for (size_t j = 0; j < result.cols(); ++j)
				for (size_t k = 0; k < result.rows(); ++k)
					result(i, j) += first(i, k) * second(k, j);
	else
		throw std::invalid_argument("Wrong dimensions");

	return result;
}

Matrix mulParallel(const Matrix& first, const Matrix& second) {
	Matrix result(first.rows(), second.cols());
	if (first.cols() == second.rows())
		#pragma omp parallel for default(shared)
		for (size_t i = 0; i < result.rows(); ++i)
			for (size_t j = 0; j < result.cols(); ++j) {
				result(i, j) = 0;
				for (size_t k = 0; k < result.rows(); ++k)
					result(i, j) += first(i, k) * second(k, j);
			}
	else
		throw std::invalid_argument("Wrong dimensions");

	return result;
}

std::string toString(const Matrix& matrix) {
	std::stringstream ss;
	for (size_t i = 0; i < matrix.rows(); ++i) {
		for (size_t j = 0; j < matrix.cols(); ++j) {
			ss << matrix(i, j) << " ";
		}
		ss << std::endl;
	}
	return ss.str();
}

Matrix Matrix::operator*(const Matrix& matrix) {
	return mulParallel((*this), matrix);
}
