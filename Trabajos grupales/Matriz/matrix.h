#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include<algorithm>
#include <stdexcept>

template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    size_t rows;
    size_t cols;

public:
    Matrix(size_t r, size_t c) : rows(r), cols(c) {
        data.resize(rows, std::vector<T>(cols));
    }

    // Getter y Setter
    T& at(size_t i, size_t j) {
        if (i >= rows || j >= cols) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[i][j];
    }

    const T& at(size_t i, size_t j) const {
        if (i >= rows || j >= cols) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[i][j];
    }

    // Obtener dimensiones
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }

    // Función para imprimir matriz
    void print() const {
        std::for_each(data.begin(), data.end(), [](const std::vector<int>& fila) {
            std::for_each(fila.begin(), fila.end(), [](int num) {
                std::cout << num << " ";
            });
        std::cout << std::endl;
    });
    }

    // Suma recursiva de matrices
    template<typename U>
    Matrix<T> recursiveSum(const Matrix<U>& other) const {
        if (rows != other.getRows() || cols != other.getCols()) {
            throw std::invalid_argument("Matrices must have the same dimensions");
        }
        
        Matrix<T> result(rows, cols);
        recursiveSumHelper(other, result, static_cast<int>(rows)-1, static_cast<int>(cols)-1);
        return result;
    }

private:
    template<typename U>
    void recursiveSumHelper(const Matrix<U>& other, Matrix<T>& result, int i, int j) const {
        auto recursiveSumLambda = [this, &other, &result, &i, &j](int currentI, int currentJ) -> void {
            if (currentI < 0) return;
            
            if (currentJ >= 0) {
                result.at(currentI, currentJ) = this->at(currentI, currentJ) + other.at(currentI, currentJ);
                recursiveSumLambda(currentI, currentJ - 1);
            } else {
                recursiveSumLambda(currentI - 1, cols - 1);
            }
        };

        recursiveSumLambda(i, j);
    }
};

#endif