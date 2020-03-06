#include "perceptron.h" 
Perceptron::Perceptron(){
    this->inputSize = 0;
}
Perceptron:: Perceptron(int inputSize): inputSize(inputSize), weights(inputSize,0){
}

void Perceptron::init(int size){
    this->inputSize = size;
    this->weights = vector<int>(inputSize, 0);
}

int Perceptron::getInputSize(){
    return this->inputSize;
}


string Perceptron::str(){
    ostringstream os;
    for(int i = 0; i < this->inputSize; ++i){
        if(i != this->inputSize - 1){
            os << this->weights[i] << ", ";
        }
        else{
            os << this->weights[i];
        }
    }
    return os.str();
}

int Perceptron::predict(uint64_t history){
    int sum = this->weights[0];
    for(int i = 1; i < this->inputSize; ++i){ //w1...wn
        unsigned char value = history & (1 << i);
        if(value){
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

void Perceptron::updateWeights(uint64_t history, int result, int expected, double theta){
    if( ((result ^ expected) < 0) || abs(result) < theta){
        for(int i = 1; i < this->inputSize; ++i){ //w1...wn
            unsigned char value = history & (1 << i);
            if((value && expected == 1) || (!value && expected == -1)){ 
                this->weights[i] += 1;
            }
            else{
                this->weights[i] -= 1;
            }
        }
    }
}