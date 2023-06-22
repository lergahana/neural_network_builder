#include "layer.h"

Layer::Layer(int numNeurons, int numWeights, ActivationFunction* actFunction) : actFunction(actFunction)
{
    neurons.clear();
    neurons.reserve(numNeurons);
    std::generate_n(std::back_inserter(neurons), numNeurons, [numWeights, actFunction]() {
        return Neuron(numWeights, actFunction);
    });
}

void Layer::setActivationFunction(ActivationFunction* activationFunction)
{
    actFunction = activationFunction;
}
