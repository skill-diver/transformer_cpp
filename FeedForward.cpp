#include "Matrix.h"

class FeedForward {
private:
    Matrix w1;
    Matrix b1;
    Matrix w2;
    Matrix b2;

public:
    FeedForward(int inputDim, int hiddenDim, int outputDim)
        : w1(inputDim, hiddenDim), b1(1, hiddenDim),
          w2(hiddenDim, outputDim), b2(1, outputDim) {}

    Matrix forward(const Matrix& input) {
        Matrix hidden = relu(input * w1 + b1);
        Matrix output = hidden * w2 + b2;
        return output;
    }

private:
    Matrix relu(const Matrix& input) {
        Matrix output(input.getRows(), input.getCols());
        for (int i = 0; i < input.getRows(); ++i) {
            for (int j = 0; j < input.getCols(); ++j) {
                output(i, j) = std::max(0.0, input(i, j));
            }
        }
        return output;
    }
};