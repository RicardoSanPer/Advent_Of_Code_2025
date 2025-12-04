#include "Problem.h"
#include <iostream>
int Problem::stringToInt(std::string input)
{
    int sum = 0;

    for (char c : input)
    {
        sum *= 10;
        sum += c - '0';
    }

    return sum;
}

uint64_t Problem::stringToUint64(std::string input)
{
    uint64_t value = 0;
    for (char c : input)
    {
        value *= 10;
        value += c - '0';
    }
    return value;
}

/// @brief Solves a problem
/// @param input Input File Stream
void Problem::Solve(std::ifstream& input)
{
    std::string line;
    while (std::getline(input, line))
    {
        passInputLine(line);
    }

    printAnswer();
}
