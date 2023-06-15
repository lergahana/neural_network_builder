#include "activation_function.h"
#include <iostream>

double Sigmoid::activate(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}

double Sigmoid::activateDerivative(double x) {
    return x * (1.0 - x);
}


