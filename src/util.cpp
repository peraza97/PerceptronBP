#include "util.h"

string getBinary(uint64_t value, int length){
    string bin(64,'*');
    uint64_t temp = value;
    int i;
    for(i = 63; i >= 0; --i){
        bin[i] = temp & 0x01 ? '1' : '0';
        temp >>= 1;
    }
    bin.insert(64-length,1,'|');
    return bin;
}