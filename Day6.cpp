#include "Day6.h"

void Day6::processInputPart1(std::string input)
{
	std::string number;

	int index = 0;
	bool isOperator = false;
	bool previousWasSpace = true;

	if (input.empty())
	{
		operatorInput = true;
		return;
	}

	if (!operatorInput)
	{
		valuesPart2.push_back(input);
	}

	for (char c : input)
	{
		//If its a number, extract digit
		if (c >= '0' && c <= '9')
		{
			previousWasSpace = false;
			number += c;
		}
		//If operator, add to list
		else if (c == '*' || c == '+')
		{
			operators += c;
			previousWasSpace = false;
			isOperator = true;
		}
		//Space
		else if (c == ' ')
		{
			//If previous character was a space (case where there are multiple spaces between values)
			//or an operator, do not modify list of values
			if (previousWasSpace || isOperator)
			{
				continue;
			}

			//Otherwise add value to the corresponding column
			addNumberToColumn(number, index);
			number.clear();
			previousWasSpace = true;
			index++;
		}
	}
	//Add missing numeric value in case there were no trailing spaces
	if (!number.empty() && !isOperator)
	{
		addNumberToColumn(number, index);
	}
}

void Day6::processInputPart2()
{
	uint64_t columnValue = 0;
	int column = 0;

	//Initial value of the colum value to facilitate operations
	char op = operators[column];
	if (op == '*')
	{
		columnValue = 1;
	}
	else
	{
		columnValue = 0;
	}

	//Iterate top to bottom, left to right
	for (int i = 0; i < valuesPart2[0].size(); i++)
	{
		uint64_t value = 0;
		int spaceCount = 0;

		for (int j = 0; j < valuesPart2.size(); j++)
		{
			char c = valuesPart2[j][i];

			//If the character is a digit, add to the current value
			if (c >= '0' && c <= '9')
			{
				value *= 10;
				value += c - '0';
			}
			//Otherwise ignore
			else if (c == ' ')
			{
				spaceCount++;
			}
		}
		//If the current column line was all spaces (column delimiter),
		//add the column value to the total value (answer)
		if (spaceCount >= valuesPart2.size())
		{
			spaceCount = 0;

			//Add column value
			answer2 += columnValue;

			//advance column
			column++;
			//Starting value of column value according to operator
			char op = operators[column];
			if (op == '*')
			{
				columnValue = 1;
			}
			else
			{
				columnValue = 0;
			}
		}
		//Otherwise if the column line was a number
		//add to value of column according to operator
		else
		{
			char op = operators[column];
			if (op == '*')
			{
				columnValue *= value;
			}
			else
			{
				columnValue += value;
			}
		}
	}
	//Add value of last column
	answer2 += columnValue;
	
}

void Day6::processAnswerPart1()
{
	//Process values for part 1
	for (int i = 0; i < operators.length(); i++)
	{
		char op = operators[i];
		uint64_t value = op == '+' ? 0 : 1;

		for (uint64_t v : values[i])
		{
			if (op == '*')
			{
				value *= v;
			}
			else
			{
				value += v;
			}
		}
		answer1 += value;
	}
}

/// @brief Add number to the current column list
/// @param number 
/// @param index 
void Day6::addNumberToColumn(std::string number, int index)
{
	if (index >= values.size())
	{
		std::vector<uint64_t> line;
		values.push_back(line);
	}

	values[index].push_back(stringToUint64(number));
}

void Day6::passInputLine(std::string input)
{
	processInputPart1(input);
}

void Day6::printAnswer()
{
	processAnswerPart1();
	processInputPart2();

	std::cout << "Answer to part 1: " << answer1 << std::endl;
	std::cout << "Answer to part 2: " << answer2 << std::endl;

}
