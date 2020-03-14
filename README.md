## Installation

To compile the project, run the following command in the top level directory
```sh
make
```

## Usage
run the following command in the top level directory
```sh
$ ./build/cachesim -f <file> -m <global history length> -n <perceptron table size> 
```
Optional parameters:
* -f : input file 
* -m : global history length
* -n : pereptron table size

### Example
```
$ ./build/perceptron -f ./text/gcc-10K.txt  -m 15 -n 1024
```
