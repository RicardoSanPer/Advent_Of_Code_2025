#pragma once
#include "Problem.h"
class Day3 : public Problem
{
    int answer = 0;
    uint64_t answer2 = 0;
    void solvePart1(std::string input);
    void solvePart2(std::string input);
    void passInputLine(std::string input) override;
    void printAnswer() override;
};

