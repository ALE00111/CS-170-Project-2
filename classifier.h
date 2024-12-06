#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <fstream>
#include <vector>
using namespace std; 

using namespace std; 

//This class is used to hold training instances in memory and use NN
//Use Euclidean distance to measure the distance between two points
//This done by having a eucilidean distance be calcualted with a space of 10
//For each instance of data, it will contain subset of features it has, the class label, and its current position 

struct Instance {
    double classType;
    int ID;
    vector<double> features; 
};
 
class Classifier {
    public:
        Classifier();
        void Train(const vector<Instance>& trainingData); //function for inputting training instances
        int Test(const Instance testInstance); //function for inputting test instances and output is the prdicted class label
    private:
        vector<Instance> trainingInstances;
        double EuclideanDistance(const vector<double>& features1, const vector<double>& features2);
};

#endif
