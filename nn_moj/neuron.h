#ifndef NEURON_H
#define NEURON_H

#pragma once
#include <iostream>
#include <vector>
#include "activation_function.h"

class Neuron {
public:
    Neuron(int n_weights, int activation_function, Factory* act_function_factory);
    ~Neuron()= default;

    void activate(std::vector<double> inputs);
    void transfer();
    double transfer_derivative();

    // return mutable reference to the neuron weights
    std::vector<double>& get_weights(void) { return m_weights; };

    double get_output(void) { return m_output; };
    double get_activation(void) { return m_activation; };
    double get_delta(void) { return m_delta; };

    void set_delta(double delta) { m_delta = delta; };

private:
    size_t m_nWeights;
    std::vector<double> m_weights;
    double m_activation=0;
    double m_output;
    double m_delta;
    int m_activation_function;
    Factory* act_function_factory;

private:
    void initWeights(int n_weights);
};

#endif // NEURON_H
