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
double ActivationFunction::sigmoid(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}

// ReLU activation function
double ActivationFunction::relu(double x) {
    return static_cast<double>(std::max(0.0, static_cast<double>(x)));
}

// Leaky ReLU activation function
double ActivationFunction::leaky_relu(double x, double alpha) {
    return x < 0 ? alpha * x : x;
}

// Tanh activation function
double ActivationFunction::tanh(double x) {
    return std::tanh(x);
}

// Softmax activation function
std::vector<double> ActivationFunction::softmax(std::vector<double> x) {
    std::vector<double> result(x.size());
    double sum = 0;

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

double ActivationFunction::der_sigmoid(double x){
    return x * (1.0 - x);
}

double ActivationFunction::der_relu(double x){
    return x > 0 ? 1 : 0;
}

double ActivationFunction::der_leaky_relu(double x, double alpha){
    return x > 0 ? 1 : alpha;
}

double ActivationFunction::der_tanh(double x){
     return 1.0 - x * x;
}

////std::vector<double> ActivationFunction::der_softmax(std::vector<double> x){

////}

//#include "activation_function.h"
//#include <iostream>

double Sigmoid::activate(double x) {
    return (1.0 / (1.0 + std::exp(-x)));
}

double Sigmoid::activateDerivative(double x) {
    double sigmoid = (1.0 / (1.0 + std::exp(-x)));
    return (sigmoid * (1 - sigmoid));
}




