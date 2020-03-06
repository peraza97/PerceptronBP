#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include "app.h"
#include "predictor.h"
#include "perceptron.h"

using namespace std;

int main(int argc, char ** argv){
	int opt;
	int historyLength = 6; 
    int addressBits = 10;
    bool debug = false;
	string fileName = "text/test.txt";
	while ((opt = getopt(argc,argv,"f:m:a:d")) != EOF){
        switch(opt){
            case 'f': fileName.assign(optarg); break;
            case 'm': historyLength = atoi(optarg); break;
            case 'a': addressBits = atoi(optarg); break;
            case 'd': debug = true; break;
            case '?': printf("usuage is \n -f : fileName \n -m : history length\n -a : address length\n");
            default: exit(1);
        }
    }
    Application app(fileName);
    app.InitApplication();
    Predictor myPerceptron(historyLength, addressBits, debug);
    string address = "";
    int expected;
    while(app.getBranch(address,expected)){
        myPerceptron.makePrediction(address,expected);
    }




    return 0;
}