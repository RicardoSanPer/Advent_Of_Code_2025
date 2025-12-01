#pragma once
#include <string>
/// @brief Class containing the functions to solve the day 1 problem.
///	Given a safe with a dial marked from 0 to 99, starting at 50, instructions
/// are provided on how to turn it, in the format LN or RN, where R/L are the
/// directions to which turn the dial, and N the number of times to turn it.
/// The password is the number of times the dial lands in 0 after each rotation.
class Day1
{
private:
	int dial_pos = 50;
	int max_dial_pos = 99;
	int password = 0;

	int getDirection(char c);
	int getTimes(std::string input);
public:
	void Rotate(std::string input);
	int GetPassword();
};

