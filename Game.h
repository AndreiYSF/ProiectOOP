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

class Player {
private:
    std::pair<int, int> position;
    int health;
    int armor;

public:
    Player() : position({0, 0}), health(100), armor(0) {}

    Player(const Player &other)
            : position(other.position), health(other.health), armor(other.armor) {}

    Player& operator=(const Player &other) {
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

public:
    static bool in(char c, const std::string &s) {
        for (char i : s)
            if (i == c)
                return true;
        return false;
    }

    Map() {
        A.resize(15, std::vector<char>(15, ' '));
    }

    Map(const Map& other)
            : A(other.A) {}

    Map& operator=(const Map& other) {
        if (this != &other) {
            A = other.A;
        }
        return *this;
    }

    std::vector<char>& operator[](int i) {
        return A[i];
    }

    friend std::ostream& operator<<(std::ostream& os, const Map& m) {
        os << "+";
        for (int j = 0; j < 15; j++) {
            os << "---";
        }
        os << "+\n";

        for (int i = 0; i < 15; i++) {
            os << "|";
            for (int j = 0; j < 15; j++) {
                os << " " << m.A[i][j] << " ";
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

    void run() {

    }

    ~Map() {

        A.clear();
    }
};

class Game {
public:
    enum Difficulty {
        EASY,
        HARD
    };

private:
    Player player;
    Map map;
    Difficulty difficulty;

public:
    explicit Game(Difficulty dif)
            : player(), map(), difficulty(dif) {
        player.setPosition(5, 5);
    }

    Game(const Game& other)
            : player(other.player), map(other.map), difficulty(other.difficulty) {}

    Game& operator=(const Game& other) {
        if (this != &other) {
            difficulty = other.difficulty;
            player = other.player;
            map = other.map;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Game& g) {
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
        map.run();
    }

    ~Game() {}
};
