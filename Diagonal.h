#pragma once
#include <bits/stdc++.h>
#include "Obstacol.h"
#include "PositionOutOfRangeException.h"

class Diagonal : public Obstacol {
public:
    Diagonal(int x = 0, int y = 0, char simbol = 'H', int damage = 0)
            : Obstacol(x, y, simbol, damage) {

        if (x < 0 || x >= 15 || y < 0 || y >= 15)
            throw PositionOutOfRangeException(x, y);
    }

    Diagonal(const Diagonal &other)
            : Obstacol(other) {}

    Diagonal &operator=(Diagonal other) {
        swap(*this, other);
        return *this;
    }

    void move() override {
        (*this)[0]++;
        (*this)[1]++;

        if ((*this)[0] == 15 || (*this)[1] == 15) {

            int dif = (*this)[0] - (*this)[1];

            if (dif >= 0) {

                (*this)[0] = 0;
                (*this)[1] = dif;
            }
            else {
                (*this)[0] = - dif;
                (*this)[1] = 0;
            }
        }
    }
};