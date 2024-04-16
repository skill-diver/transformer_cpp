#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

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

    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Matrix operator+(const Matrix& other) const;
    void print() const;
    Matrix transpose() const;
};

#endif // MATRIX_H