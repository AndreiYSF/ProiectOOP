#include <bits/stdc++.h>
#include "Obstacol.h"
#include "PositionOutOfRangeException.h"

class Vertical : public Obstacol {
public:
    Vertical(int x = 0, int y = 0, char simbol = 'H', int damage = 0)
            : Obstacol(x, y, simbol, damage) {

        if (x < 0 || x >= 15 || y < 0 || y >= 15)
            throw PositionOutOfRangeException(x, y);
    }

    Vertical(const Vertical& other)
            : Obstacol(other)
    {}

    Vertical& operator=(Vertical other) {
        swap(*this, other);
        return *this;
    }

    void move() override {
        (*this)[1] += 1;
        if ((*this)[1] == 15) {
            (*this)[1] = 0;
        }
    }
};