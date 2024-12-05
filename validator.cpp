#include "validator.h"

Validator::Validator() {}
                                                        
double Validator::Validate(const vector<Instance>& data, Classifier& classifier) {
    int rightPredictionCount = 0;

    for (int i = 0; i < data.size(); ++i) {
        vector<Instance> trainingData = createSubset(data, i);
        Instance testing = data[i];

        classifier.Train(trainingData);

        // does this work?
        int predicted = classifier.Test(testing.features);

        // Check if the prediction is correct
       // if (predicted == i'm not sure what to compare it with) {
           // ++rightPredictionCount;
        //}
    }

    // return accuracy 
    return static_cast<double> (rightPredictionCount) / data.size();
}


// this function creates the subset by iterating through the dataset and excluding the specified instance 
vector<Instance> Validator::createSubset(const vector<Instance>& data, int indexToExclude) {
    // new subset vector created to store the instances (will be returned at the end)
    vector<Instance> newSubset;

    // this loop iterates through the data and adds the instances to the new subset while excluding the specified one
    for(int i = 0; i < data.size(); ++i) {
        if(i != indexToExclude) {
            newSubset.push_back(data[i]);
        }
    }
    
    return newSubset;
}

