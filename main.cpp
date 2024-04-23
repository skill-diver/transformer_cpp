#include <iostream>
#include "Matrix.h"
#include "MultiHeadAttention.h"
#include "FeedForward.h"
#include "Transformer.h"

int main() {
    int seqLen = 5;
    int inputDim = 12;
    int numHeads = inputDim/3;
    int hiddenDim = 10;
    int outputDim = inputDim;

    Matrix input(seqLen, inputDim);
    for (int i = 0; i < seqLen; ++i) {
        for (int j = 0; j < inputDim; ++j) {
            input(i, j) = (i + j) / 10.0;
        }
    }

    int numLayers = 1000;
// ...
    Transformer transformer(numLayers, numHeads, inputDim, hiddenDim, outputDim);
    Matrix output = transformer.forward(input);
    std::cout << "Num parameters:" << transformer.getNumParameters() << std::endl;
    output.print();
}