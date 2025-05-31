
#include "Obstacol.h"
#include <utility>

Obstacol::Obstacol(int x_, int y_, char simbol_, int damage_)
        : x(x_), y(y_), simbol(simbol_), damage(damage_) {}

Obstacol::~Obstacol() = default;

Obstacol::Obstacol(const Obstacol &other)
        : x(other.x), y(other.y), simbol(other.simbol), damage(other.damage) {}

Obstacol &Obstacol::operator=(const Obstacol &other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        simbol = other.simbol;
        damage = other.damage;
    }
    return *this;
}

void Obstacol::executaMiscare() {
    move();
}

int &Obstacol::operator[](int k) {
    if (k == 0)
        return x;
    else if (k == 1)
        return y;
    else
        throw IndexOutOfRangeException(k);
}

char Obstacol::getSimbol() const {
    return simbol;
}

int Obstacol::getDamage() const {
    return damage;
}

void swap(Obstacol &a, Obstacol &b) noexcept {
    using std::swap;
    swap(a.x, b.x);
    swap(a.y, b.y);
    swap(a.simbol, b.simbol);
    swap(a.damage, b.damage);
}