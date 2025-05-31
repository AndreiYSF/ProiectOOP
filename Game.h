#include <bits/stdc++.h>
#include "ManagerObiecte.h"

class Player {
private:
    std::pair<int, int> position;
    int health;
    int armor;

public:
    Player();
    Player(const Player &other);
    Player &operator=(const Player &other);
    ~Player();

    void setPosition(int x, int y);
    int operator[](int idx) const;

    void setHealth(int h);
    int getHealth() const;

    void setArmor(int a);
    int getArmor() const;
};

class Map {
private:
    std::vector<std::vector<char>> A;
    ManagerObiect &manager;

public:
    static bool in(char c, const std::string &s);

    explicit Map(ManagerObiect &manager);
    Map(const Map &other);
    Map &operator=(const Map &other);
    ~Map();

    std::vector<char> &operator[](int i);

    friend std::ostream &operator<<(std::ostream &os, const Map &m);
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
    Map map;
    Difficulty difficulty;
    std::chrono::steady_clock::time_point lastUpdate;

public:
    explicit Game(Difficulty dif);
    Game(const Game &other);
    Game &operator=(const Game &other);
    ~Game();

    friend std::ostream &operator<<(std::ostream &os, const Game &g);

    void move(int dx, int dy, char c);
    void run();
    int getHealth() const;
};