#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "matrix.h"
#include <random>
#include <functional>

template<typename T>
class MatrixOperations {
public:
    static Matrix<T> generateRandomMatrix(size_t rows, size_t cols, T min, T max) {
        Matrix<T> matrix(rows, cols);
        
        // Lambda for generating random numbers
        auto randomGenerator = [&]() {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(min, max);
            return static_cast<T>(dis(gen));
        };

        // Fill matrix using lambda
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                matrix.at(i, j) = randomGenerator();
            }
        }
        return matrix;
    }
};

#endif