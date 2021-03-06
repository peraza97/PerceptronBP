#ifndef __PREDICTOR_H__
#define __PREDICTOR_H__

#include <cstdio>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "util.h"
#include "perceptron.h"

using namespace std;

typedef unordered_map<uint32_t, Perceptron> perceptronTable;

class Predictor{
    private:
        //global history
        int historyLength;
        uint64_t history; 
        //perceptron table
        perceptronTable table;
        int tableSize;
        //threshold
        int theta;
        //misc
        int correct;
        int total;
        bool debug;

        uint32_t hashAddress(string);
        void updateHistory(int);
    
    public:
        Predictor(int, int, bool);
        void makePrediction(string, int);
        void printRates();
};

#endif