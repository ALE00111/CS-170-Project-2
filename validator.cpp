#include "validator.h"
#include <chrono> //Library used to measue time for execution

Validator::Validator() {}

//Parameters include the feature subset that we're specifically using to classify with, data that holds all our instances, and the classifier which is just NN                                                        
//This is the leave one out algorithm that is similar to K-fold cross validation
double Validator::Validate(const vector<int> featureSubset, const vector<Instance> data, Classifier& classifier) {
    int rightPredictionCnt = 0;

    //First we have to create and/or modify our data to only take into account the features within our feature subset and exclude all other features
    //Now we gotta remove all other features that are not within the feature susbset and only add the ones needed into a new data sub set called newDataset

    vector<Instance> newDataset = excludeFeatures(featureSubset, data);

    for (int i = 0; i < data.size(); ++i) {
        // Start the timer per iteration
        auto start = chrono::high_resolution_clock::now();
        cout << "Instance: " << i + 1 << ", ";
        vector<Instance> trainingData = createSubset(newDataset, i);
        Instance testingInstance = newDataset.at(i);

        //First we must train the data, and set it to the training data which we modified to remove an instance 
        classifier.Train(trainingData);

        int predictedClass = classifier.Test(testingInstance);

        cout << "Predicted class: " << predictedClass << ", ";
        cout << "Acutal class: " << data.at(i).classifier << ", ";

        // Check if the prediction is correct
        if (predictedClass == data.at(i).classifier) { //Compare predicted to original
           ++rightPredictionCnt;
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Time to complete iteration in microseconds: " << duration.count() << endl;
    }

    cout << "Results: " << rightPredictionCnt << "/" << data.size() << endl;

    // return accuracy 
    return static_cast<double> (rightPredictionCnt) / data.size();
}

//helper function that returns a new data set that modified our current dataset to only inlcude the features in the feature subset
vector<Instance> Validator::excludeFeatures(vector<int> featureSubset, vector<Instance> dataset) {
    vector<Instance> newDataset(dataset.size()); //set new vector as same size as dataset
    int featureToInclude;

    for(int i = 0; i < featureSubset.size(); ++i) {
        featureToInclude = featureSubset.at(i);
        for(int j = 0; j < newDataset.size(); ++j) {
            newDataset.at(j).classifier = dataset.at(j).classifier;
            newDataset.at(j).features.push_back(dataset.at(j).features.at(featureToInclude - 1)); 
            //Subtract 1 because the features stored on the dataset start at index 0, meaning that feature 1 is at index 0, feature 2 is at index 1, etc...
        }
    }

    return newDataset; //returns new datset that only holds the features in the feature subset
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

