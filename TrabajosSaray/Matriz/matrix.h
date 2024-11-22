#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
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

    // Getter y Setter separados para mayor claridad
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
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cout << data[i][j] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // Suma recursiva de matrices
    template<typename U>
    Matrix<T> recursiveSum(const Matrix<U>& other) const {
        if (rows != oth6+er.getRows() || cols != other.getCols()) {
            throw std::invalid_argument("Matrices must have the same dimensions");
        }
        
        Matrix<T> result(rows, cols);
        recursiveSumHelper(other, result, static_cast<int>(rows)-1, static_cast<int>(cols)-1);
        return result;
    }

private:
    template<typename U>
    void recursiveSumHelper(const Matrix<U>& other, Matrix<T>& result, int i, int j) const {
        if (i < 0) return;
        
        if (j >= 0) {
            result.at(i, j) = this->at(i, j) + other.at(i, j);
            recursiveSumHelper(other, result, i, j-1);
        } else {
            recursiveSumHelper(other, result, i-1, cols-1);
        }
    }
};

#endif