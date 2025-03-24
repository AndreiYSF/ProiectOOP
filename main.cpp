#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <utility>

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
        A.resize(10, std::vector<char>(10, ' '));
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
        for (int j = 0; j < 10; j++) {
            os << "---";
        }
        os << "+\n";

        for (int i = 0; i < 10; i++) {
            os << "|";
            for (int j = 0; j < 10; j++) {
                os << " " << m.A[i][j] << " ";
            }
            os << "|\n";
        }

        os << "+";
        for (int j = 0; j < 10; j++) {
            os << "---";
        }
        os << "+\n";

        return os;
    }

    void run() {
        // Add game logic here if needed.
    }

    ~Map() {}
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

        player.setPosition((player[0] + dx + 10) % 10, (player[1] + dy + 10) % 10);
        map[player[0]][player[1]] = c;
    }

    void run() {
        map.run();
    }

    ~Game() {}
};

void setTerminalMode(termios &orig_termios) {
    tcgetattr(STDIN_FILENO, &orig_termios);
    termios new_termios = orig_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void restoreTerminalMode(const termios &orig_termios) {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

int main() {
    Game game(Game::EASY);

    termios orig_termios;
    setTerminalMode(orig_termios);

    std::cout << "Press keys to see them in real time. Press 'q' to quit." << std::endl;

    while (true) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000;

        int ret = select(STDIN_FILENO + 1, &readfds, nullptr, nullptr, &timeout);
        if (ret > 0 && FD_ISSET(STDIN_FILENO, &readfds)) {
            system("clear");

            int ch = getchar();
            if (ch == 'q') {
                break;
            } else if (ch == 27) { // ESC key
                int ch1 = getchar();
                int ch2 = getchar();
                if (ch1 == '[') {
                    if (ch2 == 'A')
                        game.move(-1, 0, '^');
                    else if (ch2 == 'B')
                        game.move(1, 0, 'v');
                    else if (ch2 == 'C')
                        game.move(0, 1, '>');
                    else if (ch2 == 'D')
                        game.move(0, -1, '<');
                }
            }

            game.run();
            std::cout << game << std::endl;
        }
        usleep(10000);
    }

    restoreTerminalMode(orig_termios);
    return 0;
}