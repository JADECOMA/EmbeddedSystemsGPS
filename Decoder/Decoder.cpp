//
// Created by Manuel on 23.04.2016.
//

#include "Decoder.h"
#include "../Satellite/Satellite.h"
#include "../SumSignal/SumSignal.h"

Decoder::Decoder() { }

Decoder::~Decoder() { }

/**
 * GPS-Summensignal Softwaredekoder
 *
 * Sucht in Abhängigkeit eines Summensignals welche Satelliten welche Bits gesendet haben und welche Verschiebung die
 * Periode der Chipsequenzen aufweist.
 */
void Decoder::decode(char fileName[]) {
    // ID des Satelliten
    int id = 0;

    // Verschiebung der Chipsequenzen
    int delta = 0;

    // Laufvariable für die Itteration durch das Summensignal und die Chipsequenzen mit Verschiebung
    int i = 0;

    // Korrelationsprodukt des Summensignals mit einer verschobenen Chipsequenz
    int correlationProduct = 0;

    // In Satellite generierte Chipsequenzen werden hier abgerufen
    int (*chipSequences)[24][1024] = 0;
    Satellite satellite;
    satellite.getChipSequences(chipSequences);

    // Holen des Summensignals
    SumSignal *sSignal = new SumSignal(fileName);
    int *sumSignal = sSignal->getSumSignal();

    // Itterieren über alle 24 Satelliten
    while (id < 24) {
        delta = 0;

        // Verschiebung der Chipsequenzen
        while (delta < 1024) {
            i = 0;
            correlationProduct = 0;

            // Itterieren über die verschobenen Chipsequenzen
            while (i < 1023) {
                // Bilden des Korrelationsprodukts des Summensignals mit einer verschobenen Chipsequenz
                correlationProduct += sumSignal[i] * (chipSequences[0][id][(i + delta) % 1023]);
                i++;
            }

            // Konnte ein Peak im Korrelationsprodukt festgestellt werden, wird dies hier ausgegeben.
            // Mathematischer Hintergrund: Wird ein Summensignal mit einer Chipsequenz kreuzkorreliert, so ist das
            //                             Ergebnis in normalisierter Form == 1 oder == -1 falls eine Übereinstimmung
            //                             vorhanden ist.
            if (correlationProduct / 1024 == 1) {
                cout << "Satellite " << id << " has sent bit 1 (delta = " << delta << ")" << endl;
                break;
            } else if (correlationProduct / 1024 == -1) {
                cout << "Satellite " << id << " has sent bit 0 (delta = " << delta << ")" << endl;
                break;
            }
            delta++;
        }
        id++;
    }

    delete sSignal;
}

