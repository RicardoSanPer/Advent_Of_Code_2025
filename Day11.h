#pragma once
#include "Problem.h"
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

struct Node
{
    bool dac = false;
    bool fft = false;

    std::string id;
    std::vector<std::string> children;
    std::vector<std::string> parents;
};

class Day11 : public Problem
{
    int answer1 = 0;
    uint64_t answer2 = 0;

    std::unordered_map<std::string, Node*> nodes;
    std::unordered_map<std::string, uint64_t> visited;

    void processPart1(std::string root);
    void processPart2(std::string root);
    void propagatePart2(std::string root);
    void updateChildNodeParent(std::string parent, std::string child);
    void traverseTree(Node* node);
    void traverseTreePart2(Node* node);

    void passInputLine(std::string input) override;
    void printAnswer() override;
};

