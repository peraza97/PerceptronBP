#ifndef __PREDICTOR_H__
#define __PREDICTOR_H__

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include "util.h"
#include "perceptron.h"

using namespace std;

typedef unordered_map<uint64_t, Perceptron> perceptronTable;

class Predictor{
    private:
        //global history
        int globalHistoryLength;
        uint64_t history; 
        //keep track of address length
        int addressBits;
        //rates
        int correct;
        int total;
        bool debug;
        //perceptron table
        perceptronTable table;
        double theta;

        uint64_t hashAddress(string);
        void updateHistory(int);
    
    public:
        Predictor(int, int, bool);
        void makePrediction(string, int);
        void printRates();
};

#endif