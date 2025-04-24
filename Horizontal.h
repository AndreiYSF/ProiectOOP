#pragma once
#include <bits/stdc++.h>
#include "Obstacol.h"
#include "PositionOutOfRangeException.h"

class Horizontal : public Obstacol {
public:
    Horizontal(int x = 0, int y = 0, char simbol = 'H', int damage = 0)
            : Obstacol(x, y, simbol, damage) {

        if (x < 0 || x >= 15 || y < 0 || y >= 15)
            throw PositionOutOfRangeException(x, y);
    }

    Horizontal(const Horizontal &other)
            : Obstacol(other) {}

    Horizontal &operator=(Horizontal other) {
        swap(*this, other);
        return *this;
    }

    void move() override {
        (*this)[0] += 1;
        if ((*this)[0] == 15) {
            (*this)[0] = 0;
        }
    }
};