#include "activation_function.h"
#include <iostream>

double Sigmoid::activate(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}

double Sigmoid::activateDerivative(double x) {
    return x * (1.0 - x);
}


double Relu::activate(double x) {
    return (x > 0) ? x : 0;
}

double Relu::activateDerivative(double x) {
    return (x > 0) ? 1 : 0;
}

double Tanh::activate(double x) {
    return std::tanh(x);
}

double Tanh::activateDerivative(double x) {
    return 1 - std::pow(std::tanh(x), 2);
}
