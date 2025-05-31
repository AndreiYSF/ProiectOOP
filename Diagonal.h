#pragma once
#include "Obstacol.h"
#include "PositionOutOfRangeException.h"

class Diagonal : public Obstacol {
public:
    Diagonal(int x = 0, int y = 0, char simbol = 'H', int damage = 0);
    Diagonal(const Diagonal &other);
    Diagonal &operator=(Diagonal other);

    void move() override;
};