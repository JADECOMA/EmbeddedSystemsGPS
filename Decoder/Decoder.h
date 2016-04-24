//
// Created by Manuel on 23.04.2016.
//

#ifndef EMBEDDEDSYSTEMSGPS_DECODER_H
#define EMBEDDEDSYSTEMSGPS_DECODER_H

class Decoder {
public:
    Decoder();
    virtual ~Decoder();
    void decode(char fileName[]);
};


#endif //EMBEDDEDSYSTEMSGPS_DECODER_H
