#include "activation_function.h"
#include <cmath>


/* ACTIVATIONFUNCTION */

/*
* ActivationFunction Constructor
*/


ActivationFunction::ActivationFunction(int function) {
    m_function = function;
}

/*
* ActivationFunction Destructor
*/
ActivationFunction::~ActivationFunction() {
    /*pass*/
}

// Sigmoid activation function
float ActivationFunction::sigmoid(float x) {
    return 1.0 / (1.0 + std::exp(-x));
}

// ReLU activation function
float ActivationFunction::relu(float x) {
    return static_cast<float>(std::max(0.0, static_cast<double>(x)));
}

// Leaky ReLU activation function
float ActivationFunction::leaky_relu(float x, float alpha) {
    return x < 0 ? alpha * x : x;
}

// Tanh activation function
float ActivationFunction::tanh(float x) {
    return std::tanh(x);
}

// Softmax activation function
std::vector<float> ActivationFunction::softmax(std::vector<float> x) {
    std::vector<float> result(x.size());
    float sum = 0;

    // Compute the sum of exponentials of x
    for (int i = 0; i < x.size(); i++) {
        result[i] = std::exp(x[i]);
        sum += result[i];
    }

    // Normalize the result by the sum
    for (int i = 0; i < x.size(); i++) {
        result[i] /= sum;
    }

    return result;
}

float ActivationFunction::der_sigmoid(float x){
    return x * (1.0 - x);
}

float ActivationFunction::der_relu(float x){
    return x > 0 ? 1 : 0;
}

float ActivationFunction::der_leaky_relu(float x, float alpha){
    return x > 0 ? 1 : alpha;
}

float ActivationFunction::der_tanh(float x){
     return 1.0 - x * x;
}

//std::vector<float> ActivationFunction::der_softmax(std::vector<float> x){

//}
