#include "layer.h"

Layer::Layer(int numNeurons, int numWeights, ActivationFunction* actFunction) : m_actFunction(actFunction)
{
    m_neurons.clear();
    m_neurons.reserve(numNeurons);
    std::generate_n(std::back_inserter(m_neurons), numNeurons, [numWeights, actFunction]() {
        return Neuron(numWeights, actFunction);
    });
}
