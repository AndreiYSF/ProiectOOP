
#include "Vertical.h"
#include <utility>

Vertical::Vertical(int x, int y, char simbol, int damage)
        : Obstacol(x, y, simbol, damage)
{
    if (x < 0 || x >= 15 || y < 0 || y >= 15)
        throw PositionOutOfRangeException(x, y);
}

Vertical::Vertical(const Vertical& other)
        : Obstacol(other)
{}

Vertical& Vertical::operator=(Vertical other) {
    swap(*this, other);
    return *this;
}

void Vertical::move() {
    (*this)[1] += 1;
    if ((*this)[1] == 15) {
        (*this)[1] = 0;
    }
}