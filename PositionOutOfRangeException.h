
#pragma once
#include <stdexcept>
#include <string>

class PositionOutOfRangeException : public std::out_of_range {
public:
    PositionOutOfRangeException(int x, int y);
};