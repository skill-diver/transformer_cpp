#include "Matrix.h"
#include "FeedForward.h"

FeedForward::FeedForward(int inputDim, int hiddenDim, int outputDim)
    : w1(inputDim, hiddenDim), b1(1, hiddenDim),
      w2(hiddenDim, outputDim), b2(1, outputDim) {}

Matrix FeedForward::forward(const Matrix& input) {
    Matrix hidden = relu(input * w1 + b1);
    Matrix output = hidden * w2 + b2;
    return output;
}

Matrix FeedForward::relu(const Matrix& input) {
    Matrix output(input.getRows(), input.getCols());
    for (int i = 0; i < input.getRows(); ++i) {
        for (int j = 0; j < input.getCols(); ++j) {
            output(i, j) = std::max(0.0, input(i, j));
        }
    }
    return output;
}

int FeedForward::getNumParameters() const {
    return w1.getRows() * w1.getCols() +
           b1.getRows() * b1.getCols() +
           w2.getRows() * w2.getCols() +
           b2.getRows() * b2.getCols();
}