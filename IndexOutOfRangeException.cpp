
#include "IndexOutOfRangeException.h"

IndexOutOfRangeException::IndexOutOfRangeException(int idx)
        : std::out_of_range("Index " + std::to_string(idx) + " out of range [0,2)") {}