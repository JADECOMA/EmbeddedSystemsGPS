//
// Created by Manuel on 23.04.2016.
//

#include "SumSignal.h"

SumSignal::SumSignal(char fileName[]) {
    this->readFile(fileName);
}

SumSignal::~SumSignal() { }

/**
 * Einlesen einer Datei mit Summensignal
 */
void SumSignal::readFile(char fileName[]) {
    // Pointer auf eine Date
    FILE *file;

    // aktuell auszulesender Wert
    int number = 0;

    // Laufvariable
    int i = 0;


    if (fileName != NULL) {
        // Datei einlesen
        try {
            file = fopen(fileName, "r");
        } catch (int e) {
            cout << "Datei konnte nicht eingelesen werden!" << endl << "Vorgang wird abgebrochen." << endl;
            cout << e;
        }

        // Über den Dateiinhalt itterieren und Leerzeichen getrennte Werte in das Summensignal-Array schreiben
        while (fscanf(file, "%d ", &number) != EOF) {
            sumSignal[i++] = number;
        }
    }
}

