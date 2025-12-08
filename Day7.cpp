#include "Day7.h"


void Day7::passInputLine(std::string input)
{
	if (previous_line.empty())
	{
		for (char c : input)
		{
			if (c == 'S')
			{
				paths.push_back(1);
				previous_line += '|';
			}
			else
			{
				paths.push_back(0);
				previous_line += c;
			}
		}
		return;
	}

	std::string newLine;

	for (int i = 0; i < input.length(); i++)
	{
		char c = previous_line[i];

		//If the current character in the line is a split and
		//is hit by a beam, split beam
		if (input[i] == '^' && c == '|')
		{
			splits++;
			uint64_t value = paths[i];

			paths[i] = 0;
			//Change cells to beam
			if (i >= 1)
			{
				previous_line[i - 1] = '|';
				paths[i - 1] += value;

			}
			//Clear current cell from beam
			previous_line[i] =  '.';
			//Change next cell to beam
			if (i <= input.length() - 1)
			{
				previous_line[i + 1] = '|';
				paths[i + 1] += value;
				i++;
			}
			continue;
		}
	}
}

void Day7::printAnswer()
{
	for (uint64_t v : paths)
	{
		timelines += v;
	}
	std::cout << "Answer to part 1: " << splits << std::endl;
	std::cout << "Answer to part 2: " << timelines << std::endl;
}
