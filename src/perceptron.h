#ifndef __PERCEPTRON_H__
#define __PERCEPTRON_H__

#include <cstdio>
#include <vector>
#include <sstream>
#include "util.h"

using namespace std;

typedef vector<int> PerceptronWeights;

class Perceptron{
    private:
        int inputSize;
        PerceptronWeights weights;
    
    public:
        Perceptron();
        Perceptron(int);
        int getInputSize();
        void init(int);
        int predict(uint64_t);
        void updateWeights(uint64_t, int, int, double);
        string str();
};

#endif