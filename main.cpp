//RESULTS
//Group: Austin Le - ale193, Andrew Permatigari - aperm003, Michelle Sun - msun082
// Small Dataset Results:
//          -   Forward: Feature Subset: {5, 3} Acc: 92%
//          -   Backward: Feature Subset: {3, 5} Acc: 92%
// Large Dataset Results:
//          -   Forward: Feature Subset: {27, 1} Acc: 95.5% 
//          -   Backward: Feature Subset: {3, 7, 8, 9, 11, 12, 13, 17, 20, 24, 25, 26, 28, 31, 35, 36, 37, 38, 39, 40} Acc: 76%
// Titanic Dataset Results:
//          -   Forward: Feature Subset: {2} Acc: 78.0112%
//          -   Backward: Feature Subset: {2} Acc: 78.0112%
#include <iostream>
#include <random>
#include <cmath>    
#include <cstdlib> 
#include <vector> 
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono> //Library used to measue time for execution
#include "classifier.h"
#include "validator.h"
using namespace std;

//We're going to create a struct that will hold our instances initially because it will hold the list of features, 
//the classifier, the ID, and accuracy. We can jsut simply modify node a bit and use it to store our data and we can then have a
//classifier object hold all our nodes for us.
class Node {
    public:
        Node() {
            percentage = 0;
        }
        //adds number to list
        void addValue(int num) {
            numList.push_back(num);
        }

        //returns value of number at index i
        int getValueAtIndex(int index) {
            return numList.at(index);
        }

        //returns true if the list contains the number in the function
        bool numWithin(int num) {
            for(int i = 0; i < numList.size(); ++i) {
                if(num == numList.at(i)) {
                    return true;
                }
            }
            return false; 
        }

        //No need for stub evaluation function, use validator
        void evaluation(vector<Instance> records) {
            //Sets percenatge to values between 0 and 100
            // percentage = static_cast<double>(rand()) / RAND_MAX * 100.0;
            // percentage = round(percentage * 10.0) / 10.0;
            //Now using validator for evaluation
            percentage = v.Validate(numList, records, NN);
        }

        double getEvaluation() {
            return percentage* 100; //to get whole value instead of decimal
        }

        int sizeOfNode() {
            return numList.size();
        }

        void printNums() {
            for(int i = 0; i < numList.size() ; ++i) {
                if((numList.size() == 1) || (i == numList.size() - 1)) {
                    cout << numList.at(i);
                }
                else {
                    cout << numList.at(i) << ", ";
                }
            }
        }

        void resetPercentage() {
            percentage = 0.0;
        }

        vector<int> numList; //list of feature subsets
        double percentage;
        Classifier NN;
        Validator v;
};

void NormalizeData(vector<Instance>& records, int numFeatures);
Node ForwardSelection(vector<int> featuresList, vector<Instance> records);
Node BackwardElimination(vector<int> featuresList, vector<Instance> records);
Node meetInMiddleAlgorithm(vector<int> featuresList, vector<Instance> records);

