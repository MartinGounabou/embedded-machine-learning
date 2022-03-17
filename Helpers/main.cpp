#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <string>
#include <filesystem>
#include <vector>
#include "etypes.h"
#include "au_reading.h"


using namespace std;
typedef uint32_t u_32;


int main() {

    std::filesystem::path fileName = "/home/martinho/Documents/embedded-machine-learning/Helpers/metal.00000.au";
    DataVector data;
    data = readAuFile(fileName);
    std::cout << data[400] <<endl;
    return 0;
}