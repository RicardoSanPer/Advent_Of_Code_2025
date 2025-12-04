#include "Day2.h"
#include <vector>
#include <string>
#include <iostream>

/// @brief Given the limits of the range, obtains IDs in it and checks their validity
/// @param id1 lower limit
/// @param id2 upper limit
void Day2::process(std::string id1, std::string id2)
{
	uint64_t low = stringToUint64(id1);
	uint64_t top = stringToUint64(id2);

	for (uint64_t i = low; i <= top; i++)
	{
		if (!checkForIdValidity(std::to_string(i)))
		{
			sum_part1 += i;
		}
		if (!checkForIdValidity2(std::to_string(i)))
		{
			sum_part2 += i;
			i++;
		}
	}
}

/// @brief Check for the validity of an ID, that is the number is not a sequence of numbers repeating twice
/// @param input 
/// @return bool indicating validity
bool Day2::checkForIdValidity(std::string input)
{
	//Since an invalid string must be composed of a string repeated twice
	//we can first check if the input ID is even
	if (input.length() % 2 != 0)
	{
		return true;
	}

	int half = input.length() / 2;
	//Compare each char of the first and second half. If there's any differente, then the ID is valid
	return input.substr(0, half) != input.substr(half);
}

bool Day2::checkForIdValidity2(std::string input)
{
	//For part 2. We find factors for the length
	std::vector<int> factors = {};
	for (int i = 2; i <= input.length(); i++)
	{
		if (input.length() % i == 0)
		{
			factors.push_back(i);
		}
	}

	//For each factor
	for (int factor : factors)
	{
		bool different = false;
		int length = input.length() / factor;

		//We compare the first block with all the others
		for (int i = 1; i < factor; i++)
		{
			if (input.substr(0, length) != input.substr(length * i, length))
			{
				different = true;
				break;
			}
		}
		//If blocks are different, try next factor
		if (different)
		{
			different = false;
			continue;
		}
		//Otherwise, blocks are equal and the id is not valid
		return false;
	}

	return true;
}

/// @brief Obtains the ranges from the input
/// @param input 
void Day2::passInputLine(std::string input)
{
	std::string id1;
	std::string id2;

	bool first_id = true;

	for (int i = 0; i < input.length(); i++)
	{
		char c = input[i];

		//If the current character is a delimiter, process the range and clear for the next one
		if (c == ',')
		{
			process(id1, id2);

			first_id = true;
			id1.clear();
			id2.clear();
		}
		//Switch to the other range limit
		else if (c == '-')
		{
			first_id = false;
		}
		//Extract the ranges
		else if (c >= '0' && c <= '9')
		{
			if (first_id)
			{
				id1 += c;
			}
			else
			{
				id2 += c;
			}
		}
	}
	//Process last pair in case of eof/eol
	process(id1, id2);
}

void Day2::printAnswer()
{
	std::cout << "Answer for part 1: " << sum_part1 << std::endl;
	std::cout << "Answer for part 2: " << sum_part2 << std::endl;
}
