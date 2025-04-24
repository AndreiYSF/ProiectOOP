
#include <stdexcept>
#include <string>

class PositionOutOfRangeException : public std::out_of_range {
public:
    PositionOutOfRangeException(int x, int y)
            : std::out_of_range("Position (" + std::to_string(x) + "," + std::to_string(y) + ") out of range [0,15)") {}
};