#include "network.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>


Network::Network() {
    // Needed for rand
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Network::initialize_network(int n_inputs, std::vector<LayerInfo> m_hidden, int n_outputs) {
    //first layer
    Layer first = Layer(m_hidden[0].n_neurons, n_inputs+1, m_hidden[0].act_function);
    add_layer(first);

    //hidden layers
    for (int i = 0; i < m_hidden.size()-1; i++) {
        Layer hidden = Layer(m_hidden[i+1].n_neurons, m_hidden[i].n_neurons+1, m_hidden[i+1].act_function);
        add_layer(hidden);
    }

    //last layer
    Layer last = Layer(n_outputs, m_hidden.back().n_neurons+1, m_hidden.back().act_function);
    add_layer(last);
    setNLayers();
}


void Network::add_layer(Layer l) {
    m_layers.push_back(l);
}

void Network::insert_hidden_layer(LayerInfo l){
    Layer output = m_layers.back();
    int count = 0;
    for (auto &layer: m_layers)
    {
        // Insert the hidden layer before the output layer
        if (count == m_nLayers - 1)
        {
            m_layers[count] = Layer(l.n_neurons, m_layers[count-1].get_neurons().size()+1, l.act_function);
        }
        count += 1;
    }
    // Fix the output layer
    m_layers.push_back(Layer(output.get_neurons().size(), m_layers[count-1].get_neurons().size()+1, output.get_act_function()));
    setNLayers();
}


std::vector<double> Network::forward_propagate(std::vector<double> inputs) {
    std::vector<double> new_inputs;
    for (int i = 0; i < m_nLayers; i++)
    {
        new_inputs.clear();
        std::vector<Neuron>& layer_neurons = m_layers[i].get_neurons();

        for (int n = 0; n < layer_neurons.size(); n++)
        {
            layer_neurons[n].activate(inputs);
            layer_neurons[n].transfer();
            new_inputs.push_back(layer_neurons[n].getOutput());
        }
        inputs = new_inputs;
    }
    return inputs;
}


void Network::backward_propagate_error(std::vector<double> expected) {

    // Start from last layer and propagate error to the first layer
    for (int i = m_nLayers-1; i >= 0; i--)
    {
        std::vector<Neuron>& layer_neurons = m_layers[i].get_neurons();
        // iterate over each neuron in this layer
        for (int n = 0; n < layer_neurons.size(); n++)
        {
            double error = 0.0;
            // last layer
            if (i == m_nLayers-1)
            {
                error = expected[n] - layer_neurons[n].getOutput();
            }
            // all other layers
            else {
                for (auto& neuron : m_layers[i + 1].get_neurons()) {
                    error += (neuron.getWeights()[n] * neuron.getDelta());
                }
            }
            layer_neurons[n].setDelta(error * layer_neurons[n].transferDerivative());
        }
    }

}


void Network::update_weights(std::vector<double> inputs, double l_rate) {
    std::vector<double> new_inputs;
    for (int i = 0; i < m_nLayers; i++)
    {
        new_inputs.clear();
        if (i != 0)
        {
            for (auto &neuron: m_layers[i-1].get_neurons()){
                new_inputs.push_back(neuron.getOutput());
            }
        }
        else {
            new_inputs = std::vector<double>(inputs.begin(), inputs.end() - 1);
        }

        std::vector<Neuron>& layer_neurons = m_layers[i].get_neurons();

        for (int n = 0; n < layer_neurons.size(); n++)
        {
            std::vector<double>& weights = layer_neurons[n].getWeights();

            for (int j = 0; j < new_inputs.size(); j++)
            {
                weights[j] += l_rate * layer_neurons[n].getDelta() * new_inputs[j];
            }
            // update bias
            weights.back() += l_rate * layer_neurons[n].getDelta();
        }
    }
}


void Network::train(std::vector<std::vector<double>> training_data, double l_rate, int n_epoch, int n_outputs) {

    for (int e = 0; e < n_epoch; e++)
    {
        double sum_error = 0;

        for (const auto &row: training_data)
        {
            std::vector<double> outputs = forward_propagate(row);
            std::vector<double> expected(n_outputs, 0.0);
            //the index corresponding to the expected output class is set to 1.0, while all other elements remain 0.0
            expected[static_cast<int>(row.back())] = 1.0;
            for (int x = 0; x < n_outputs; x++)
            {
                sum_error += static_cast<double>(std::pow((expected[x] - outputs[x]), 2));
            }
            backward_propagate_error(expected);
            update_weights(row, l_rate);
        }
        std::cout << "[>] epoch=" << (e+1) << ", l_rate=" << l_rate << ", error=" << sum_error << std::endl;
        output += "[>] epoch=" + std::to_string(e+1) + ", l_rate=" + std::to_string(l_rate) + ", error=" + std::to_string(sum_error) + "\n";
    }
}


int Network::predict(std::vector<double> input) {
    std::vector<double> outputs = forward_propagate(input);
    return std::max_element(outputs.begin(), outputs.end()) - outputs.begin();
}


void Network::toString(){
    std::cout << "Network: " << std::endl;
    std::cout << "Number of layers: " << get_layers().size() << std::endl;
    for (int i = 0; i < get_layers().size(); i++){
        std::string line(100, '-');
        std::cout << line << std::endl;
        std::cout << "Number of neurons in layer: " << i+1 << ": " << get_layers()[i].get_neurons().size() << std::endl;
        for (int j = 0; j < get_layers()[i].get_neurons().size(); j++)
        {
            std::cout << "Neuron " << (j+1) << "\n   weights: ";
            std::vector<double> weights = get_layers()[i].get_neurons()[j].getWeights();
            for (size_t w = 0; w < weights.size(); ++w)
            {
                std::cout << weights[w];
                if (w < weights.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "\t delta: " << get_layers()[i].get_neurons()[j].getDelta();
            std::cout << "\t output: " << get_layers()[i].get_neurons()[j].getOutput();
            std::cout << "\t activation: " << get_layers()[i].get_neurons()[j].getActivation();
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}
