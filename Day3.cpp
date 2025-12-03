#include "Day3.h"
#include <iostream>
void Day3::passInputLine(std::string input)
{
	char digit1 = '0';
	char digit2 = '0';

	for (char digit : input)
	{
		if (digit2 > digit1)
		{
			digit1 = digit2;
			digit2 = '0';
		}
		if (digit > digit2)
		{
			digit2 = digit;
		}
	}
	int temp = 0;
	temp += digit1 - '0';
	temp *= 10;
	temp += digit2 - '0';

	answer += temp;
}

void Day3::printAnswer()
{
	std::cout << "Answer to part 1: " << answer << std::endl;
}
