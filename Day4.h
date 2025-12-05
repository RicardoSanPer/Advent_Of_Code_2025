#pragma once
#include "Problem.h"
#include <vector>
class Day4 : public Problem
{
    std::vector<std::string> board{};
    int answer1 = 0;
    void solvePart1();

    void passInputLine(std::string input) override;
    void printAnswer() override;
};

