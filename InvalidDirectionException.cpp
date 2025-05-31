// InvalidDirectionException.cpp
#include "InvalidDirectionException.h"

InvalidDirectionException::InvalidDirectionException(char dir)
        : std::invalid_argument("Invalid direction: " + std::string(1, dir)) {}