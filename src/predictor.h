#ifndef __PREDICTOR_H__
#define __PREDICTOR_H__

#include <cstdio>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "util.h"
#include "perceptron.h"

using namespace std;

typedef uint32_t nSize_t;

typedef unordered_map<nSize_t, Perceptron> perceptronTable;

class Predictor{
    private:
        //global history
        int historyLength;
        uint64_t history; 
        //how many bits should we address
        int addressBits;
        //perceptron table
        perceptronTable table;
        //threshold
        double theta;
        //misc
        int correct;
        int total;
        bool debug;

        nSize_t hashAddress(string);
        void updateHistory(int);
    
    public:
        Predictor(int, int, bool);
        void makePrediction(string, int);
        void printRates();
};

#endif