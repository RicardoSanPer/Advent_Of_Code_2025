#pragma once
#include "Problem.h"
#include <tuple>
#include <vector>
#include <iostream>
#include <unordered_map>

class Day5 :  public Problem
{
	std::vector<std::tuple<uint64_t, uint64_t>> ranges;
	std::unordered_map<uint64_t, bool> freshIds;

	int answer1 = 0;
	uint64_t answer2 = 0;
	bool isRange = true;

	void processPart2();

	void passInputLine(std::string input) override;
	void printAnswer() override;
};

