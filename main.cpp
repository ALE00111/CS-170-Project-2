#include <iostream>
#include <random>
#include <cmath>    
#include <cstdlib> 
#include <vector> 
#include <unordered_map>
using namespace std;

class Node {
    public:
        Node() {
            //Want to get range of values from 50 to 100
            percentage = 0;
        }

        void addValue(int num) {
            numList.push_back(num);
        }

        int getValueAtIndex(int index) {
            return numList.at(index);
        }

        bool numWithin(int num) {
            for(int i = 0; i < numList.size(); ++i) {
                if(num == numList.at(i)) {
                    return true;
                }
            }
            return false; 
        }

        void evaluation() {
            percentage = rand() % (51) + 50;
        }

        int getEvaluation() {
            return percentage;
        }
        
    private:
        vector<int> numList;
        int percentage;
};


double ForwardSelection(vector<int> featuresList);
double BackwardElimination(vector<int> featuresList);

// bool isGoal(vector<int> goalState, vector<Node> list) {
//         for(int i = 0; i < list.size(); ++i) {
//             for(int j = 0; j < )
//             if(list.at(i).getValueAtIndex(i) != goalState.at(i)) {
//                 return false;
//                }
//         }
//         return true;
// }

int main() {
    srand(time(0)); 
    int numFeatures;
    int algo;


    cout << "Welcome to the Feature Selection ALgorithms" << endl;
    cout << "Please enter a number of features: ";
    cin >> numFeatures;
    cout << endl;
    cout << "Which algorithm would you like to use?: " << endl;
    cout << "(1) Forward Selection" << endl;
    cout << "(2) Backward Elimination" << endl;
    cin >> algo;
    cout << endl;

    cout << "Using no features and \"random\" evaluation, I get an accuracy of ";
    // v2 = static_cast<double>(rand()) / RAND_MAX * 100.0;
    //v2 = rand() % (51) + 50;
    // v2 = round(v2 * 10) / 10.0;
    // v2 = rand() % 100 + 1;

    //Create vector of all possible beginning features
    vector<int> featuresList;
    for(int i = 1; i <= numFeatures; ++i) {
        featuresList.push_back(i);
    }

    if(algo == 1) {
        ForwardSelection(featuresList);
    }
    else if(algo == 2) {
        BackwardElimination(featuresList);
    }

    return 0;
}

// int evaluation() {
//     //For now it will return a random number between 50 to 100
//     return rand() % (51) + 50;
// }

double ForwardSelection(vector<int> featuresList) {
    //We're creating the forward selection algorithm
    //ALL WORK IN PROGRESS
    vector<Node> listOfNodes;
    Node bestNode;    //Highest percentage node in all the possibilites
    Node currentBest; //Highest percentage out of all nodes in their current depth
    int indexOfCurrent;
    bestNode.evaluation();
    cout << bestNode.getEvaluation() << "%" << endl;


    vector<int> goalState;
    for(int i = 0; i < featuresList.size(); ++i) {
        Node temp;
        temp.addValue(featuresList.at(i));
        temp.evaluation();
        if(temp.getEvaluation() > currentBest.getEvaluation()) {
            currentBest = temp;
            indexOfCurrent = i;
        }
        listOfNodes.push_back(temp);
        goalState.push_back(featuresList.at(i));

        if(i == 0) {
            currentBest = temp;
        }
    }
    
    if(currentBest.getEvaluation() > bestNode.getEvaluation()) {
        bestNode = currentBest;
    }
    

    //From here, we've expanded to our first level with only one value in each node and now we'll take the bestNode and remove it from our vector
    //and add their value to the other nodes to expand them. The value we want to add to the other nodes is the one that is in currentBestNode 
    //in that depth and it'll always be the node at the front of the list


    //Our goal is to stop when we searched to the point where the listOfNodes contains a node that has the values of all the features(goalState)

    return 100.0;
}


double BackwardElimination(vector<int> featuresList) {
    return 100.0;
}