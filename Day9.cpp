#include "Day9.h"

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

	std::cout << answer1 << std::endl;
}
