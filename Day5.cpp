#include "Day5.h"

void Day5::processPart2()
{
	//Iterate through each range
	for (int i = 0; i < ranges.size(); i++)
	{
		std::tuple<uint64_t, uint64_t> range = ranges[i];
		uint64_t lower = std::get<0>(range);
		uint64_t top = std::get<1>(range);

		//Test with ranges not yet tested
		for (int j = i + 1; j < ranges.size(); j++)
		{
			std::tuple<uint64_t, uint64_t> sampleRange = ranges[j];
			uint64_t sampleLow = std::get<0>(sampleRange);
			uint64_t sampleHigh = std::get<1>(sampleRange);

			/// 3 cases
			/// range is within range being testes (subrange of another range): skip by creating invalid range, no unique elements
			if (lower >= sampleLow && top <= sampleHigh)
			{
				lower = 1;
				top = 0;
				break;
			}
			/// Lower bound is within range, top isnt: reduce range size by shifting the lower bound to the sample top bound + 1
			else if (lower >= sampleLow && lower <= sampleHigh)
			{
				lower = sampleHigh + 1;
				continue;
			}
			/// Lower bound is outside range, higher one is within range: reduce range size by shifting higher bound to sample low bound - 1
			else if(top >= sampleLow && top <= sampleHigh)
			{
				top = sampleLow - 1;
				continue;
			}
			/// Range that is being sampled is fully cointainted within the range: split range
			else if (lower < sampleLow && top > sampleHigh)
			{
				uint64_t newLow = sampleLow + 1;
				uint64_t newTop = top;

				top = sampleLow - 1;
				ranges.push_back(std::make_tuple(newLow, newTop));
			}


		}

		if (top < lower)
		{
			//std::cout << "[" << std::get<0>(range) << ":" << std::get<1>(range) << "] Count : 0" << std::endl;
			
			continue;
		}
		else
		{
			answer2 += (top - lower) + 1;
		}
	}
}

void Day5::passInputLine(std::string input)
{
	if (input.empty())
	{
		isRange = false;
	}
	
	//If the entry denotes a range
	if (isRange)
	{
		std::string first;
		std::string second;
		bool firstNumber = true;

		//Extract values
		for (char c : input)
		{
			//Switch to upper limit
			if (c == '-')
			{
				firstNumber = false;
				continue;
			}
			if (firstNumber)
			{
				first += c;
			}
			else
			{
				second += c;
			}
		}
		//Create range
		uint64_t firstn = stringToUint64(first);
		uint64_t secondn = stringToUint64(second);

		ranges.push_back(std::make_tuple(firstn, secondn));
	}
	else
	{
		uint64_t value = stringToUint64(input);
		//Search for a range the vallue of the input falls in
		for (std::tuple<uint64_t, uint64_t> range : ranges)
		{
			//Mark as fresh if it's within any range
			if (value >= std::get<0>(range) && value <= std::get<1>(range))
			{
				answer1++;
				break;
			}
		}
	}
}

void Day5::printAnswer()
{
	processPart2();
	std::cout << "Answer to part 1: " << answer1 << std::endl;
	std::cout << "Answer to part 2: " << answer2 << std::endl;
}
