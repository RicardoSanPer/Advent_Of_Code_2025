#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <tuple>

/// @brief Base class for problems
class Problem
{
private:
	/// @brief Pass the current input line to interpret as needed by the problem
	/// @param inputLine 
	void virtual passInputLine(std::string inputLine) {}
	/// @brief Prints the answer
	void virtual printAnswer() {}

public:
	/// @brief Solve the problem
	/// @param input Input File Stream
	void Solve(std::ifstream& input);
	uint64_t stringToUint64(std::string input);
	int stringToInt(std::string input);
};

