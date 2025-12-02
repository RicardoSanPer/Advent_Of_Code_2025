#pragma once
#include "Problem.h"
class Day2 : public Problem
{
    uint64_t sum_part1 = 0;
    uint64_t sum_part2 = 0;

    void process(std::string id1, std::string id2);
    uint64_t stringToInt(std::string s);
    bool checkForIdValidity(std::string input);
    bool checkForIdValidity2(std::string input);

    void passInputLine(std::string input) override;
    void printAnswer() override;
};

