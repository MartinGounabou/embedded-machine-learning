#ifndef PRINT_HELPERS_H
#define PRINT_HELPERS_H

#include <iterator>
#include "etypes.h"

template<typename T>
std::ostream &operator<<(std::ostream &s, const std::vector<T> &v) {
    s << '[';
    if (!v.empty()) {
        std::copy(v.cbegin(), v.cend() - 1, std::ostream_iterator<T>(s, ", "));
        s << v.back();
    }
    return s << ']';
}


std::ostream &operator<<(std::ostream &s, const DataVector &v) {
    s << '[';
    if (!v.empty()) {
        std::copy(v.cbegin(), v.cend() - 1, std::ostream_iterator<real>(s, ", "));
        s << v.back();
    }
    return s << ']';
}

template<typename T, size_t SIZE>
std::ostream &operator<<(std::ostream &s, const std::array<T, SIZE> &a) {
    s << '[';
    if (!a.empty()) {
        std::copy(a.cbegin(), a.cend() - 1, std::ostream_iterator<T>(s, ", "));
        s << a.back();
    }
    return s << ']';
}

#endif //PRINT_HELPERS_H
