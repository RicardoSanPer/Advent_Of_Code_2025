#pragma once
#include "Problem.h"
#include <iostream>
#include <vector>
class Day6 : public Problem
{
	std::vector<std::vector<std::uint64_t>> values;
	std::vector<std::string> valuesPart2;
	std::string operators;

	uint64_t answer1 = 0;
	uint64_t answer2 = 0;

	bool operatorInput = false;

	void processInputPart1(std::string input);
	void processInputPart2();

	void processAnswerPart1();

	void addNumberToColumn(std::string number, int index);
	void passInputLine(std::string input) override;
	void printAnswer() override;
};

