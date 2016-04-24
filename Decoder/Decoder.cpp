//
// Created by Manuel on 23.04.2016.
//

#include "Decoder.h"
#include "../Satellite/Satellite.h"
#include "../SumSignal/SumSignal.h"

Decoder::Decoder() {}
Decoder::~Decoder() {}

void Decoder::decode(char fileName[]) {
    int id = 0;
    int delta = 0;
    int i = 0;
    int correlationProduct = 0;

    int (*chipSequences)[24][1024] = 0;
    Satellite satellite;
    satellite.getChipSequences(chipSequences);

    SumSignal *sSignal = new SumSignal(fileName);
    int *sumSignal = sSignal->getSumSignal();

    while (id < 24) {
        delta = 0;
        while (delta < 1024) {
            i = 0;
            correlationProduct = 0;
            while (i < 1023) {
                correlationProduct += sumSignal[i] * (chipSequences[0][id][(i + delta) % 1023]);
                i++;
            }

            if (correlationProduct / 1024 == 1) {
                cout << "Satellite " << id << " has sent bit 1 (delta = " << delta << ")" << endl;
            } else if (correlationProduct / 1024 == -1) {
                cout << "Satellite " << id << " has sent bit 0 (delta = " << delta << ")" << endl;
            }
            delta++;
        }
        id++;
    }

    delete sSignal;
}

