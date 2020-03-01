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
        int theta;
        PerceptronWeights weights;
    
    public:
        Perceptron(int, int);
        int predict(uint64_t);
        int updateWeights(int, int);
        void printWeights();
};

#endif