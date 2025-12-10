#include "Day9.h"

/// Part 2:
/// For every corner
/// 1. Pic another corner
/// 2. For every corner in the list, check if any cuts into the square:
///		- If previous was outside rectangle and current is within (not including edges), rectangle is not valid

void Day9::passInputLine(std::string input)
{
	std::string number;
	RedTile* tile = new RedTile();

	for (char c : input)
	{
		if (c == ',')
		{
			tile->x = stringToUint64(number);
			number.clear();
			continue;
		}
		number += c;
	}
	tile->y = stringToUint64(number);
	tiles.push_back(tile);
}

void Day9::processPart1()
{
	uint64_t area = 0;
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = i + 1; j < tiles.size(); j++)
		{
			area = getArea(tiles[i], tiles[j]);
			if (area > answer1)
			{
				answer1 = area;
			}
		}
	}
}

void Day9::processPart2()
{
	RedTile* currentTile;
	RedTile* currentCorner;
	for (int i = 0; i < tiles.size(); i++)
	{
		currentTile = tiles[i];
		for (int j = i + 1; j < tiles.size(); j++)
		{
			currentCorner = tiles[j];
			testCorners(currentTile, currentCorner);
		}
	}
}


void Day9::testCorners(RedTile* corner1, RedTile* corner2)
{
	uint64_t top = 0;
	uint64_t bottom = 0;
	uint64_t left = 0;
	uint64_t right = 0;

	//std::cout << "Testing: " << corner1->x << ", " << corner1->y << " : " << corner2->x << ", " << corner2->y << std::endl;

	//Bounding box
	if (corner1->x > corner2->x)
	{
		right = corner1->x;
		left = corner2->x;
	}
	else
	{
		right = corner2->x;
		left = corner1->x;
	}

	if (corner1->y > corner2->y)
	{
		top = corner1->y;
		bottom = corner2->y;
	}
	else
	{
		top = corner2->y;
		bottom = corner1->y;
	}

	RedTile* testTile;

	uint64_t x = tiles[0]->x;
	uint64_t y = tiles[0]->y;

	uint64_t prevx = tiles[tiles.size() - 1]-> x;
	uint64_t prevy = tiles[tiles.size() - 1]-> y;

	uint64_t area = 0;
	for (int i = 0; i < tiles.size(); i++)
	{
		testTile = tiles[i];
		x = testTile->x;
		y = testTile->y;

		//std::cout << "\tTesting edge: " << prevx << ", " << prevy << " : " << x << ", " << y << " ";

		if (prevx <= left && x <= left)
		{
			//std::cout << "Out (LEFT)" << std::endl;
			prevx = x;
			prevy = y;
			continue;
		}

		if (prevx >= right && x >= right)
		{
			//std::cout << "Out (RIGHT)" << std::endl;
			prevx = x;
			prevy = y;
			continue;
		}

		if (prevy <= bottom && y <= bottom)
		{
			//std::cout << "Out (BOTTOM)" << std::endl;
			prevx = x;
			prevy = y;
			continue;
		}

		if (prevy >= top && y >= top)
		{
			//std::cout << "Out (TOP)" << std::endl;
			prevx = x;
			prevy = y;
			continue;
		}
		
		//std::cout << "FAILED" << std::endl;

		return;

	}

	area = (1 + right - left) * (1 + top - bottom);
	if (area > answer2)
	{
		answer2 = area;
		//std::cout << "Largest: " << corner1->x << ", " << corner1->y << " and " << corner2->x << ", " << corner2->y << std::endl;
	}
}


uint64_t Day9::getArea(RedTile* tile1, RedTile* tile2)
{
	uint64_t x = 0;
	uint64_t y = 0;

	if (tile1->x > tile2->x)
	{
		x = (tile1->x) - (tile2->x);
	}
	else
	{
		x = (tile2->x) - (tile1->x);
	}

	if (tile1->y > tile2->y)
	{
		y = (tile1->y) - (tile2->y);
	}
	else
	{
		y = (tile2->y) - (tile1->y);
	}

	return (x  + 1) * (y + 1);
}

void Day9::printAnswer()
{
	processPart1();
	processPart2();

	std::cout << "Answer to part 1: " <<  answer1 << std::endl;
	std::cout << "Answer to part 2: " <<  answer2 << std::endl;
}
