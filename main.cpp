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
#include "Game.h"
#include "Obstacol.h"
#include "ManagerObiecte.h"

termios orig_termios;

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit([]() { tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios); });

    termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

int kbhit() {
    timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv);
}

int main() {

    try {

        Game game(Game::MEDIUM);

        std::cout << "Press 'q' to quit. The program will auto-exit after 1 minute of inactivity." << std::endl;

        // Record the time of the last activity
        auto lastActivity = std::chrono::steady_clock::now();

        enableRawMode();
        while (true) {
            if (kbhit()) {
                char ch;
                read(STDIN_FILENO, &ch, 1);
                lastActivity = std::chrono::steady_clock::now(); // Update activity time
                if (ch == 'q') break;
                system("clear");

                if (ch == 'w')
                    game.move(-1, 0, '^');
                else if (ch == 's')
                    game.move(1, 0, 'v');
                else if (ch == 'a')
                    game.move(0, -1, '<');
                else if (ch == 'd')
                    game.move(0, 1, '>');
            }
            // Auto exit after 1 minute of inactivity
            auto now = std::chrono::steady_clock::now();
            if (now - lastActivity >= std::chrono::minutes(1)) break;

            game.run();
            if (game.getHealth() <= 0) {

                std::cout << "Game Over!" << std::endl;
                return 0;
            }
            system("clear");
            std::cout << game << std::endl;
            std::cout << "Health: " << game.getHealth() << std::endl;
            usleep(50000);
        }
    }
    catch (const std::exception &e) {

        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 0;
    }

    std::cout << "Exiting due to inactivity or key press..." << std::endl;
    return 0;
}