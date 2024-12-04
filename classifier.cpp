#include "classifier.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;


// Train function to input training instances
void Classifier::Train(const vector<Instance>& trainingData) {
    trainingInstances = trainingData; //Assigns data to member variable trainingInstances
}

// Test function to predict the class label for instance
int Classifier::Test(const Instance testInstance) {
    double minDistance = numeric_limits<double>::max(); //assign largest double value to min distance
    int predictedLabel = -1;

    for (int i = 0; i < trainingInstances.size(); ++i) {
        double distance = ComputeDistance(testInstance.features, trainingInstances.at(i).features);
        if (distance < minDistance) {
            minDistance = distance;
            predictedLabel = trainingInstances.at(i).classifier;
        }
    }
    return predictedLabel;
}

// Helper function to compute Euclidean distance between two feature vectors
double Classifier::ComputeDistance(const vector<double>& features1, const vector<double>& features2) {
    double sum = 0.0;
    for (int i = 0; i < features1.size(); ++i) {
        sum += pow(features1[i] - features2[i], 2);
    }
    return sqrt(sum);
}

