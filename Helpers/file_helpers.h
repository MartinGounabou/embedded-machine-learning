#ifndef FILE_HELPERS_H
#define FILE_HELPERS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <tuple>
#include <set>
#include <filesystem>
#include <map>
#include <random>
#include "etypes.h"


std::vector<std::filesystem::path> alpha_dir_listing(std::string dir_path) {
    std::set<std::filesystem::path> sorted_by_name_dirs;
    std::set<std::filesystem::path> sorted_by_name_files;
    std::vector<std::filesystem::path> dirs_listing;
    for (auto &entry: std::filesystem::directory_iterator(dir_path)) {
        if (std::filesystem::is_directory(entry.path())) {
            sorted_by_name_dirs.insert(entry.path());
        }
    }
    std::copy(sorted_by_name_dirs.cbegin(), sorted_by_name_dirs.cend(), std::back_inserter(dirs_listing));
    return dirs_listing;
}

std::vector<std::filesystem::path> alpha_files_listing(std::string dir_path) {
    std::set<std::filesystem::path> sorted_by_name_files;
    std::vector<std::filesystem::path> files_listing;
    for (const auto &file: std::filesystem::directory_iterator(dir_path))
        sorted_by_name_files.insert(file);
    std::copy(sorted_by_name_files.cbegin(), sorted_by_name_files.cend(), std::back_inserter(files_listing));
    return files_listing;
}


std::pair<std::vector<std::filesystem::path>, std::vector<std::filesystem::path>>
select_train_test_files(std::vector<std::filesystem::path> files, double ratio) {
    std::size_t training_size = std::floor(files.size() * (1.0 - ratio));
    //std::size_t testing_size = files.size() - training_size;
    //std::cout << training_size << " " << testing_size << std::endl;
    std::random_device random_device;
    //std::mt19937 engine{66};
    std::mt19937 engine{random_device()};
    std::uniform_int_distribution<int> dist(0, files.size() - 1);
    std::set<std::filesystem::path> training_files_set;
    std::set<int> indexes;
    for (std::size_t k = 0; k < training_size; k++) {
        int random_index;
        do {
            random_index = dist(engine);
        } while (indexes.contains(random_index));
        indexes.insert(random_index);
        training_files_set.insert(files[random_index]);
    }
    std::vector<std::filesystem::path> testing_files;
    for (std::size_t k = 0; k < files.size(); k++) {
        if (!indexes.contains(k))
            testing_files.push_back(files[k]);
    }
    std::vector<std::filesystem::path> training_files;
    std::copy(training_files_set.cbegin(), training_files_set.cend(), std::back_inserter(training_files));
    return std::make_pair(training_files, testing_files);
}


#endif //FILE_HELPERS_H
