
#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H

class ActivationFunction {
public:
    ActivationFunction(int n_weights);
    ~ActivationFunction();

    double sigmoid(double x);

};

#endif // ACTIVATION_FUNCTIONS_H