int main() {
    srand(time(0)); 
    string fileName;
    int algo;
    int numFeatures = 0;
    int numInstances = 0;
    string line;
    Node bestNode;
    Classifier classifier;
    Validator v;
    vector<Instance> records; //Holds all of our lines of data
    Instance unseen; //unseeen instance used for testing
    
    cout << "Welcome to the Feature Selection Algorithms" << endl;
    cout << "Select file to test: ";
    getline(cin, fileName);
    cout << fileName << endl;

    ifstream data(fileName); //open file

    //After opening the file and checking if it works, we must parse through the file and extract the all the data in the way we want 
    //The first column of data contains the classification, while everything after contains the features
    //We must also normalize the data that comes after the classifier 
    if(!data.is_open()) { //Check if file is opened properly
        cout << "Error opening the file!" << endl;
        return 1;
    }
    else { //File opened correctly
        //cout << "Opening file: " << fileName << endl << endl;
        int i = 0;
        while (getline(data, line)) {
            //Now we extract and parse the data and get its classifier and the features
            Instance temp;
            double num;
            
            //Use stringstream to easily parse the string number by number
            stringstream stream(line);// Sets to line to be parsed with stringstream
            stream >> num; //Gets first column which is the classifier 
            temp.classType = num;

            //Get the other columns with the features
            while(stream >> num){ 
                temp.features.push_back(num);
            }

            //setting ID
            temp.ID = i;
            ++i;
            //Now store temp into records to hold all data line by line to be normalized later
            records.push_back(temp);
        }
    }

    data.close(); //Closes file DONT FORGET TO DO THIS
    
    cout << endl;
    cout << "Type the number of the algorithm you want to run: " << endl;
    cout << "(1) Forward Selection" << endl;
    cout << "(2) Backward Elimination" << endl;
    cout << "(3) Meet in the Middle Algorithm" << endl; //Custom Feature selection we made that combines forward and backwards
    cin >> algo;
    cout << endl;

    //get number of features, since all have the same number fo features, just use the frist instance
    numFeatures = records.at(0).features.size();
    numInstances = records.size();
    cout << "This dataset has " << records.at(0).features.size() << " features (not including the class attribute), with " << numInstances << " instances." << endl;


    //Now we normalize the data
    cout << "Please wait while I normalize the data";
    NormalizeData(records, numFeatures);
    cout << "... Done!" << endl << endl;

    //Used for extracting data in .csv file for plotting, can uncomment when using.
    // ofstream plotFile("forwardselection.csv");
    // if (plotFile.is_open()) {
    //     for(int i = 0; i < numFeatures; ++i) {
    //         if(i == 1) {
    //             for(int j = 0; j < records.size(); ++j) {
    //             plotFile << records.at(j).classType << ' ';
    //             }
    //             plotFile << endl;
    //             for(int k = 0; k < records.size(); ++k) {
    //             plotFile << records.at(k).features.at(i) << ' ';
    //             }
    //             plotFile << endl;
    //         }
    //     }
        
    //    //plotFile << "Hello WOrld";
    // }
    // else{
    //     cout << "Couldnt open file forward selection.csv";
    // }
    // plotFile.close();

    //Create vector of all possible beginning features
    vector<int> featuresList;
    for(int i = 1; i <= numFeatures; ++i) {
        featuresList.push_back(i);
    }

    if(algo == 1) { //if 1 is chosen, perform forward selection
        cout <<"Foroward Selection: " << endl << endl;
        cout << "Running nearest neighbor with no features (default rate), using \"leaving-one-out\" evaluation, I get an accuracy of ";
        bestNode = ForwardSelection(featuresList, records);
    }
    else if(algo == 2) { // else if 2 is chosen run Backward elimination
        cout << "Backward Elimination: " << endl << endl;
        cout << "Running nearest neighbor with all features (default rate), using \"leaving-one-out\" evaluation, I get an accuracy of ";
        bestNode = BackwardElimination(featuresList, records);
    }
    else if(algo == 3) { // else if 2 is chosen run new algorithm (forward and backward, meet in the middle)
        cout << "Hyrbid Algorithm: " << endl << endl;
        cout << "Running nearest neighbor with all features (default rate), using \"leaving-one-out\" evaluation, I get an accuracy of ";
        bestNode = meetInMiddleAlgorithm(featuresList, records);
    }

    cout << "Finished Search! The Best feature subset is {";
    bestNode.printNums();
    cout << "}, which has an accuracy of " << bestNode.getEvaluation() << "%" << endl;

    return 0;
}

void NormalizeData(vector<Instance>& records, int numFeatures) {
    //z-score normalization
    // vector<double> mean;
    // vector<double> stdDev;
    // vector<double> sum;

    // for(int i = 0; i < numFeatures; ++i) { //gets sum for mean
    //     double val;
    //     for(int j = 0; j < records.size(); ++j) {
    //         val += records.at(j).features.at(i);
    //     }
    //     sum.push_back(val);
    // }


    // for(int i = 0; i < numFeatures; ++i) { //gets mean for each feature
    //     mean.push_back((sum.at(i) / records.size()));
    // }


    // for(int i = 0; i < numFeatures; ++i) { //gets part of std deviation
    //     double val;
    //     for(int j = 0; j < records.size(); ++j) {
    //         val += pow(records.at(j).features.at(i) - mean.at(i), 2);
    //     }
    //     stdDev.push_back(val);
    // }


    // for(int i = 0; i < numFeatures; ++i) { //gets std deviation for each feature
    //     stdDev.at(i) = sqrt(stdDev.at(i) / records.size());
    // }


    // for(int i = 0; i < numFeatures; ++i) { //normalizes the data with the mean and standard deviation
    //     for(int j = 0; j < records.size(); ++j) {
    //         records.at(j).features.at(i) = (records.at(j).features.at(i) - mean.at(i)) / stdDev.at(i);  
    //     }
    // }


    //Standard normalizing method(this one gets better results)
    //First we have to find the min and max of each feature
    vector<double> max; //Holds max values of all features 
    vector<double> min; //Holds min values of all features
    double maxHolder = 0; 
    double minHolder = 0;
    double value = 0;;

    for(int i = 0; i < numFeatures; ++i) { //Loop through features and get min and max values
        maxHolder = 0;
        minHolder = 0;
        for(int j = 0; j < records.size(); ++j) { //Loop through each instance at that specific feature
            value = records.at(j).features.at(i);
            if(value > maxHolder) {
                maxHolder = value;
            }

            if(value < minHolder) {
                minHolder = value; 
            }
            //Once this loop finsihes completely, we now have the max and min values for that feature
        }
        max.push_back(maxHolder);
        min.push_back(minHolder);
    }

    //Now we normalize each data point
    for(int i = 0; i < numFeatures; ++i) {
        for(int j = 0; j < records.size(); ++j) {
            records.at(j).features.at(i) = (records.at(j).features.at(i) - min.at(i)) / (max.at(i) - min.at(i));
        }
    } 
}   

