#ifndef MULTIHEADATTENTION_H
#define MULTIHEADATTENTION_H

#include "Matrix.h"
#include <vector>

class MultiHeadAttention {
private:
    int numHeads;
    int headDim;
    std::vector<Matrix> wq;
    std::vector<Matrix> wk;
    std::vector<Matrix> wv;
    Matrix wo;

public:
    MultiHeadAttention(int numHeads, int inputDim, int outputDim);
    Matrix forward(const Matrix& input);

private:
    Matrix softmax(const Matrix& input);
};

#endif // MULTIHEADATTENTION_H
