#include "Horizontal.h"
#include <utility>

Horizontal::Horizontal(int x, int y, char simbol, int damage)
        : Obstacol(x, y, simbol, damage)
{
    if (x < 0 || x >= 15 || y < 0 || y >= 15)
        throw PositionOutOfRangeException(x, y);
}

Horizontal::Horizontal(const Horizontal &other)
        : Obstacol(other)
{}

Horizontal &Horizontal::operator=(Horizontal other) {
    swap(*this, other);
    return *this;
}

void Horizontal::move() {
    (*this)[0] += 1;
    if ((*this)[0] == 15) {
        (*this)[0] = 0;
    }
}