#include <iostream>
using namespace std; 


//This class is used to hold training instances in memory and use NN
//Use Euclidean distance to measure the distance between two points

class Classifier {
    public:
        Classifier();
        void Train(); //function for inputting training instances
        int Test(); //function for inputting test instances and output is the prdicted class label
    private:

};

