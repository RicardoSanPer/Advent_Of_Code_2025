#pragma once
#include "Problem.h"
#include <iostream>
#include <vector>
class Day7 :
    public Problem
{
    std::string previous_line;
    std::vector<uint64_t> paths;
    uint64_t timelines = 0;

    int splits = 0;

    void passInputLine(std::string input) override;
    void printAnswer() override;
};

