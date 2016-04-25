//
// Created by Manuel on 23.04.2016.
//

#include "Satellite.h"

// Die Bitmasken resultieren aus den XOR-Verknüpfungen des Goldcode-Generators. Für deren Generierung werden nicht alle
// Bits benötigt, daher werden nicht alle denkbaren Bitmasken definiert.

// Bitmaske für Bit 1 (niederwertigstes Bit)
#define BIT_1  (1 << 0)

// Bitmaske für Bit 2
#define BIT_2  (1 << 1)

// Bitmaske für Bit 3
#define BIT_3  (1 << 2)

// Bitmaske für Bit 5
#define BIT_5  (1 << 4)

// Bitmaske für Bit 8
#define BIT_8  (1 << 7)

// Bitmaske für Bit 9
#define BIT_9  (1 << 8)

// Höchstes Bit
#define HIGH_BIT 9

// Initialwert der Schieberegister für die Generierung der Goldcodes
#define INITIAL_VALUE 1023

// Größe der Schieberegister
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

/**
 * Generierung der ersten Mutterfolge
 */
void Satellite::createMotherSequence1() {
    // Laufvariable für alle Chips der Sequenz
    int i = 0;

    // Das Bit, das als höchstwertiges Bit in das Schieberegister eingefügt werden soll.
    int newBit = 0;

    // Aktueller Inhalt des Schiebereigsters
    int currentSequence = INITIAL_VALUE;

    while (i <= INITIAL_VALUE) {
        // XOR-Verknüpfung des 1. mit dem 8. Bit des aktuellen Schiebregisterinhalts;
        // Dieses Bit wird im Anschluss das neue höchstwertige Bit des Schieberegisters
        newBit = (currentSequence & BIT_1 ^ (currentSequence & BIT_8) >> 7);

        // Das erste Bit des aktuellen Schieberegisters in die Mutterfolge einfügen
        motherSequence1[i++] = (currentSequence & BIT_1);

        // Entfernen des ersten Bits aus dem Schieberegister
        currentSequence >>= 1;

        // Setzen des höchsten Bits des Schieberegisters
        currentSequence |= (newBit << HIGH_BIT);
    }
}

/**
 * Generierung der zweiten Mutterfolge
 */
void Satellite::createMotherSequence2() {
    // Laufvariable für alle Chips der Sequenz
    int i = 0;

    // Das Bit, das als höchstwertiges Bit in das Schieberegister eingefügt werden soll.
    int newBit = 0;

    // Aktueller Inhalt des Schiebereigsters
    int currentSequence = INITIAL_VALUE;

    while (i <= INITIAL_VALUE) {
        // Aktueller Zustand des Schieberegisters der zweiten Mutterfolge
        motherRegister2[i] = currentSequence;

        // XOR-Verknüpfung des 1. mit dem 2., 4., 7. und 8. Bit des aktuellen Schiebregisterinhalts;
        // Dieses Bit wird im Anschluss das neue höchstwertige Bit des Schieberegisters
        newBit = (currentSequence & BIT_1) ^
                  (currentSequence & BIT_2) >> 1 ^
                  (currentSequence & BIT_3) >> 2 ^
                  (currentSequence & BIT_5) >> 4 ^
                  (currentSequence & BIT_8) >> 7 ^
                  (currentSequence & BIT_9) >> 8;

        // Das erste Bit des aktuellen Schieberegisters in die Mutterfolge einfügen
        motherSequence2[i] = currentSequence & BIT_1;

        // Entfernen des ersten Bits aus dem Schieberegister
        currentSequence >>= 1;

        // Setzen des höchsten Bits des Schieberegisters
        currentSequence |= (newBit << HIGH_BIT);
        i++;
    }
}

/**
 * Generierung der Chipsequenzen
 */
void Satellite::createChipSequences() {
    // ID des Satelliten
    int id = 0;

    // Laufvariable für die Chipsequenzen
    int i = 0;

    // Jeder Satellit hat zwei spezifische Bits, die XOR-verknüpft werden um die individuelle Chipsequenz zu erzeugen
    // niedrigeres Register der zweiten Mutterfolge das XOR verknüpft werden soll
    int firstRegister = 0;
    // höheres Register der zweiten Mutterfolge das XOR verknüpft werden soll
    int secondRegister = 0;

    // Bit, das aus der XOR-Verknüpfung der zwei Bits der zweiten Mutterfolge resultiert
    int registerResult = 0;

    // einzutragendes Bit der Goldfolge
    int fillBit = 0;

    // Itterieren über alle Satelliten
    while (id < 24) {
        for (i = 0; i <= INITIAL_VALUE; i++) {
            // niedrigeres Bit aus der zweiten Mutterfolge extrahieren
            firstRegister = (1 << satelliteRegisters[id][0]);
            // höheres Bit aus der zweiten Mutterfolge extrahieren
            secondRegister = (1 << satelliteRegisters[id][1]);

            // extrahierte Bits XOR-Verknüpfen
            registerResult = (motherRegister2[i] & firstRegister) >> satelliteRegisters[id][0] ^
                             (motherRegister2[i] & secondRegister) >> satelliteRegisters[id][1];

            // Resultat der Verknüpfung der zweiten Mutterfolge XOR verknüpfen mit dem ersten Bit der ersten Mutterfolge
            fillBit = ((motherSequence1[i] ^ registerResult) == 0) ? -1 : 1;

            // 1 oder -1 in die Chipsequenz eines Satelliten einfügen
            chipSequences[id][i] = fillBit;
        }
        id++;
    }
}

/**
 * Konstantentabelle.
 * Zur Generierung des Goldcodes werden pro Satellit zwei spezifische (konstante) Bits XOR-verknüpft. Diese sind
 * aufgrund der Literatur gegeben und werden hier übernommen.
 */
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



