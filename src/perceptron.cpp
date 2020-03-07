#include "perceptron.h" 
Perceptron::Perceptron(){
    this->inputSize = 0;
    this->debug = false;
    this->prevStep = 0;
}
Perceptron:: Perceptron(int inputSize): inputSize(inputSize), weights(inputSize,0), debug(false), prevStep(0){
}

void Perceptron::init(int size, bool debug){
    this->inputSize = size;
    this->weights = vector<int>(inputSize, 0);
    this->debug = debug;
    this->prevStep = 0;
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
        if(this->debug){
            printf("Summation: %d + ", sum);
        }
    for(int i = 1; i < this->inputSize; ++i){ //w1...wn
        unsigned char value = history & (1 << (i-1)); //check the history
        if(this->debug){
            printf("(%d * %d)%s", value ? 1 : -1, this->weights[i], i <this->inputSize - 1 ? " + " : " ");
        }
        if(value){
            sum += this->weights[i];
        }
        else{
            sum -= this->weights[i];
        }
    }
    this->prevStep = abs(sum);
    if(this->debug){
        printf("\nPrediction sum: %d\n", sum);
    }
    if(sum >= 0){
        return 1;
    }
    return -1;
}

void Perceptron::updateWeights(uint64_t history, int result, int expected, int theta){
    if(this->debug){
        printf("Sign(Y_out) != expected: %d\n",(result ^ expected) < 0 ? 1 : 0);
        printf("prevStep < theta: %d\n",(this->prevStep < theta) ? 1: 0);
    }

    if(((result ^ expected) < 0) || this->prevStep < theta){
        if(expected == 1){
            this->weights[0] += 1;
        }
        else{
            this->weights[0] -= 1;
        }
        for(int i = 1; i < this->inputSize; ++i){ 
            unsigned char value = history & (1 << (i-1));
            if((value && expected == 1) || (!value && expected == -1)){  //if the history and output match
                this->weights[i] += 1;
            }
            else{
                this->weights[i] -= 1;
            }
        }
    }
}