#pragma once
#include <vector>
#include "Obstacol.h"
#include "Horizontal.h"
#include "Vertical.h"
#include "Diagonal.h"
#include "InvalidDirectionException.h"

class ManagerObiect {
public:

    ManagerObiect() = default;
    ~ManagerObiect() = default;

    void add(int x, int y, char simbol, char direction, int damage = 0) {
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

    void updateAll() {
        for (auto& o : obstacole_)
            o->executaMiscare();
    }

    void display() {
        for (auto& o : obstacole_) {
            std::cout << "At position (" << (*o)[0] << ", " << (*o)[1] << ")\n";
        }
    }

    int size() const {
        return obstacole_.size();
    }

    Obstacol& operator[](std::size_t index) const {
        return *obstacole_.at(index);
    }

private:


    std::vector<std::unique_ptr<Obstacol>> obstacole_;
};