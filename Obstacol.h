#include <bits/stdc++.h>
#include "IndexOutOfRangeException.h"

class Obstacol {
private:
    int x;
    int y;
    char simbol;
    int damage;

public:
    Obstacol(int x = 0, int y = 0, char simbol = 'O', int damage = 0)
            : x(x), y(y), simbol(simbol), damage(damage) {}

    virtual ~Obstacol() = default;

    Obstacol(const Obstacol &other)
            : x(other.x), y(other.y), simbol(other.simbol), damage(other.damage) {}

    Obstacol &operator=(const Obstacol &other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            simbol = other.simbol;
            damage = other.damage;
        }
        return *this;
    }

    void executaMiscare() {
        move();
    }

    virtual void move() = 0;

    int& operator[] (int k) {

        if (k == 0)
            return x;
        else if (k == 1)
            return y;
        else
            throw IndexOutOfRangeException(k);
    }

    char getSimbol() const { return simbol; }

    int getDamage() const { return damage; }

    friend void swap(Obstacol &a, Obstacol &b) noexcept {
        using std::swap;
        swap(a.x, b.x);
        swap(a.y, b.y);
        swap(a.simbol, b.simbol);
        swap(a.damage, b.damage);
    }
};