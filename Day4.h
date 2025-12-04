#pragma once
#include "Problem.h"
#include <vector>
class Day4 : public Problem
{
    std::vector<std::string> board{};
    int solvePart1();
    int solvePart2();

    void passInputLine(std::string input) override;
    void printAnswer() override;
};

