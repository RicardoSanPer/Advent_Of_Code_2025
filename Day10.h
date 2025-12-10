#pragma once
#include "Problem.h"
#include <iostream>
#include <vector>
#include <queue>
#include <set>

struct Machine
{
    std::string lights;
    std::vector<std::vector<int>> buttons;
    std::vector<int> joltage;
};

class Day10 :
    public Problem
{
    int answer1 = 0;
    std::vector<Machine> machines;


    void processPart1();

    void passInputLine(std::string input) override;
    void printAnswer() override;

    void printMachine(Machine m);
};

