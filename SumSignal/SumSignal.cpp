//
// Created by Manuel on 23.04.2016.
//

#include "SumSignal.h"

SumSignal::SumSignal(char fileName[]) {
    this->readFile(fileName);
}

SumSignal::~SumSignal() { }

void SumSignal::readFile(char fileName[]) {
    FILE *file;
    int number = 0;
    int i = 0;

    if (fileName != NULL) {
        try {
            file = fopen(fileName, "r");
        } catch (int e) {
            cout << "Datei konnte nicht eingelesen werden!" << endl << "Vorgang wird abgebrochen." << endl;
            cout << e;
        }

        while (fscanf(file, "%d ", &number) != EOF) {
            sumSignal[i++] = number;
        }
    }
}

