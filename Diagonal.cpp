#include "Diagonal.h"
#include <utility>

Diagonal::Diagonal(int x, int y, char simbol, int damage)
        : Obstacol(x, y, simbol, damage)
{
    if (x < 0 || x >= 15 || y < 0 || y >= 15)
        throw PositionOutOfRangeException(x, y);
}

Diagonal::Diagonal(const Diagonal &other)
        : Obstacol(other)
{}

Diagonal &Diagonal::operator=(Diagonal other) {
    swap(*this, other);
    return *this;
}

void Diagonal::move() {
    (*this)[0]++;
    (*this)[1]++;

    if ((*this)[0] == 15 || (*this)[1] == 15) {
        int dif = (*this)[0] - (*this)[1];

        if (dif >= 0) {
            (*this)[0] = 0;
            (*this)[1] = dif;
        } else {
            (*this)[0] = -dif;
            (*this)[1] = 0;
        }
    }
}