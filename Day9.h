#pragma once
#include "Problem.h"
#include <vector>

struct RedTile
{
	uint64_t x;
	uint64_t y;
};

class Day9 : public Problem
{
	uint64_t answer1 = 0;
	std::vector<RedTile*> tiles;

	void processPart1();
	uint64_t getArea(RedTile* tile1, RedTile* tile2);

	void passInputLine(std::string input) override;
	void printAnswer() override;
};

