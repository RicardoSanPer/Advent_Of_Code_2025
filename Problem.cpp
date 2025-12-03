#include "Problem.h"

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
