#pragma once
#include <stdexcept>
#include <string>

class InvalidDirectionException : public std::invalid_argument {
public:
    explicit InvalidDirectionException(char dir)
            : std::invalid_argument("Invalid direction: " + std::string(1, dir)) {}
};