#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cinttypes>  // For int8_t and int32_t

class Matrix {
private:
    std::vector<std::vector<double>> data;
    int rows;
    int cols;

public:
    Matrix(int rows, int cols);
    Matrix(); // Default constructor declaration
    int getRows() const;
    int getCols() const;
    std::pair<int, int> getShape() const;
    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Matrix operator+(const Matrix& other) const;
    void print() const;
    static void quantize(const Matrix& mat, Matrix<int8_t>& quantized_mat, Matrix<float>& scale);
    static void dequantize(const Matrix<int32_t>& quantized_mat, Matrix<float>& dequantized_mat, Matrix<float>& scale);
    Matrix transpose() const;
};

#endif // MATRIX_H
