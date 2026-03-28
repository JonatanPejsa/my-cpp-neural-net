#include <iostream>
#include <vector>

struct Matrix {
  Matrix(size_t numberOfRowsInput, size_t numberOfColumsInput)
      : numberOfRows(numberOfRowsInput), numberOfColums(numberOfColumsInput),
        data(numberOfColums * numberOfRows, 0.0) {}
  void random() {
    for (size_t i = 0; i < data.size(); ++i) {
      float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
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
  size_t numberOfRows;
  size_t numberOfColums;
  std::vector<float> data;
};

class Layer {
public:
  Layer(size_t numberOfNeuronsInput, size_t numberOfPrevNeuronsInput)
      : numberOfNeurons(numberOfNeuronsInput),
        numNeuronsPrevLayer(numberOfPrevNeuronsInput),
        weights(numberOfNeurons, numNeuronsPrevLayer) {
    for (size_t i = 0; i < numberOfNeurons; ++i) {
      float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
      bias.push_back(r);
    }
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
  std::vector<float> forwardPropagation(std::vector<float> input) {
    std::vector<float> output;
    output.reserve(numberOfNeurons);
    return output;
  }

private:
  size_t numberOfNeurons;
  size_t numNeuronsPrevLayer;
  Matrix weights;
  std::vector<float> bias;
};

int main() {
  Layer layer(5, 8);

  std::cout << "funguje" << std::endl;
  std::cout << layer << std::endl;
  return 0;
}
