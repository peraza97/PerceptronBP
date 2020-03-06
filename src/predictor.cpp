#include "predictor.h"

Predictor::Predictor(int globalHistory, int addressBits, bool debug){
    this->history = 0;
    this->historyLength = globalHistory;
    this->addressBits = addressBits;
    this->correct = 0;
    this->total = 0;
    this->debug = debug;
    this->theta = 1.93 * this->historyLength + 14;

    printf("------------------------------\n");
    printf("Global history: %d\nAdress bits: %d\nThreshold: %.2f\n",this->historyLength, this->addressBits, this->theta);
    printf("------------------------------\n");
}

void Predictor::updateHistory(int expected){
    bool converted = (expected == 1 ? 1 : 0);
    this->history = this->history << 1;
    this->history = this->history | converted;
    history = history << (64 - this->historyLength);
    history = history >> (64 - this->historyLength);
}

nSize_t Predictor::hashAddress(string address){
    return 0;
}

void Predictor::makePrediction(string input, int expected){
    if(this->debug){
        printf("------------------------------------------\n");  
        printf("Address: 0x%s,  expected: %d\n", input.c_str(), expected);
    }
    uint64_t prevHistory = this->history;
    uint64_t index = this->hashAddress(input); //hash the address for an index
    //check if it is in the table
    if(this->table[index].getInputSize() == 0){
        this->table[index].init(this->historyLength+1);
    }
    //get the prediction
    int prediction = this->table[index].predict(prevHistory);
    //update the perceptron weights
    string prevWeights = this->table[index].str();
    this->table[index].updateWeights(this->history, prediction, expected, this->theta);
    //update history
    this->updateHistory(expected);
    if(this->debug){
        printf("------------------------------------------\n");  
        printf("Address: 0x%s,  expected: %d\n", input.c_str(), expected);
        printf("Previous History: %s\n", getBinary(prevHistory,this->historyLength).c_str());
        printf("Previous weights: %s\n", prevWeights.c_str());
        printf("Prediction: %d\n", prediction);
        printf("Updated  weights: %s\n", this->table[index].str().c_str());
        printf("New History     : %s\n", getBinary(this->history, this->historyLength).c_str());
    }
}


void Predictor::printRates(){ 
    printf("------------------------------------------\n"); 
    if(total == 0){
        printf("Error, Cannot get rate \n");
    }
    else{
        printf("Misclassification rate: %.2f%%\n", 100.00 * (1 - (double)(this->correct)/this->total));
    } 
}