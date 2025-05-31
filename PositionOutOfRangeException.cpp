// PositionOutOfRangeException.cpp
#include "PositionOutOfRangeException.h"

PositionOutOfRangeException::PositionOutOfRangeException(int x, int y)
        : std::out_of_range("Position (" + std::to_string(x) + "," + std::to_string(y) + ") out of range [0,15)") {}