#include "network.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include "activation_function.h"


/* NETWORK */

/*
* Network Constructor
*/
Network::Network() {
    // initialize prng
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    m_nLayers = 0;
}

/*
* Network Destructor
*/
Network::~Network() {
    /*pass*/
}

/*
* Initialize a network manually with more hidden layers
* n_hidden is a pair: {number of neurons in the layer, activation function for that layer}
*/
void Network::initialize_network(int n_inputs, std::vector<std::pair<int, int>> n_hidden, int n_outputs, Factory* act_function_factory) {

    // add the first hidden layer (n_hidden neurons are each connected to all inputs)
    this->add_layer(n_hidden[0].first, n_inputs+1, n_hidden[0].second, act_function_factory);

    for (int i = 0; i < n_hidden.size()-1; i++) {
        // add a hidden layer (n_hidden neurons are each connected to all neurons from last layer)
        this->add_layer(n_hidden[i+1].first, n_hidden[i].first+1, n_hidden[i+1].second, act_function_factory);
    }


    // add an output layer (one neuron for each output is connected to all neurons from the previous layer)
    this->add_layer(n_outputs, n_hidden.back().first+1, n_hidden.back().second, act_function_factory);
}

/*
* Add another layer to the network
*/
void Network::add_layer(int n_neurons, int n_weights, int activation_function, Factory* act_function_factory) {
    m_layers.push_back(Layer(n_neurons, n_weights, activation_function, act_function_factory));
    m_nLayers++;
}

/*
* One forward propagation of an input
*/
std::vector<double> Network::forward_propagate(std::vector<double> inputs) {
    std::vector<double> new_inputs;
    for (size_t i = 0; i < m_nLayers; i++)
    {
        new_inputs.clear();

        // reference the layer neurons directly
        std::vector<Neuron>& layer_neurons = m_layers[i].get_neurons();
        for (size_t n = 0; n < layer_neurons.size(); n++)
        {
            layer_neurons[n].activate(inputs);
            layer_neurons[n].transfer();
            new_inputs.push_back(layer_neurons[n].get_output());
        }
        inputs = new_inputs;
    }

    return inputs;
}

/*
* Propagate the deviation from an expected output backwards through the network
*/
void Network::backward_propagate_error(std::vector<double> expected) {
    // reverse traverse the layers
    for (size_t i = m_nLayers; i --> 0;)
    {
        // get a reference to the neurons of this layer
        std::vector<Neuron>& layer_neurons = m_layers[i].get_neurons();
        // iterate over each neuron in this layer
        for (size_t n = 0; n < layer_neurons.size(); n++)
        {
            double error = 0.0;
            // feed the expected result to the output layer
            if (i == m_nLayers - 1)
            {
                error = expected[n] - layer_neurons[n].get_output();
            }
            else {
                for (auto& neu : m_layers[i + 1].get_neurons()) {
                    error += (neu.get_weights()[n] * neu.get_delta());
                }
            }
            // update the delta value of the neuron
            layer_neurons[n].set_delta(error * layer_neurons[n].transfer_derivative());
        }
    }
}

/*
* Update weights of a network after an error back propagation
*/
void Network::update_weights(std::vector<double> inputs, double l_rate) {
    // iterate over the layers
    for (size_t i = 0; i < m_nLayers; i++)
    {
        std::vector<double> new_inputs = {};
        if (i != 0) {
            // grab the outputs from the previous layer (except for the first layer)
            for (auto &neuron: m_layers[i-1].get_neurons())
            {
                new_inputs.push_back(neuron.get_output());
            }
        }
        else {
            // use the original input for the first layer (ignore the bias input / last element)
            new_inputs = std::vector<double>(inputs.begin(), inputs.end() - 1);
        }

        // get a reference to the neurons of this layer
        std::vector<Neuron>& layer_neurons = m_layers[i].get_neurons();

        for (size_t n = 0; n < layer_neurons.size(); n++)
        {
            // get a reference to the weights of the neuron
            std::vector<double>& weights = layer_neurons[n].get_weights();
            // update weights
            for (size_t j = 0; j < new_inputs.size(); j++)
            {
                weights[j] += l_rate * layer_neurons[n].get_delta() * new_inputs[j];
            }
            // update bias
            weights.back() += l_rate * layer_neurons[n].get_delta();
        }
    }
}

/*
* Train the network with trainings data
*/
void Network::train(std::vector<std::vector<double>>trainings_data, double l_rate, size_t n_epoch, size_t n_outputs) {
    for (size_t e = 0; e < n_epoch; e++)
    {
        double sum_error = 0;

        for (const auto &row: trainings_data)
        {
            std::vector<double> outputs = this->forward_propagate(row);
            std::vector<double> expected(n_outputs, 0.0);
            expected[static_cast<int>(row.back())] = 1.0;
            for (size_t x = 0; x < n_outputs; x++)
            {
                sum_error += static_cast<double>(std::pow((expected[x] - outputs[x]), 2));
            }
            this->backward_propagate_error(expected);
            this->update_weights(row, l_rate);
        }
        std::cout << "[>] epoch=" << e << ", l_rate=" << l_rate << ", error=" << sum_error << std::endl;

    }
}

/*
* Make a prediction for an input (one forward propagation)
*/
int Network::predict(std::vector<double> input) {
    std::vector<double> outputs = this->forward_propagate(input);
//    for (auto &output : outputs){
//        std::cout << output << " ";
//    }
//    std::cout << std::endl;
    return std::max_element(outputs.begin(), outputs.end()) - outputs.begin();
}

/*
* Display the network in a human readable format
*/
void Network::display_human() {
    std::cout << "[Network] (Layers: " << m_nLayers << ")" << std::endl;

    std::cout << "{" << std::endl;
    for (size_t l = 0; l < m_layers.size(); l++)
    {
        Layer layer = m_layers[l];
        std::cout << "\t (Layer " << l << " , function: " << m_layers[l].get_function() << "): {";
        for (size_t i = 0; i < layer.get_neurons().size(); i++)
        {
            Neuron neuron = layer.get_neurons()[i];
            std::cout << "<(Neuron " << i << "): [ weights={";
            std::vector<double> weights = neuron.get_weights();
            for (size_t w = 0; w < weights.size(); ++w)
            {
                std::cout << weights[w];
                if (w < weights.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "}, output=" << neuron.get_output() << ", activation=" << neuron.get_activation() << ", delta=" << neuron.get_delta();
            std::cout << "]>";
            if (i < layer.get_neurons().size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "}";
        if (l < m_layers.size() - 1) {
            std::cout << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << "}" << std::endl;
}

void Network::toString(){
    std::cout << "Network: " << std::endl;
    std::cout << "Number of layers: " << m_layers.size() << std::endl;
    for (int i = 0; i < m_layers.size(); i++){
        std::cout << "Number of neurons in layer: " << i+1 << ": " << m_layers[i].get_neurons().size() << std::endl;
        std::string line(40, '-');
        std::cout << line << std::endl;
        for (int j = 0; j < m_layers[i].get_neurons().size(); j++)
        {
            std::cout << "Neuron " << (j+1) << "\t weights: ";
            std::vector<double>& weights = m_layers[i].get_neurons()[j].get_weights();
            for (size_t w = 0; w < weights.size(); ++w)
            {
                std::cout << weights[w];
                if (w < weights.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "\t delta: " << m_layers[i].get_neurons()[j].get_delta();
            std::cout << "\t output: " << m_layers[i].get_neurons()[j].get_output();
            std::cout << "\t activation: " << m_layers[i].get_neurons()[j].get_activation();
            std::cout << std::endl;

        }
    }
}
