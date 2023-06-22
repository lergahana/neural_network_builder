#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <functional>
#include <vector>
#include "activation_function.h"

class Neuron {

private:
    int m_numWeights = 0;
    std::vector<double> m_weights;
    double m_activation = 0.0;
    double m_output = 0.0;
    double m_delta = 0.0;
    ActivationFunction* activationFunction;

public:
    Neuron(int numWeights, ActivationFunction* activationFunction);
    ~Neuron() = default;

    void activate(std::vector<double> inputs);
    void transfer();
    double transferDerivative();

    std::vector<double>& getWeights() { return m_weights; }

    double getOutput() { return m_output; }
    double getActivation() { return m_activation; }
    double getDelta() { return m_delta; }

    void setDelta(double delta) { m_delta = delta; }
    void setOutput(double output) { m_output = output; }
    void setActivation(double activation) { m_activation = activation; }

};

#endif // NEURON_H
