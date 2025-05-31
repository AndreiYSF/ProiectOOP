
#pragma once

#include "IndexOutOfRangeException.h"

class Obstacol {
private:
    int x;
    int y;
    char simbol;
    int damage;

public:
    Obstacol(int x = 0, int y = 0, char simbol = 'O', int damage = 0);
    virtual ~Obstacol();

    Obstacol(const Obstacol &other);
    Obstacol &operator=(const Obstacol &other);

    void executaMiscare();
    virtual void move() = 0;

    int &operator[](int k);
    char getSimbol() const;
    int getDamage() const;

    friend void swap(Obstacol &a, Obstacol &b) noexcept;
};