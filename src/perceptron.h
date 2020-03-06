#ifndef __PERCEPTRON_H__
#define __PERCEPTRON_H__

#include <cstdio>
#include <vector>
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
        int updateWeights(int, double, int);
        void printWeights();
};

#endif