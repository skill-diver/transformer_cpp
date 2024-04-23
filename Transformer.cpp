#include "Transformer.h"
#include <iostream>
Transformer::Transformer(int numLayers, int numHeads, int inputDim, int hiddenDim, int outputDim) {
    for (int i = 0; i < numLayers; ++i) {
        attentionLayers.emplace_back(numHeads, inputDim, outputDim);
        feedForwardLayers.emplace_back(outputDim, hiddenDim, outputDim);
        numParameters += attentionLayers.back().getNumParameters();
        numParameters += feedForwardLayers.back().getNumParameters();
    }
}

Matrix Transformer::forward(const Matrix& input) {
    Matrix output = input;
    for (int i = 0; i < attentionLayers.size(); ++i) {
        output = attentionLayers[i].forward(output);
        auto shape = output.getShape();
        output = feedForwardLayers[i].forward(output);
    }
    return output;
}
int Transformer::getNumParameters() const {
    return numParameters;
}