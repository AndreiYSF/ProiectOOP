
#pragma once
#include "Obstacol.h"
#include "PositionOutOfRangeException.h"

class Vertical : public Obstacol {
public:
    Vertical(int x = 0, int y = 0, char simbol = 'H', int damage = 0);
    Vertical(const Vertical& other);
    Vertical& operator=(Vertical other);

    void move() override;
};