#include <iostream>
#include "Matrix.h"
#include "MultiHeadAttention.h"
#include "FeedForward.h"

int main() {
    int batchSize = 2;
    int seqLen = 3;
    int inputDim = 4;
    int numHeads = 2;
    int hiddenDim = 8;
    int outputDim = 4;

    Matrix input(batchSize, seqLen * inputDim);
    // Initialize the input matrix with appropriate values
    for (int i = 0; i < batchSize; ++i) {
        for (int j = 0; j < seqLen * inputDim; ++j) {
            input(i, j) = (i + j) / 10.0;
        }
    }

    MultiHeadAttention attention(numHeads, inputDim, outputDim);
    FeedForward feedForward(outputDim, hiddenDim, outputDim);

    Matrix attentionOutput = attention.forward(input);
    Matrix output = feedForward.forward(attentionOutput);

    std::cout << "Input:" << std::endl;
    input.print();

    std::cout << "Attention Output:" << std::endl;
    attentionOutput.print();

    std::cout << "Feed Forward Output:" << std::endl;
    output.print();

    return 0;
}