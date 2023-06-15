#pragma once
#include <iostream>
#include <vector>
#include "layer.h"

class Network {
public:
    Network();
    ~Network();

    void initialize_network(int n_inputs, std::vector<std::pair<int, int>> n_hidden, int n_outputs, Factory* act_function_factory);

    void add_layer(int n_neurons, int n_weights, int activation_function, Factory* act_function_factory);
    std::vector<double> forward_propagate(std::vector<double> inputs);
    void backward_propagate_error(std::vector<double> expected);
    void update_weights(std::vector<double> inputs, double l_rate);
    void train(std::vector<std::vector<double>>trainings_data, double l_rate, size_t n_epoch, size_t n_outputs);
    int predict(std::vector<double> input);

    void display_human();
    void toString();


private:
    size_t m_nLayers = 0;
    std::vector<Layer> m_layers;

};

