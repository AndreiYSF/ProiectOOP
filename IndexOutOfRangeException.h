
#pragma once
#include <stdexcept>
#include <string>

class IndexOutOfRangeException : public std::out_of_range {
public:
    IndexOutOfRangeException(int idx);
};