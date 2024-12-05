#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <vector>
#include "classifier.h"
#include <iostream>
using namespace std;


//This class is for the evaluation module that returns the accuract of the classifier
//of a given dataset, when using the given features subset
class Validator {
    public:
        Validator();
        double Validate(const vector<Instance>& dataset, Classifier& classifier);

    private:
        // helper function for leave-one-out algorithm
        vector<Instance> createSubset(const vector<Instance>& dataset, int indexToExclude);
};

#endif