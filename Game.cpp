#include "Game.h"
#include <random>

using Clock = std::chrono::steady_clock;

Player::Player()
        : position({0, 0}), health(100), armor(0) {}

Player::Player(const Player &other)
        : position(other.position),
          health(other.health),
          armor(other.armor) {}

Player &Player::operator=(const Player &other) {
    if (this != &other) {
        position = other.position;
        health = other.health;
        armor = other.armor;
    }
    return *this;
}

Player::~Player() {}

void Player::setPosition(int x, int y) {
    position = std::make_pair(x, y);
}

int Player::operator[](int idx) const {
    return (idx == 0) ? position.first : position.second;
}

void Player::setHealth(int h) {
    health = h;
}

int Player::getHealth() const {
    return health;
}

void Player::setArmor(int a) {
    armor = a;
}

int Player::getArmor() const {
    return armor;
}

bool Map::in(char c, const std::string &s) {
    for (char i : s) {
        if (i == c) return true;
    }
    return false;
}

Map::Map(ManagerObiect &manager_)
        : A(15, std::vector<char>(15, ' ')),
          manager(manager_) {}

Map::Map(const Map &other)
        : A(other.A),
          manager(other.manager) {}

Map &Map::operator=(const Map &other) {
    if (this != &other) {
        A = other.A;
    }
    return *this;
}

Map::~Map() {
    A.clear();
}

std::vector<char> &Map::operator[](int i) {
    return A[i];
}

std::ostream &operator<<(std::ostream &os, const Map &m) {
    std::vector<std::vector<char>> aux = m.A;
    for (int i = 0; i < m.manager.size(); ++i) {
        int x = m.manager[i][0];
        int y = m.manager[i][1];
        if (aux[x][y] == ' ') {
            aux[x][y] = '*';
        }
    }

    os << "+";
    for (int j = 0; j < 15; ++j) {
        os << "---";
    }
    os << "+\n";

    for (int i = 0; i < 15; ++i) {
        os << "|";
        for (int j = 0; j < 15; ++j) {
            os << " " << aux[i][j] << " ";
        }
        os << "|\n";
    }

    os << "+";
    for (int j = 0; j < 15; ++j) {
        os << "---";
    }
    os << "+\n";

    return os;
}

Game::Game(Difficulty dif)
        : player(),
          manager(),
          map(manager),
          difficulty(dif),
          lastUpdate(Clock::now())
{
    player.setPosition(5, 5);
    map[5][5] = '^';

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> coordDist(0, 14);
    std::uniform_int_distribution<int> dirDist(0, 2);
    const char dirs[3] = { 'h', 'v', 'd' };

    int size = 0;
    if (difficulty == EASY)   size = 5;
    else if (difficulty == MEDIUM) size = 10;
    else if (difficulty == HARD)   size = 15;

    for (int i = 0; i < size; ++i) {
        int x = coordDist(gen);
        int y = coordDist(gen);
        char direction = dirs[dirDist(gen)];
        char simbol = '*';
        int damage = 30;
        manager.add(x, y, simbol, direction, damage);
    }
}

Game::~Game() {}

std::ostream &operator<<(std::ostream &os, const Game &g) {
    os << g.map;
    return os;
}

void Game::move(int dx, int dy, char c) {
    if (Map::in(map[player[0]][player[1]], "^v<>")) {
        map[player[0]][player[1]] = ' ';
    }
    int newX = (player[0] + dx + 15) % 15;
    int newY = (player[1] + dy + 15) % 15;
    player.setPosition(newX, newY);
    map[newX][newY] = c;
}

void Game::run() {
    auto now = Clock::now();
    if (now - lastUpdate >= std::chrono::milliseconds(250)) {
        manager.updateAll();
        lastUpdate = now;
    }
    for (int i = 0; i < manager.size(); ++i) {
        int objX = manager[i][0];
        int objY = manager[i][1];
        if (player[0] == objX && player[1] == objY) {
            int dmg = manager[i].getDamage();
            player.setHealth(player.getHealth() - dmg);
        }
    }
}

int Game::getHealth() const {
    return player.getHealth();
}