#include "Day3.h"
#include <iostream>

void Day3::solvePart1(std::string input)
{
	char digit1 = '0';
	char digit2 = '0';

	for (char digit : input)
	{
		//first we check if the left digit is bigger than the right one
		if (digit2 > digit1)
		{
			//If it is, we shift the number, since the number will be bigger now
			//regardless of whichever digit substitutes the right one
			digit1 = digit2;
			digit2 = '0';
		}
		//If no shift is done, we simply try to replace the right one
		if (digit > digit2)
		{
			digit2 = digit;
		}
	}
	//Convert to int for the answer
	int temp = 0;
	temp += digit1 - '0';
	temp *= 10;
	temp += digit2 - '0';

	answer += temp;
}
void Day3::solvePart2(std::string input)
{
	//We start with a candidate highest number by picking the last 12 digits of the input
	std::string number = input.substr(input.length() -12, 12);

	//We now test each of the digits to the left of it one by one
	for (int i = input.length() - 13; i >= 0; i--)
	{
		char c = input[i];

		//If the current digit being testes is bigger than the leftmost one of the candidate, a shift must be done
		if (c >= number[0])
		{
			//Switch the leftmost digit and keep the old one to test the rest of the digits in the candidate
			char temp = number[0];
			number[0] = c;

			for (int j = 1; j < number.length(); j++)
			{
				char temp2 = number[j];
				//If the leftover digit is equal or larger than the right one,
				//we effectively move the whole block to the right to keep it
				if (temp >= number[j])
				{
					number[j] = temp;
					temp = temp2;
				}
				//Otherwise the leftover digit is "squeezed out" of the candidate number
				else
				{
					break;
				}
			}
		}
	}
	answer2 +=  stringToUint64(number);
}
void Day3::passInputLine(std::string input)
{
	solvePart1(input);
	solvePart2(input);
}

void Day3::printAnswer()
{
	std::cout << "Answer to part 1: " << answer << std::endl;
	std::cout << "Answer to part 2: " << answer2 << std::endl;
}
