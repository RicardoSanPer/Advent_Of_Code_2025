#include "Day1.h"
#include <iostream>

/// @brief Given a character, determines if it is rotating left or right. Input is in the form 'LN' or 'RN', where L and R are the directions to extract
/// @param c Direction
/// @return -1 for left, 1 for right, 0 if invalid
int Day1::getDirection(char c)
{
	int multiplier = 0;
	if (c == 'L' || c == 'l')
	{
		multiplier = -1;
	}
	else if (c == 'R' || c == 'r')
	{
		multiplier = 1;
	}
	return multiplier;
}

/// @brief Given an input, determines how many times to turn the dial. Input is in the form 'LN' or 'RN', where N is the number to extract
/// @param input
/// @return Number of times to turn, -1 if invalid number
int Day1::getTimes(std::string input)
{
	int value = 0;
	for (int i = 1; i < input.length(); i++)
	{
		int digit = input[i] - '0';
		if (digit < 0 || digit > 9)
		{
			return -1;
		}
		value *= 10;
		value += digit;
	}
	return value;
}

/// @brief Rotates the dial. Everytime it lands in '0' it updates the password.
/// @param input Input in the format Direction + Times to turn
void Day1::Rotate(std::string input)
{
	if (input.empty())
	{
		return;
	}
	//Get direction
	int direction = getDirection(input[0]);
	if (direction == 0)
	{
		std::cerr << "Not a valid direction: " << input << "\n Must be 'L' or 'R'" << std::endl;
		return;
	}
	//Get times to turn
	int times = getTimes(input);
	if (times < 0)
	{
		std::cerr << "Not a valid number: " << input << std::endl;
		return;
	}

	//Rotate
	dial_pos += direction * times;
	dial_pos = dial_pos % (max_dial_pos + 1);
	
	//Update password
	if (dial_pos == 0)
	{
		password++;
	}
}

/// @brief Retrieves the password
/// @return password
int Day1::GetPassword()
{
	return password;
}
