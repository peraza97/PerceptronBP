#include "predictor.h"

Predictor::Predictor(int globalHistory, int tableSize, bool debug){
    this->history = 0;
    this->historyLength = globalHistory;
    this->tableSize = tableSize;
    this->correct = 0;
    this->total = 0;
    this->debug = debug;
    this->theta = floor(1.93 * this->historyLength + 14);

    printf("------------------------------\n");
    printf("Global history: %d\nThreshold: %d\nTable Size: %d\n",this->historyLength, this->theta, this->tableSize);
    printf("------------------------------\n");
}

void Predictor::updateHistory(int expected){
    bool converted = (expected == 1 ? 1 : 0);
    this->history = this->history << 1;
    this->history = this->history | converted;
    history = history << (64 - this->historyLength);
    history = history >> (64 - this->historyLength);
}

uint32_t Predictor::hashAddress(string address){
    istringstream converter(address);
    uint32_t conversion;
    converter >> std::hex >> conversion; 
    conversion %= this->tableSize;
    return conversion ^ (this->history % this->tableSize);
}

void Predictor::makePrediction(string input, int expected){
    if(this->debug){
        printf("------------------------------------------\n");  
        printf("Address: 0x%s,  expected: %d\n", input.c_str(), expected);
    }
    uint64_t prevHistory = this->history;
    uint64_t index = this->hashAddress(input); 
    //check if it is in the table
    if(this->table[index].getInputSize() == 0){
        this->table[index].init(this->historyLength+1, this->debug);
    }
    //get the prediction
    int prediction = this->table[index].predict(prevHistory);
    this->table[index].updateWeights(this->history, prediction, expected, this->theta);
    
    //update history
    this->updateHistory(expected);

    if(prediction == expected){
        this->correct += 1;
    }
    this->total += 1;

    if(this->debug){
        printf("Previous History: %s\n", getBinary(prevHistory,this->historyLength).c_str());
        printf("Updated  weights: %s\n", this->table[index].str().c_str());
        printf("New History     : %s\n", getBinary(this->history, this->historyLength).c_str());
        printf("Prediction: %d\n", prediction);
        printf("%s\n", prediction == expected ? "Correct" : "Wrong");
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