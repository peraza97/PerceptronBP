#include "perceptron.h"

Perceptron::Perceptron(){
    this->inputSize = 0;
}

int Perceptron::getInputSize(){
    return this->inputSize;
}

void Perceptron::init(int size){
    this->inputSize = size;
    this->weights = vector<int>(inputSize, 0);
}

Perceptron:: Perceptron(int inputSize): inputSize(inputSize), weights(inputSize,0){
}

void Perceptron::printWeights(){
    for(int i = 0; i < this->inputSize; ++i){
        printf("%d ", this->weights[i]);
    }
    printf("\n");
}

int Perceptron::predict(uint64_t history){
    int sum = this->weights[0]; //initial is w0
    for(int i = 1; i < this->inputSize; ++i){ //w1...wn
        unsigned char temp = history & (1 << i);
        if(temp){
            sum += this->weights[i];
        }
        else{
            sum -= this->weights[i];
        }
    }
    if(sum >= 0){
        return 1;
    }
    return -1;
}

int Perceptron::updateWeights(int result, double theta, int expected){
    this->weights[0]+=1;
    return 0;
}