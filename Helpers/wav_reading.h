#ifndef WAV_READING_H
#define WAV_READING_H

//Positions 	Sample Value 	Description
//1 – 4 	“RIFF” 	Marks the file as a riff file. Characters are each 1 byte long.
//5 – 8 	File size (integer) 	Size of the overall file – 8 bytes, in bytes (32-bit integer). Typically, you’d fill this in after creation.
//9 -12 	“WAVE” 	File Type Header. For our purposes, it always equals “WAVE”.
//13-16 	“fmt “ 	Format chunk marker. Includes trailing null
//17-20 	16 	Length of format data as listed above
//21-22 	1 	Type of format (1 is PCM) – 2 byte integer
//23-24 	2 	Number of Channels – 2 byte integer
//25-28 	44100 	Sample Rate – 32 byte integer. Common values are 44100 (CD), 48000 (DAT). Sample Rate = Number of Samples per second, or Hertz.
//29-32 	176400 	(Sample Rate * BitsPerSample * Channels) / 8.
//33-34 	4 	(BitsPerSample * Channels) / 8.1 – 8 bit mono2 – 8 bit stereo/16 bit mono4 – 16 bit stereo
//35-36 	16 	Bits per sample
//37-40 	“data” 	“data” chunk header. Marks the beginning of the data section.
//41-44 	File size (data) 	Size of the data section.
//Sample values are given above for a 16-bit stereo source.

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <string>
#include <filesystem>
#include <vector>
#include "../global.h"

namespace fs = std::filesystem;


template<char ch0, char ch1, char ch2, char ch3>
struct Letters {
    enum {
        value = (ch0 << 0) + (ch1 << 8) + (ch2 << 16) + (ch3 << 24)
    };
};

// The basic chunk of RIFF file format
struct chunk {
    uint32_t fcc;    // FourCC id
    uint32_t cb_size; // size of the data field
    chunk(uint32_t word)
            : fcc(word) {
        cb_size = 0;
    }
};

// Format chunk data field
struct Wave_format {

    uint16_t format_tag; // WAVE data format, PCM data value is 1
    uint16_t channels; // number of channels
    uint32_t sample_rate; // sample rate
    uint32_t bytes_rate; // rate, channels * sample_rate * bits_per_sample / 8
    uint16_t BytePerBloc; // audio data block, the size of the data processed per sample, channels * bits_per_sample / 8
    uint16_t bits_per_sample; // quantized bits, 8, 16, 32, etc.
    uint16_t ex_size; // size of the extension block, the size of the additional block

    Wave_format() {
        format_tag = 1; // PCM format data
        ex_size = 0; // don't use extesion field
        channels = 0;
        sample_rate = 0;
        bytes_rate = 0;
        BytePerBloc = 0;
        bits_per_sample = 0;
    }

    Wave_format(uint16_t nb_channel, uint32_t sample_rate, uint16_t sample_bits)
            : channels(nb_channel), sample_rate(sample_rate), bits_per_sample(sample_bits) {
        format_tag = 0x01;                                            // PCM format data
        bytes_rate = channels * sample_rate * bits_per_sample / 8; // code rate
        BytePerBloc = channels * bits_per_sample / 8;
        ex_size = 0;                                               // don't use extension field
    }
};

struct Wave_header {

    std::shared_ptr<chunk> riff;
    uint32_t wave_fcc;
    std::shared_ptr<chunk> fmt;
    std::shared_ptr<Wave_format> fmt_data;
    std::shared_ptr<chunk> data;

    Wave_header(uint16_t nb_channel, uint32_t sample_rate, uint16_t sample_bits) {
        riff = std::make_shared<chunk>(Letters<'R', 'I', 'F', 'F'>::value);
        fmt = std::make_shared<chunk>(Letters<'f', 'm', 't', ' '>::value);
        fmt->cb_size = 18;
        fmt_data = std::make_shared<Wave_format>(nb_channel, sample_rate, sample_bits);
        data = std::make_shared<chunk>(Letters<'d', 'a', 't', 'a'>::value);
        wave_fcc = Letters<'W', 'A', 'V', 'E'>::value;
    }

    Wave_header() {
        riff = nullptr;
        fmt = nullptr;
        fmt_data = nullptr;
        data = nullptr;
        wave_fcc = 0;
    }
};

chunk read_chunk(std::ifstream &myFile) {
    uint32_t word;
    myFile.read(reinterpret_cast<char *>(&word), sizeof(uint32_t));
    chunk new_chunk(word);
    myFile.read(reinterpret_cast<char *>(&new_chunk.cb_size), sizeof(uint32_t));
    return new_chunk;
}

uint32_t read_word(std::ifstream &myFile) {
    uint32_t word;
    myFile.read(reinterpret_cast<char *>(&word), sizeof(uint32_t));
    return word;
}

uint16_t read_half_word(std::ifstream &myFile) {
    uint16_t half_word;
    myFile.read(reinterpret_cast<char *>(&half_word), sizeof(uint16_t));
    return half_word;
}

