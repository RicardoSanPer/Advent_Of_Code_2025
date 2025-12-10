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
	uint64_t answer2 = 0;
	std::vector<RedTile*> tiles;

	void processPart1();
	void processPart2();
	void testCorners(RedTile* corner1, RedTile* corner2);

	uint64_t getArea(RedTile* tile1, RedTile* tile2);

	void passInputLine(std::string input) override;
	void printAnswer() override;
};

