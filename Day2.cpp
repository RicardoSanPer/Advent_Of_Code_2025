#include "Day2.h"
#include <vector>
#include <string>
#include <iostream>

/// @brief Given the limits of the range, obtains IDs in it and checks their validity
/// @param id1 lower limit
/// @param id2 upper limit
void Day2::process(std::string id1, std::string id2)
{
	uint64_t low = stringToInt(id1);
	uint64_t top = stringToInt(id2);

	for (uint64_t i = low; i <= top; i++)
	{
		if (!checkForIdValidity(std::to_string(i)))
		{
			sum += i;
			//std::cout << "Invalid: " << i << std::endl;
		}
	}
}
/// @brief Convert a string to int, assuming it is valid
/// @param s 
/// @return int
uint64_t Day2::stringToInt(std::string s)
{
	uint64_t value = 0;
	for (char c : s)
	{
		value *= 10;
		value += c - '0';
	}
	return value;
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
	//Process last pair
	process(id1, id2);
}

void Day2::printAnswer()
{
	std::cout << "Sum of invalid IDs: " << sum << std::endl;
}
