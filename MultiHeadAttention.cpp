#include <vector>
#include <cmath>
#include "Matrix.h"
#include "MultiHeadAttention.h"

MultiHeadAttention::MultiHeadAttention(int numHeads, int inputDim, int outputDim)
    : numHeads(numHeads), headDim(outputDim / numHeads),
      wq(numHeads, Matrix(inputDim, headDim)),
      wk(numHeads, Matrix(inputDim, headDim)),
      wv(numHeads, Matrix(inputDim, headDim)),
      wo(outputDim, outputDim) {}

Matrix MultiHeadAttention::forward(const Matrix& input) {
    int batchSize = input.getRows();
    int seqLen = input.getCols() / headDim;

    std::vector<Matrix> queries(numHeads);
    std::vector<Matrix> keys(numHeads);
    std::vector<Matrix> values(numHeads);

    for (int h = 0; h < numHeads; ++h) {
        queries[h] = input * wq[h];
        keys[h] = input * wk[h];
        values[h] = input * wv[h];
    }

    std::vector<Matrix> outputs(numHeads);

    for (int h = 0; h < numHeads; ++h) {
        Matrix scores = queries[h] * keys[h].transpose();
        scores = scores * (1.0 / std::sqrt(headDim));

        Matrix attention = softmax(scores);
        outputs[h] = attention * values[h];
    }

    Matrix concatOutput(batchSize, seqLen * headDim);
    for (int h = 0; h < numHeads; ++h) {
        for (int i = 0; i < batchSize; ++i) {
            for (int j = 0; j < seqLen; ++j) {
                concatOutput(i, h * seqLen + j) = outputs[h](i, j);
            }
        }
    }

    Matrix output = concatOutput * wo;
    return output;
}

Matrix MultiHeadAttention::softmax(const Matrix& input) {
    Matrix exp(input.getRows(), input.getCols());
    for (int i = 0; i < input.getRows(); ++i) {
        double sum = 0.0;
        for (int j = 0; j < input.getCols(); ++j) {
            exp(i, j) = std::exp(input(i, j));
            sum += exp(i, j);
        }
        for (int j = 0; j < input.getCols(); ++j) {
            exp(i, j) /= sum;
        }
    }
    return exp;
}