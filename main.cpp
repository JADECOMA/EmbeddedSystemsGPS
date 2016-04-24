#include "Decoder/Decoder.h"

int main(int argc, char **argv) {
    Decoder *decoder = new Decoder();
    decoder->decode(argv[1]);

    return 0;
}