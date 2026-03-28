#include <iostream>
#include <vector>

class Layer {
public:
  Layer(unsigned int numberOfNeurons) {
    for (unsigned int i = 0; i < numberOfNeurons; i++) {
      float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
      std::vector<float> row(numberOfNeurons, r);
      weights.push_back(row);
    }
  }

private:
  std::vector<std::vector<float>> weights;
  unsigned int numberOfNeurons;
  unsigned int numNeuronsPrevLayer;
};

int main() {
  Layer layer(50);

  std::cout << "funguje" << std::endl;
  return 0;
}