Node ForwardSelection(vector<int> featuresList, vector<Instance> records) {
    //We're creating the forward selection algorithm(greedy)
    //Starts with empty set, then add's all features and continues to expand the node with highest evaluation with all its possibilities until reach a goal state
    Node bestNode;    //Highest percentage node in all the possibilites
    Node currentBest; //Highest percentage out of all nodes in their current depth
    vector<int> vectorOfPrev; //Since once finding the first node that is highest, all other features will be added to that individual node
    Validator v;
    Classifier nearestNeighbor;

    bestNode.evaluation(records);//This will originally try to classify a node with no features, so accuracy should be 0
    cout << bestNode.getEvaluation() << "%" << endl << endl;
    int depths = featuresList.size(); // The number of depths that the algorithm should search is the num of features there are, this is also the depth of the goal state(all features)
    cout << "Beginning search: " << endl << endl;

    //Must find node at first depth because that node's vector values will be built upon by the other features
    currentBest = bestNode;
    vectorOfPrev = currentBest.numList; //Sets the best vector list for the current depth

    //After, loop until you reach goal state
    while(depths > 0) {
        cout << endl;
        cout << "Feature Set {";
        currentBest.printNums();
        cout << "} was best, accuracy is " << currentBest.getEvaluation() << "%" << endl << endl;
        currentBest.resetPercentage(); //Reset the percentage so the first node of each dpeth will be the currentBest
        for(int i = 0; i < featuresList.size(); ++i) {
            Node temp;
            temp.numList = vectorOfPrev;
            if(temp.numWithin(featuresList.at(i))) {
                continue;
            }
            else {
                temp.addValue(featuresList.at(i));
                temp.evaluation(records); //use validation to get accuracy percentage
            }

            if(temp.getEvaluation() > currentBest.getEvaluation()) {
                currentBest = temp;
            }

            cout << "\tUsing feature(s) {";
            temp.printNums();
            cout << "} accuracy is " << temp.getEvaluation() << "%" << endl;
        }

        vectorOfPrev = currentBest.numList; //Gets the best node's values and places it within this variable to be used in the next depth
        if(currentBest.getEvaluation() > bestNode.getEvaluation()) {
            bestNode = currentBest;
        }
        else { //Evaluation drops so notify user
            cout << endl;
            cout << "(Warning, Accuracy Has Decreased! Continuing search in case of local maxima.)" << endl;
        }
        --depths;
    }
    cout << endl << endl;

    return bestNode;
}


Node BackwardElimination(vector<int> featuresList, vector<Instance> records) {
    //Implementing backwards elimination(greedy)
    //Starts with all possible features in one set, then chooses highest evaluated node and continue to eliminate one feature from it until its an empty set
    Node bestNode;
    Node currentBest;
    vector<int> vectorOfPrev;
    Validator v;
    Classifier nearestNeighbor;

    //Must add all features to starting node and that would be our best node for now
    bestNode.numList = featuresList;
    bestNode.evaluation(records);//This will originally try to classify a node with all the features
    cout << bestNode.getEvaluation() << "%" << endl << endl;
    int depths = featuresList.size(); // The number of depths that the algorithm should search is the num of features there are, this is also the depth of the goal state
    cout << "Beginning search: " << endl << endl;

    vectorOfPrev = bestNode.numList;
    currentBest = bestNode;

    // The while loop iterates through the depths and finds the best subset of features based on their accuracy  
    // decrement the depth every iteration until it reaches 0 to correctly iterate through all the depths
    while(depths > 0) {
        cout << endl;
        cout << "Feature Set {";
        currentBest.printNums();
        cout << "} was best, accuracy is " << currentBest.getEvaluation() << "%" << endl << endl;
        currentBest.resetPercentage(); //Reset the percentage so the first node of each dpeth will be the currentBest

        for(int i = 0; i < vectorOfPrev.size(); ++i) {
            Node temp;
            temp.numList = vectorOfPrev;
            temp.numList.erase(temp.numList.begin() + i);
            temp.evaluation(records);//use validation to get accuracy percentage

            if(i == 0) { //Starting currentLowest
                currentBest = temp;
            }

            if(temp.getEvaluation() > currentBest.getEvaluation()) {
                currentBest = temp;
            }
            //Print out values
            cout << "\tUsing feature(s) {";
            temp.printNums();
            cout << "} accuracy is " << temp.getEvaluation() << "%" << endl; 
        }
        vectorOfPrev = currentBest.numList; //Gets the best node's values and places it within this variable to be used in the next depth
        if(currentBest.getEvaluation() > bestNode.getEvaluation()) {
            bestNode = currentBest;
        }
        else { //Evaluation drops so notify user
            cout << endl;
            cout << "(Warning, Accuracy Has Decreased! Continuing search in case of local maxima.)" << endl;
        }
        --depths;
    }
    cout << endl << endl;

    return bestNode;
}

