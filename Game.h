#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <utility>

#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "ManagerObiecte.h"

class Player {
private:
    std::pair<int, int> position;
    int health;
    int armor;

public:
    Player() : position({0, 0}), health(100), armor(0) {}

    Player(const Player &other)
            : position(other.position), health(other.health), armor(other.armor) {}

    Player &operator=(const Player &other) {
        if (this != &other) {
            position = other.position;
            health = other.health;
            armor = other.armor;
        }
        return *this;
    }

    ~Player() {}

    void setPosition(int x, int y) {
        position = std::make_pair(x, y);
    }

    int operator[](int x) const {
        return (x == 0) ? position.first : position.second;
    }

    void setHealth(int h) {
        health = h;
    }

    int getHealth() const {
        return health;
    }

    void setArmor(int a) {
        armor = a;
    }

    int getArmor() const {
        return armor;
    }
};

class Map {
private:
    std::vector<std::vector<char>> A;
    ManagerObiect &manager;

public:
    static bool in(char c, const std::string &s) {
        for (char i: s)
            if (i == c)
                return true;
        return false;
    }

    Map(ManagerObiect &manager) : manager(manager) {
        A.resize(15, std::vector<char>(15, ' '));
    }

    Map(const Map &other)
            : A(other.A), manager(other.manager) {}

    Map &operator=(const Map &other) {
        if (this != &other) {
            A = other.A;
        }
        return *this;
    }

    std::vector<char> &operator[](int i) {
        return A[i];
    }

    friend std::ostream &operator<<(std::ostream &os, const Map &m) {

        std::vector<std::vector<char>> aux = m.A;

        for (int i = 0; i < m.manager.size(); i++)
            if (aux[m.manager[i][0]][m.manager[i][1]] == ' ')
                aux[m.manager[i][0]][m.manager[i][1]] = '*';

        os << "+";
        for (int j = 0; j < 15; j++) {
            os << "---";
        }
        os << "+\n";

        for (int i = 0; i < 15; i++) {
            os << "|";
            for (int j = 0; j < 15; j++) {
                os << " " << aux[i][j] << " ";
            }
            os << "|\n";
        }

        os << "+";
        for (int j = 0; j < 15; j++) {
            os << "---";
        }
        os << "+\n";

        return os;
    }

    ~Map() {

        A.clear();
    }
};

class Game {
public:
    enum Difficulty {
        EASY,
        MEDIUM,
        HARD,
    };

private:
    Player player;
    ManagerObiect manager;
    Map map = Map(manager);
    Difficulty difficulty;

    std::chrono::steady_clock::time_point lastUpdate;

public:
    explicit Game(Difficulty dif)
            : player(), difficulty(dif) {

        player.setPosition(5, 5);
        map[5][5] = '^';
        using clock = std::chrono::steady_clock;
        lastUpdate = clock::now();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> coordDist(0, 14);
        std::uniform_int_distribution<int> dirDist(0, 2);
        const char dirs[3] = {'h', 'v', 'd'};

        int size = 0;
        if (difficulty == EASY) size = 5;
        else if (difficulty == MEDIUM) size = 10;
        else if (difficulty == HARD) size = 15;

        for (int i = 0; i < size; ++i) {
            int x = coordDist(gen);
            int y = coordDist(gen);
            char direction = dirs[dirDist(gen)];
            char simbol = '*';
            manager.add(x, y, simbol, direction, 30);
        }
    }

    Game(const Game &other)
            : player(other.player), map(other.map), difficulty(other.difficulty) {}

    Game &operator=(const Game &other) {
        if (this != &other) {
            difficulty = other.difficulty;
            player = other.player;
            map = other.map;
        }
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Game &g) {
        os << g.map;
        return os;
    }

    void move(int dx, int dy, char c) {
        if (Map::in(map[player[0]][player[1]], "^v<>"))
            map[player[0]][player[1]] = ' ';

        player.setPosition((player[0] + dx + 15) % 15, (player[1] + dy + 15) % 15);
        map[player[0]][player[1]] = c;
    }

    void run() {

        using clock = std::chrono::steady_clock;
        auto now = clock::now();

        if (now - lastUpdate >= std::chrono::milliseconds(250)) {
            manager.updateAll();
            lastUpdate = now;
        }

        for (int i = 0; i < manager.size(); i++) {
            if (player[0] == manager[i][0] && player[1] == manager[i][1]) {
                player.setHealth(player.getHealth() - manager[i].getDamage());
            }
        }
    }

    int getHealth() const {
        return player.getHealth();
    }

    ~Game() {}
};
