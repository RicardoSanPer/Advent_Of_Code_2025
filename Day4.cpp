#include "Day4.h"
#include <iostream>

int Day4::solvePart1()
{
	int width = board[0].length();

	int height = board.size();

	int adyacentRolls = 0;

	int count = 0;

	//Iterate through each cell in the grid
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			adyacentRolls = 0;

			char current = board[i][j];
			if (current != '@' && current != 'x')
			{
				continue;
			}

			//Iterate through each adjacent cell
			for (int dy = -1; dy < 2; dy++)
			{
				//About testing outside the board
				if (i + dy < 0 || i + dy >= height)
				{
					continue;
				}
				for (int dx = -1; dx < 2; dx++)
				{
					//Avoid testing outside the board or the same cell
					if (j + dx < 0 || j + dx >= width || (dx == 0 && dy == 0))
					{
						continue;
					}
					if (board[i + dy][j + dx] == '@' || board[i + dy][j + dx] == 'x')
					{
						adyacentRolls++;
					}
					if (adyacentRolls > 3)
					{
						break;
					}
				}
				//If 4 or more rolls are adjacent, skip the rest
				if (adyacentRolls >3)
				{
					break;
				}
			}
			//Count only if cell has less than 4 rolls
			if (adyacentRolls < 4)
			{
				//Mark roll for removing for part 2
				board[i][j] = 'x';
				count++;
			}
		}
	}

	return count;
}

int Day4::solvePart2()
{
	int count = 0;

	int width = board[0].length();
	int height = board.size();

	//While there's at leas one roll to remove
	while (solvePart1() > 0)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				//remove, add to the count
				if (board[i][j] == 'x')
				{
					count++;
					board[i][j] = '.';
				}
			}
		}
	}

	return count;
}

void Day4::passInputLine(std::string input)
{
	board.push_back(input);
	
}

void Day4::printAnswer()
{
	int answer1 = solvePart1();

	int answer2 = solvePart2();

	std::cout << "Answer to part 1: " << answer1 << std::endl;
	std::cout << "Answer to part 2: " << answer2 << std::endl;
}
