#ifndef FEEDFORWARD_H
#define FEEDFORWARD_H

#include "Matrix.h"

class FeedForward {
public:
    FeedForward(int inputDim, int hiddenDim, int outputDim);
    Matrix forward(const Matrix& input);
    int getNumParameters() const;
private:
    Matrix relu(const Matrix& input);

    Matrix w1;
    Matrix b1;
    Matrix w2;
    Matrix b2;
};

#endif // FEEDFORWARD_H
