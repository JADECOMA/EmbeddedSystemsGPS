//
// Created by Manuel on 23.04.2016.
//

#include "Satellite.h"

#define BIT_1  (1 << 0)
#define BIT_2  (1 << 1)
#define BIT_3  (1 << 2)
#define BIT_5  (1 << 4)
#define BIT_8  (1 << 7)
#define BIT_9  (1 << 8)

#define HIGH_BIT 9

#define INITIAL_VALUE 1023

#define REGISTER_WIDTH 10

Satellite::Satellite() {
    this->init();
}

Satellite::~Satellite() { }

void Satellite::getChipSequences(int (*&returnValue)[24][1024]) {
    returnValue = &chipSequences;
}

void Satellite::init() {
    this->createMotherSequence1();
    this->createMotherSequence2();

    this->initSatelliteRegisters();
    this->createChipSequences();
}

void Satellite::createMotherSequence1() {
    int i = 0;
    int newBit = 0;
    int currentSequence = INITIAL_VALUE;

    while (i <= INITIAL_VALUE) {
        newBit = (currentSequence & BIT_1 ^ (currentSequence & BIT_8) >> 7);
        motherSequence1[i++] = (currentSequence & BIT_1);
        currentSequence >>= 1;
        currentSequence |= (newBit << HIGH_BIT);
    }
}

void Satellite::createMotherSequence2() {
    int i = 0;
    int newBit = 0;
    int currentSequence = INITIAL_VALUE;

    while (i <= INITIAL_VALUE) {
        motherRegister2[i] = currentSequence;
        newBit = (currentSequence & BIT_1) ^
                  (currentSequence & BIT_2) >> 1 ^
                  (currentSequence & BIT_3) >> 2 ^
                  (currentSequence & BIT_5) >> 4 ^
                  (currentSequence & BIT_8) >> 7 ^
                  (currentSequence & BIT_9) >> 8;
        motherSequence2[i] = currentSequence & BIT_1;
        currentSequence >>= 1;
        currentSequence |= (newBit << HIGH_BIT);
        i++;
    }
}

void Satellite::createChipSequences() {
    int id = 0;
    int i = 0;

    int registerResult = 0;
    int firstRegister = 0;
    int secondRegister = 0;
    int fillBit = 0;

    while (id < 24) {
        for (i = 0; i <= INITIAL_VALUE; i++) {
            firstRegister = (1 << satelliteRegisters[id][0]);
            secondRegister = (1 << satelliteRegisters[id][1]);

            registerResult = (motherRegister2[i] & firstRegister) >> satelliteRegisters[id][0] ^
                             (motherRegister2[i] & secondRegister) >> satelliteRegisters[id][1];

            fillBit = ((motherSequence1[i] ^ registerResult) == 0) ? -1 : 1;
            chipSequences[id][i] = fillBit;
        }
        id++;
    }
}


void Satellite::initSatelliteRegisters() {
    satelliteRegisters[0][0] = REGISTER_WIDTH - 2;
    satelliteRegisters[0][1] = REGISTER_WIDTH - 6;
    satelliteRegisters[1][0] = REGISTER_WIDTH - 3;
    satelliteRegisters[1][1] = REGISTER_WIDTH - 7;
    satelliteRegisters[2][0] = REGISTER_WIDTH - 4;
    satelliteRegisters[2][1] = REGISTER_WIDTH - 8;
    satelliteRegisters[3][0] = REGISTER_WIDTH - 5;
    satelliteRegisters[3][1] = REGISTER_WIDTH - 9;
    satelliteRegisters[4][0] = REGISTER_WIDTH - 1;
    satelliteRegisters[4][1] = REGISTER_WIDTH - 9;
    satelliteRegisters[5][0] = REGISTER_WIDTH - 2;
    satelliteRegisters[5][1] = REGISTER_WIDTH - 10;
    satelliteRegisters[6][0] = REGISTER_WIDTH - 1;
    satelliteRegisters[6][1] = REGISTER_WIDTH - 8;
    satelliteRegisters[7][0] = REGISTER_WIDTH - 2;
    satelliteRegisters[7][1] = REGISTER_WIDTH - 9;
    satelliteRegisters[8][0] = REGISTER_WIDTH - 3;
    satelliteRegisters[8][1] = REGISTER_WIDTH - 10;
    satelliteRegisters[9][0] = REGISTER_WIDTH - 2;
    satelliteRegisters[9][1] = REGISTER_WIDTH - 3;
    satelliteRegisters[10][0] = REGISTER_WIDTH - 3;
    satelliteRegisters[10][1] = REGISTER_WIDTH - 4;
    satelliteRegisters[11][0] = REGISTER_WIDTH - 5;
    satelliteRegisters[11][1] = REGISTER_WIDTH - 6;
    satelliteRegisters[12][0] = REGISTER_WIDTH - 6;
    satelliteRegisters[12][1] = REGISTER_WIDTH - 7;
    satelliteRegisters[13][0] = REGISTER_WIDTH - 7;
    satelliteRegisters[13][1] = REGISTER_WIDTH - 8;
    satelliteRegisters[14][0] = REGISTER_WIDTH - 8;
    satelliteRegisters[14][1] = REGISTER_WIDTH - 9;
    satelliteRegisters[15][0] = REGISTER_WIDTH - 9;
    satelliteRegisters[15][1] = REGISTER_WIDTH - 10;
    satelliteRegisters[16][0] = REGISTER_WIDTH - 1;
    satelliteRegisters[16][1] = REGISTER_WIDTH - 4;
    satelliteRegisters[17][0] = REGISTER_WIDTH - 2;
    satelliteRegisters[17][1] = REGISTER_WIDTH - 5;
    satelliteRegisters[18][0] = REGISTER_WIDTH - 3;
    satelliteRegisters[18][1] = REGISTER_WIDTH - 6;
    satelliteRegisters[19][0] = REGISTER_WIDTH - 4;
    satelliteRegisters[19][1] = REGISTER_WIDTH - 7;
    satelliteRegisters[20][0] = REGISTER_WIDTH - 5;
    satelliteRegisters[20][1] = REGISTER_WIDTH - 8;
    satelliteRegisters[21][0] = REGISTER_WIDTH - 6;
    satelliteRegisters[21][1] = REGISTER_WIDTH - 9;
    satelliteRegisters[22][0] = REGISTER_WIDTH - 1;
    satelliteRegisters[22][1] = REGISTER_WIDTH - 3;
    satelliteRegisters[23][0] = REGISTER_WIDTH - 4;
    satelliteRegisters[23][1] = REGISTER_WIDTH - 6;
}



