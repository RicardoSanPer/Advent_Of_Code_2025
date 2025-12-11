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
    std::string joltage;
};

class Day10 :
    public Problem
{
    int answer1 = 0;
    int answer2 = 0;
    std::vector<Machine> machines;


    void processPart1();
    void processPart2();

    void passInputLine(std::string input) override;
    void printAnswer() override;

    void printMachine(Machine m);
};