Node meetInMiddleAlgorithm(vector<int> featuresList, vector<Instance> records) {
    Node forwardNode, backwardNode;
    forwardNode.evaluation(records);
    backwardNode.numList = featuresList;
    backwardNode.evaluation(records); //Intial evaluation for backwards section

    Validator v;
    Classifier nearestNeighbor;
    Node bestNode;

    vector<int> availableFeatures = featuresList;
    int totalFeatures = featuresList.size();
    int iterations = totalFeatures / 2; //divide by 2 to get the middle

    //Set best Node to highest evaluation of the starting nodes
    if(backwardNode.getEvaluation() > forwardNode.getEvaluation()) {
        bestNode = backwardNode;
    }
    else {
        bestNode = forwardNode;
    }
    cout << bestNode.getEvaluation() << "%" << endl << endl;
    int depths = featuresList.size(); // The number of depths that the algorithm should search is the num of features there are, this is also the depth of the goal state
    cout << "Beginning search: " << endl << endl;


    // looped for half of the total features so that each algorithm can run till the middle
    for(int i = 0; i < iterations; ++i) {
        cout << endl;
        cout << "Feature Set {";
        bestNode.printNums();
        cout << "} was best, accuracy is " << bestNode.getEvaluation() << "%" << endl << endl;
        cout << endl;

        // Forward Selection
        Node currentBestForwardNode;
        currentBestForwardNode.resetPercentage();

        cout << "Starting forward selection: " << endl;
        for(int j = 0; j < availableFeatures.size(); ++j) {
            int feature = availableFeatures.at(j);
            Node temp = forwardNode; // create temp node to evaluate new feature set
            if(!forwardNode.numWithin(feature)) {
                temp.addValue(feature); // add feature to current set
                //temp.percentage = v.Validate(temp.numList, records, nearestNeighbor); 
                temp.evaluation(records);
                if(temp.getEvaluation() > currentBestForwardNode.getEvaluation()) { 
                    currentBestForwardNode = temp;
                }
                //Print out values
                cout << "\tUsing feature(s) {";
                temp.printNums();
                cout << "} accuracy is " << temp.getEvaluation() << "%" << endl; 
            }
        }
        forwardNode = currentBestForwardNode;

        //Backward Elimination
        Node currentBestBackwardNode;
        currentBestBackwardNode.resetPercentage();

        cout << "Starting Backward Elimination: "<< endl;
        for(int i = 0; i < backwardNode.numList.size(); ++i) {
            Node temp = backwardNode;
            temp.numList.erase(temp.numList.begin() + i); // remove feature at index
            temp.evaluation(records);
            if(temp.getEvaluation() > currentBestBackwardNode.getEvaluation()) {
                currentBestBackwardNode = temp;
            }
            //Print out values
            cout << "\tUsing feature(s) {";
            temp.printNums();
            cout << "} accuracy is " << temp.getEvaluation() << "%" << endl; 
        }
        backwardNode = currentBestBackwardNode;
        cout << endl;
    

        Node currentBest;
        if (currentBestForwardNode.getEvaluation() > currentBestBackwardNode.getEvaluation()) {
            currentBest = currentBestForwardNode; // Use forward node 
        } 
        else {
            currentBest = currentBestBackwardNode; // Use backward node 
        }
        
        cout << "Best sub feature from forwards and backwards is feature(s): {";
        currentBest.printNums();
        cout << "}, accuracy is: " << currentBest.getEvaluation() << "%" << endl << endl;

        if(currentBest.getEvaluation() > bestNode.getEvaluation()) {
            bestNode = currentBest;
        }
        else {
            cout << endl;
            cout << "(Warning, Accuracy Has Decreased! Continuing search in case of local maxima.)" << endl;
        }
    } 
    cout << endl;  
    return bestNode;
}