
#pragma once
#include <vector>
#include <memory>
#include "Obstacol.h"
#include "Horizontal.h"
#include "Vertical.h"
#include "Diagonal.h"
#include "InvalidDirectionException.h"

class ManagerObiect {
public:
    ManagerObiect() = default;
    ~ManagerObiect() = default;

    void add(int x, int y, char simbol, char direction, int damage = 0);
    void updateAll();
    void display();
    int size() const;
    Obstacol &operator[](std::size_t index) const;

private:
    std::vector<std::unique_ptr<Obstacol>> obstacole_;
};