#include <iostream>
#include <random>
#include <cmath>    
#include <cstdlib> 
#include <vector> 
#include <unordered_map>
#include <algorithm>
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
            //Sets percenatge to values between 0 and 100
            percentage = static_cast<double>(rand()) / RAND_MAX * 100.0;
            percentage = round(percentage * 10.0) / 10.0;
        }

        double getEvaluation() {
            return percentage;
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

        vector<int> numList;
        double percentage;
};


Node ForwardSelection(vector<int> featuresList);
Node BackwardElimination(vector<int> featuresList);

int main() {
    srand(time(0)); 
    int numFeatures;
    int algo;
    Node bestNode;


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
        bestNode = ForwardSelection(featuresList);
    }
    else if(algo == 2) {
        bestNode = BackwardElimination(featuresList);
    }

    cout << "Finished Search! The Best feature subset is {";
    bestNode.printNums();
    cout << "}, which has an accuracy of " << bestNode.getEvaluation() << "%" << endl;

    return 0;
}

bool isGoalState(vector<Node> listOfNodes, vector<int> featuresList) {
    for(int i = 0; i < listOfNodes.size(); ++i) {
      if(listOfNodes.at(i).sizeOfNode() == featuresList.size()) {
        return true;
      }
    }
    return false; 
}

Node ForwardSelection(vector<int> featuresList) {
    //We're creating the forward selection algorithm(greedy)
    //Starts with empty set, then add's all features and continues to expand the node with highest evaluation with all its possibilities until reach a goal state
    vector<Node> listOfNodes; //List of all nodes with highest percentages in their depths
    Node bestNode;    //Highest percentage node in all the possibilites
    Node currentBest; //Highest percentage out of all nodes in their current depth
    vector<int> vectorOfPrev; //Since once finding the first node that is highest, all other features will be added to that individual node
    bestNode.evaluation();
    cout << bestNode.getEvaluation() << "%" << endl << endl;
    int depths = featuresList.size(); // The number of depths that the algorithm should search is the num of features there are, this is also the depth of the goal state
    listOfNodes.push_back(bestNode); //Adding empty node to list as first
    cout << "Beginning search: " << endl << endl;



    //To find node at first depth because that node's vector values will be built upon by the other features
    for(int i = 0; i < featuresList.size(); ++i) {
        Node temp;

        temp.addValue(featuresList.at(i));
        temp.evaluation();
            
        if(i == 0) {
            currentBest = temp;
        }


        if(temp.getEvaluation() > currentBest.getEvaluation()) {
            currentBest = temp;
        }

        //You can add each node to the list, or only add the nodes that are the best at that current depth
        //listOfNodes.push_back(temp);

        cout << "Using feature(s) {";
        temp.printNums();
        cout << "} accuracy is " << temp.getEvaluation() << "%" << endl;
    }

    listOfNodes.push_back(currentBest);
    if(currentBest.getEvaluation() > bestNode.getEvaluation()) {
        bestNode = currentBest;
    }
    vectorOfPrev = currentBest.numList; //Sets the best vector list for the current depth
    --depths;

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
                temp.evaluation();
            }

            if(temp.getEvaluation() > currentBest.getEvaluation()) {
                currentBest = temp;
            }

            //You can add each node to the list, or only add the nodes that are the best at that current depth
            //listOfNodes.push_back(temp);

            cout << "Using feature(s) {";
            temp.printNums();
            cout << "} accuracy is " << temp.getEvaluation() << "%" << endl;
        }

        listOfNodes.push_back(currentBest);
        vectorOfPrev = currentBest.numList; //Gets the best node's values and places it within this variable to be used in the next depth
        
        if(currentBest.getEvaluation() > bestNode.getEvaluation()) {
            bestNode = currentBest;
        }
        --depths;
    }
    cout << endl << endl;
    
    //Our goal is to stop when we searched to the point where the listOfNodes contains a node that has the values of all the features(goalState)
    //Then return the highest percentage node(bestNode)

    return bestNode;
}


Node BackwardElimination(vector<int> featuresList) {
    //Implementing backwwards elimination(greedy)
    //Starts with all possible features in one set, then elimiantes one feature at a time basedo on lowest evaluation and yo ugo until theres no more features
    Node bestNode;
    Node currentBest;
    vector<Node> listOfNodes;
    vector<int> vectorOfPrev;
    






    return bestNode;
}