//
// Created by Manuel on 23.04.2016.
//

#ifndef EMBEDDEDSYSTEMSGPS_SUMSIGNAL_H
#define EMBEDDEDSYSTEMSGPS_SUMSIGNAL_H

#include <iostream>
using namespace std;

class SumSignal {

public:
    SumSignal(char fileName[]);
    virtual ~SumSignal();
    int *getSumSignal() {
        return sumSignal;
    }


private:
    int sumSignal[1023];

    void readFile(char fileName[]);
};


#endif //EMBEDDEDSYSTEMSGPS_SUMSIGNAL_H
