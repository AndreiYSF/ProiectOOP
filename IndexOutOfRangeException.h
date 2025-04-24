#pragma once
#include <stdexcept>
#include <string>

class IndexOutOfRangeException : public std::out_of_range {
public:
    IndexOutOfRangeException(int idx)
            : std::out_of_range("Index " + std::to_string(idx) + " out of range [0,2)") {}
};