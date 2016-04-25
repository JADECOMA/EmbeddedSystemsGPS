#include "Decoder/Decoder.h"
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char **argv) {
    Decoder *decoder = new Decoder();

    int i;
    string file;
    char fileName[200];

    for (i = 1; i < 31; i++) {
        //decoder->decode(argv[1]);

        file = string("C:\\Users\\Manuel\\ClionProjects\\EmbeddedSystemsGPS\\testFiles\\gps_sequence_") + string(to_string(i)) + string(".txt");
        strncpy(fileName, file.c_str(), sizeof(fileName));
        cout << fileName << endl;
        decoder->decode(fileName);
        cout << endl;
    }


    return 0;
}