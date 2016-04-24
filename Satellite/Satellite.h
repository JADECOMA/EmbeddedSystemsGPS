//
// Created by Manuel on 23.04.2016.
//

#ifndef EMBEDDEDSYSTEMSGPS_SATELLITE_H
#define EMBEDDEDSYSTEMSGPS_SATELLITE_H

class Satellite {

public:
    Satellite();
    virtual ~Satellite();
    void getChipSequences(int (*&returnValue)[24][1024]);

private:
    void init();
    void createMotherSequence1();
    void createMotherSequence2();

    void createChipSequences();

    void initSatelliteRegisters();

    int motherSequence1[1024];
    int motherSequence2[1024];
    int motherRegister2[1024];

    int satelliteRegisters[24][2];

    int chipSequences[24][1024];
};


#endif //EMBEDDEDSYSTEMSGPS_SATELLITE_H
