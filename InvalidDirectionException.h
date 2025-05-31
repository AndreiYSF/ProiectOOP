
#pragma once
#include <stdexcept>
#include <string>

class InvalidDirectionException : public std::invalid_argument {
public:
    explicit InvalidDirectionException(char dir);
};