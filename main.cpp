#include <cmath>
#include <functional>
#include <iostream>
#include <valarray>
#include <vector>
float relu(float input) {
  if (input > 0.0f)
    return input;
  return 0.0f;
}

float sigmoid(float input) { return 1.0f / (1.0f + std::exp(-input)); }

struct Matrix {
  Matrix(size_t numberOfRowsInput, size_t numberOfColumsInput)
      : numberOfRows(numberOfRowsInput), numberOfColums(numberOfColumsInput),
        data(numberOfColums * numberOfRows, 0.0) {}
  void random() {
    for (size_t i = 0; i < data.size(); ++i) {
      float r =
          static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f -
          1.0f;
      data[i] = r;
    }
  }

  friend std::ostream &operator<<(std::ostream &stream, const Matrix &matrix) {
    for (size_t i = 0; i < matrix.data.size(); ++i) {
      stream << matrix.data[i] << " ";
      if ((1 + i) % matrix.numberOfRows == 0)
        stream << std::endl;
    }
    return stream;
  }

  friend std::valarray<float> operator*(const Matrix &matrix,
                                        const std::valarray<float> &vector) {
    std::valarray<float> output(0.0, matrix.numberOfRows);
    for (size_t i = 0; i < matrix.numberOfRows; ++i) {
      for (size_t j = 0; j < matrix.numberOfColums; ++j) {
        output[i] += vector[j] * matrix.data[i * matrix.numberOfColums + j];
      }
    }
    return output;
  }

  friend Matrix operator*(const Matrix &matrix1, const Matrix &matrix2) {
    Matrix output(matrix1.numberOfRows, matrix2.numberOfColums);
    for (size_t i = 0; i < matrix1.numberOfRows; ++i) {
      for (size_t k = 0; k < matrix2.numberOfColums; ++k) {
        float sum = 0.0;
        for (size_t j = 0; j < matrix2.numberOfRows; ++j) {
          sum += matrix1.data[j + i * matrix1.numberOfColums] *
                 matrix2.data[j * matrix2.numberOfColums + k];
        }
        output.data[i * matrix2.numberOfColums + k] = sum;
      }
    }
    return output;
  }
  size_t numberOfRows;
  size_t numberOfColums;
  std::vector<float> data;
};

class Layer {
public:
  Layer(size_t numberOfNeuronsInput, size_t numberOfPrevNeuronsInput,
        std::function<float(float)> activationFunctionInput)
      : numberOfNeurons(numberOfNeuronsInput),
        numNeuronsPrevLayer(numberOfPrevNeuronsInput),
        weights(numberOfNeurons, numNeuronsPrevLayer),
        activationFunction(activationFunctionInput) {
    std::vector<float> tmp;
    for (size_t i = 0; i < numberOfNeurons; ++i) {
      float r =
          (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 2.0f -
          1.0f;
      tmp.push_back(r);
    }
    bias = std::valarray<float>(tmp.data(), tmp.size());
    weights.random();
  }
  friend std::ostream &operator<<(std::ostream &stream, const Layer &layer) {
    stream << "weights:" << std::endl;
    stream << layer.weights;
    stream << "bias" << std::endl;
    for (auto i : layer.bias) {
      stream << i << " ";
    }
    return stream;
  }
  std::valarray<float> forwardPropagation(std::valarray<float> input) {
    std::valarray<float> output;
    output = activationFunctionArray(weights * input + bias);
    return output;
  }
  std::valarray<float> activationFunctionArray(std::valarray<float> array) {
    for (float &x : array) {
      x = activationFunction(x);
    }
    return array;
  }

private:
  size_t numberOfNeurons;
  size_t numNeuronsPrevLayer;
  Matrix weights;
  std::valarray<float> bias;
  std::function<float(float)> activationFunction;
};

int main() {
  Layer layer(5, 8, relu);

  std::cout << "funguje" << std::endl;
  std::cout << layer << std::endl;

  std::valarray<float> input(1.1f, 8);
  std::valarray<float> output = layer.forwardPropagation(input);
  for (auto i : output) {
    std::cout << i << std::endl;
  }
  return 0;
}
