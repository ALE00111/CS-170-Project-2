#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std; 

// Define a structure for storing instances
struct Instance {
    vector<double> features;
    int classLabel;
};
//This class is used to hold training instances in memory and use NN
//Use Euclidean distance to measure the distance between two points

class Classifier {
    public:
        Classifier();
        void Train(const vector<Instance>& trainingData); //function for inputting training instances
        int Test(const Instance& testInstance); //function for inputting test instances and output is the prdicted class label
    private:
        vector<Instance> trainingInstances;
        double ComputeDistance(const vector<double>& features1, const vector<double>& features2);
};
#endif
