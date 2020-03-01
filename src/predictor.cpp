#include "predictor.h"

Predictor::Predictor(int globalHistory, int addressBits, bool debug){
    this->history = 0;
    this->globalHistoryLength = globalHistory;
    this->addressBits = addressBits;
    this->correct = 0;
    this->total = 0;
    this->debug = debug;
}

void Predictor::updateHistory(int expected){
    bool converted = (expected == 1 ? 1 : 0);
    this->history = this->history << 1;
    this->history = this->history | converted;
    history = history << (64 - this->globalHistoryLength);
    history = history >> (64 - this->globalHistoryLength);
}

uint64_t Predictor::hashAddress(string address){
    return 0;
}

void Predictor::makePrediction(string input, int expected){
    if(this->debug){
        printf("------------------------------------------\n");  
        printf("Address: 0x%s,  expected: %d\n", input.c_str(), expected);
    }
    uint64_t prevHistory = this->history;
    uint64_t index = this->hashAddress(input); //hash the address for an index


    updateHistory(expected);
    if(this->debug){
        printf("Previous History: %s\n", getBinary(prevHistory,this->globalHistoryLength).c_str());
        printf("New History     : %s\n", getBinary(this->history, this->globalHistoryLength).c_str());
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