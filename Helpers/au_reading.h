#ifndef AU_READING_H
#define AU_READING_H

//32 bit word (unsigned) 	field 	Description/Content Hexadecimal numbers in C notation
//0 	                    magic number 	the value 0x2e736e64 (four ASCII characters ".snd")
//1 	                    data offset 	the offset to the data in bytes, must be divisible by 8. The minimum valid number is 24 (decimal), since this is the header length (six 32-bit words) with no space reserved for extra information (the annotation field). The minimum valid number with an annotation field present is 32 (decimal).
//2 	                    data size 	data size in bytes. If unknown, the value 0xffffffff should be used.
//3 	                    encoding 	Data encoding format:
//
//1 = 8-bit G.711 μ-law
//2 = 8-bit linear PCM
//3 = 16-bit linear PCM
//4 = 24-bit linear PCM
//5 = 32-bit linear PCM
//6 = 32-bit IEEE floating point
//7 = 64-bit IEEE floating point
//8 = Fragmented sample data
//9 = DSP program
//10 = 8-bit fixed point
//11 = 16-bit fixed point
//12 = 24-bit fixed point
//13 = 32-bit fixed point
//18 = 16-bit linear with emphasis
//19 = 16-bit linear compressed
//20 = 16-bit linear with emphasis and compression
//21 = Music kit DSP commands
//23 = 4-bit compressed using the ITU-T G.721 ADPCM voice data encoding scheme
//24 = ITU-T G.722 SB-ADPCM
//25 = ITU-T G.723 3-bit ADPCM
//26 = ITU-T G.723 5-bit ADPCM
//27 = 8-bit G.711 A-law
//
//4 	sample rate 	the number of samples/second, e.g., 8000
//5 	channels 	the number of interleaved channels, e.g., 1 for mono, 2 for stereo; more channels possible, but may not be supported by all readers.

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <string>
#include <filesystem>
#include <vector>
#include "etypes.h"

using namespace std;
typedef uint32_t u_32;


u_32 read_bytes_bytes(ifstream& myFile){

    uint8_t ch0;
    uint8_t ch1;
    uint8_t ch2;
    uint8_t ch3;

    myFile.read(reinterpret_cast<char *>(&ch0), sizeof(uint8_t));
    myFile.read(reinterpret_cast<char *>(&ch1), sizeof(uint8_t));
    myFile.read(reinterpret_cast<char *>(&ch2), sizeof(uint8_t));
    myFile.read(reinterpret_cast<char *>(&ch3), sizeof(uint8_t));

    // std::cout << ua_file.magic << std::endl;

    uint32_t value = (ch0 << 24) + (ch1 << 16) + (ch2 << 8) + (ch3 << 0);

    return value ;
}


DataVector readAuFile(std::filesystem::path& fileName) {

    FILE *fin;
    fin = fopen(fileName.c_str(), "rb");
    std::ifstream myFile(fileName);

    std::ofstream Morison_File ("/home/martinho/Documents/embedded-machine-learning/Helpers/sound_cpp.txt");         //recording
    // Morison_File << "Time Force(N/m)" << endl; 

    DataVector data;
    myFile.seekg(sizeof(u_32)*2); // zap first 10 uint32 headers

    uint32_t data_size;
    data_size = read_bytes_bytes(myFile);
    
    // std::cout << data_size << std::endl;

    myFile.seekg(sizeof(u_32)*3);
    
    uint8_t lower_bits;
    uint8_t higher_bits;

    for (std::size_t k = 0; k < data_size / 2; k++) {
        myFile.read(reinterpret_cast<char *>(&higher_bits), sizeof(uint8_t));
        myFile.read(reinterpret_cast<char *>(&lower_bits), sizeof(uint8_t));
        data.push_back(static_cast<uint16_t>((signed short) ((higher_bits << 8) | lower_bits)));
        Morison_File << static_cast<uint16_t>((signed short) ((higher_bits << 8) | lower_bits)) << endl;  //recording
    }

    Morison_File.close();

    myFile.close();
    fclose(fin);
    std::cout << "fin lecture" << endl;
    return data;
}



struct Audio_filehdr{
    u_32 magic;
    u_32 hdr_size;
    u_32 data_size;
    u_32 encoding;
    u_32 sample_rate;
    u_32 channels;
} ;

#endif //AU_READING_H
