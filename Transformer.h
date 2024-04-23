#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include "MultiHeadAttention.h"
#include "FeedForward.h"

class Transformer {
public:
    Transformer(int numLayers, int numHeads, int inputDim, int hiddenDim, int outputDim);
    Matrix forward(const Matrix& input);
    int getNumParameters() const;

private:
    std::vector<MultiHeadAttention> attentionLayers;
    std::vector<FeedForward> feedForwardLayers;
    int numParameters;

};

#endif // TRANSFORMER_H