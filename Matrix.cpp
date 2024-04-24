#include <vector>
#include <iostream>
#include "Matrix.h"

Matrix::Matrix() : rows(0), cols(0) {
}

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    data.resize(rows, std::vector<double>(cols, 0));
}

int Matrix::getRows() const {
    return rows;
}

int Matrix::getCols() const {
    return cols;
}

std::pair<int, int> Matrix::getShape() const {
    return std::make_pair(rows, cols);
}

double& Matrix::operator()(int i, int j) {
    return data[i][j];
}

const double& Matrix::operator()(int i, int j) const {
    return data[i][j];
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication.");
    }

    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return result;
}

//Implement multiplication with a numeric value
Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result(i, j) = (*this)(i, j) * scalar;
        }
    }
    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (other.rows == 1 && other.cols == cols) {
        // Broadcasting: add the row vector to each row of the matrix
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result(i, j) = (*this)(i, j) + other(0, j);
            }
        }
        return result;
    } else if (rows == other.rows && cols == other.cols) {
        // Element-wise addition of two matrices with the same dimensions
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result(i, j) = (*this)(i, j) + other(i, j);
            }
        }
        return result;
    } else {
        throw std::invalid_argument("Matrix dimensions do not match for addition.");
    }
}

void Matrix::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Quantize the matrix to 8-bit integer representation.
void quantize(Matrix<float>& mat, Matrix<int8_t>& quantized_mat, Matrix<float>& scale) {
    float max_val = *std::max_element(mat.begin(), mat.end(), [](float a, float b) {
        return std::abs(a) < std::abs(b);
    });
    scale = 127.0f / max_val;

    for (size_t i = 0; i < mat.size(); ++i) {
        quantized_mat[i] = static_cast<int8_t>(std::round(mat[i] * scale));
    }
}

// Dequantize the matrix from 8-bit integer representation back to floating point.
void dequantize(Matrix<int32_t>& quantized_mat, Matrix<float>& dequantized_mat, Matrix<float>& scale) {
    for (size_t i = 0; i < quantized_mat.size(); ++i) {
        dequantized_mat[i] = quantized_mat[i] / scale;
    }
}
