#include "perceptron.h"

Perceptron:: Perceptron(int inputSize, int theta): inputSize(inputSize), theta(theta), weights(inputSize,1){}

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

int Perceptron::updateWeights(int result, int expected){
    return 0;
}