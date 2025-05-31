
#include "ManagerObiecte.h"
#include <iostream>
#include <utility>

void ManagerObiect::add(int x, int y, char simbol, char direction, int damage) {
    std::unique_ptr<Obstacol> o;
    switch (direction) {
        case 'h':
            o = std::make_unique<Horizontal>(x, y, simbol, damage);
            break;
        case 'v':
            o = std::make_unique<Vertical>(x, y, simbol, damage);
            break;
        case 'd':
            o = std::make_unique<Diagonal>(x, y, simbol, damage);
            break;
        default:
            throw InvalidDirectionException(direction);
    }
    obstacole_.push_back(std::move(o));
}

void ManagerObiect::updateAll() {
    for (auto &o : obstacole_) {
        o->executaMiscare();
    }
}

void ManagerObiect::display() {
    for (auto &o : obstacole_) {
        std::cout << "At position (" << (*o)[0] << ", " << (*o)[1] << ")\n";
    }
}

int ManagerObiect::size() const {
    return static_cast<int>(obstacole_.size());
}

Obstacol &ManagerObiect::operator[](std::size_t index) const {
    return *obstacole_.at(index);
}