void wavFileDetails(const std::string fileName) {
    FILE *fin = fopen(fileName.c_str(), "rb");
    std::ifstream myFile(fileName);
    std::unique_ptr<Wave_header> header = std::make_unique<Wave_header>();

    // Read RIFF chunk
    chunk riff_chunk = read_chunk(myFile);
    if (riff_chunk.fcc == Letters<'R', 'I', 'F', 'F'>::value) // 判断是不是RIFF
        std::cout << "(0-3) RIFF" << std::endl;
    header->riff = std::make_shared<chunk>(riff_chunk);

    std::cout << "(4-7) Overall size:  "
              << header->riff->cb_size
              << " B, "
              << header->riff->cb_size / (1.0 * (1 << 20))
              << " MiB"
              << std::endl;

    // Read WAVE uint32_t
    uint32_t wav = read_word(myFile);
    if (wav == Letters<'W', 'A', 'V', 'E'>::value)
        std::cout << "(8-11) WAVE" << std::endl;
    header->wave_fcc = wav;

    // Read fmt marker
    chunk fmt_chunk = read_chunk(myFile);
    header->fmt = std::make_shared<chunk>(fmt_chunk);
    std::cout << "(12-15) Fmt marker: " << header->fmt->fcc << std::endl;
    std::cout << "(16-19) Length of Fmt header: " << header->fmt->cb_size << std::endl;

    // Read Audio Format type
    auto format_type = read_half_word(myFile);
    std::string format_name;
    if (format_type == 1) {
        format_name = "PCM";
    } else if (format_type == 6) {
        format_name = "A-law";
    } else if (format_type == 7) {
        format_name = "µ-law";
    } else {
        format_name = "Unknown format type !";
    }
    header->fmt_data = std::make_unique<Wave_format>();
    header->fmt_data->format_tag = format_type;
    std::cout << "(20-21) Audio format type: "
              << header->fmt_data->format_tag
              << " --> "
              << format_name
              << std::endl;

    // Read Channels
    header->fmt_data->channels = read_half_word(myFile);
    std::cout << "(22-23) Channels: "
              << header->fmt_data->format_tag
              << std::endl;

    // Read Sample rate
    header->fmt_data->sample_rate = read_word(myFile);
    std::cout << "(24-27) Sample rate: "
              << header->fmt_data->sample_rate << " Hz"
              << std::endl;

    // Read Byte rate
    header->fmt_data->bytes_rate = read_word(myFile);
    std::cout << "(28-32) Byte rate: "
              << header->fmt_data->bytes_rate
              << std::endl;

    // Read Block alignment
    header->fmt_data->BytePerBloc = read_half_word(myFile);
    std::cout << "(32-33) Byte Per Bloc: "
              << header->fmt_data->BytePerBloc
              << std::endl;

    // Read Bits per sample:
    header->fmt_data->bits_per_sample = read_half_word(myFile);
    std::cout << "(34-35) Bits per sample: "
              << header->fmt_data->bits_per_sample
              << std::endl;

    // Read Data chunk :
    chunk data_chunk = read_chunk(myFile);
    header->data = std::make_shared<chunk>(data_chunk);
    std::cout << "(36-39) Data Marker: " << header->data->fcc << std::endl;
    std::cout << "(40-43) Size of data : "
              << header->data->cb_size
              << " B, "
              << header->data->cb_size / (1.0 * (1 << 20))
              << " MiB"
              << std::endl;

    // calculate no.of samples
    long num_samples = (8 * header->data->cb_size) / (header->fmt_data->channels * header->fmt_data->bits_per_sample);
    std::cout << "Number of samples: " << num_samples << std::endl;

    long size_of_each_sample = (header->fmt_data->channels * header->fmt_data->bits_per_sample) / 8;
    std::cout << "Size of each sample:" << size_of_each_sample << std::endl;

    // calculate duration of file
    float duration_in_seconds = (float) header->riff->cb_size / header->fmt_data->bytes_rate;
    std::cout << "Approx.Duration in seconds: " << duration_in_seconds << std::endl;
    fclose(fin);
}

std::vector<Complex> readWavFile(const std::string fileName) {
    FILE *fin = fopen(fileName.c_str(), "rb");
    std::ifstream myFile(fileName);
    std::vector<Complex> data;
    myFile.seekg(40); // zap first 10 uint32 headers
    uint32_t data_size;
    myFile.read(reinterpret_cast<char *>(&data_size), sizeof(uint32_t));
    // std::cout << data_size << std::endl;
    uint8_t lower_bits;
    uint8_t higher_bits;
    for (std::size_t k = 0; k < data_size / 2; k++) {
        myFile.read(reinterpret_cast<char *>(&higher_bits), sizeof(uint8_t));
        myFile.read(reinterpret_cast<char *>(&lower_bits), sizeof(uint8_t));
        data.push_back(static_cast<Complex>((signed short) ((higher_bits << 8) + lower_bits)));
    }
    myFile.close();
    fclose(fin);
    return data;
}

void readWavDir(std::string path) {
    for (const auto &entry: fs::directory_iterator(path))
        std::cout << entry.path() << std::endl;
}


#endif //WAV_READING_H
