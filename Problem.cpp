#include "Problem.h"

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
