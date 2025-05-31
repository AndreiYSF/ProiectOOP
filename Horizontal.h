#pragma once
#include "Obstacol.h"
#include "PositionOutOfRangeException.h"

class Horizontal : public Obstacol {
public:
    Horizontal(int x = 0, int y = 0, char simbol = 'H', int damage = 0);
    Horizontal(const Horizontal &other);
    Horizontal &operator=(Horizontal other);

    void move() override;
};