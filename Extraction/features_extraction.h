#ifndef EML_FEATURES_EXTRACTION_H
#define EML_FEATURES_EXTRACTION_H

#include <map>
#include <filesystem>
#include <fstream>
#include "../Helpers/etypes.h"

std::map<FTYPE, DataVector> stft(DataVector &signal);

void write_csv(std::string filename,
               std::vector<std::pair<std::filesystem::path, std::map<FTYPE, DataVector>>> &dataset);

std::map<FTYPE, DataVector> compute_features_for(std::filesystem::path &file_path);

void compute_set_of_features(std::vector<std::filesystem::path> &files);

void compute_set_of_features_test(std::ifstream &file) ;
#endif //EML_FEATURES_EXTRACTION_H
