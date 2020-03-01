#include "app.h"

Application::Application(string fileName){
    this->fileName = fileName;
}

void Application::InitApplication(){
    this->inputStream.open(this->fileName.c_str());
    if(!this->inputStream.is_open()){
        cout << "error opening file: " << this->fileName << endl;
        exit(1);
    }   
}

bool Application::getBranch(string &addr, int& result){
    if(!this->inputStream.is_open()){
        return 0;
    }   
    string input1, input2;
    //check if can get input
    if(this->inputStream >> input1 >> input2){
        addr = input1; 
        if(input2 == "T"){
            result = 1;
        }
        else if(input2 == "N"){
            result = -1;
        }
        else{
            printf("ERROR unexpected value: %s\n",input2.c_str());
            exit(1);
        }
        return 1;
    }
    //return 0
    else{
        this->inputStream.close();
        return 0;
    }
}