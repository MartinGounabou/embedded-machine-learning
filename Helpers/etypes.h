//
// Created by o on 07/12/2020.
//

#ifndef ETYPES_H
#define ETYPES_H

#include <complex>
#include <vector>

typedef double real;
typedef std::complex<real> Complex;
typedef std::vector<real> DataVector;

enum class FTYPE : char {
     BINAVG = 1, BINSTDEV = 2, SPECCENT = 3
};




#endif //ETYPES_H


