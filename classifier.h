#include <iostream>
#include <fstream>
#include <vector>
using namespace std; 


//This class is used to hold training instances in memory and use NN
//Use Euclidean distance to measure the distance between two points
//This done by having a eucilidean distance be calcualted with a space of 10
//For each instance of data, it will contain subset of features it has, the class label, and its current position 

struct Instance {
    double classifier;
    int ID;
    vector<double> restOfData; 
};

class Classifier {
    public:
        Classifier();
        void Train(vector<Instance> data); //function for inputting training instances that will be stored
        int Test(vector<Instance> unseen); //function for inputting test instances and output is the prdicted class label
    private:
        
};

