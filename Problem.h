#pragma once
#include <string>
#include<fstream>

/// @brief Base class for problems
class Problem
{
private:
	/// @brief Pass the current input line to solve
	/// @param inputLine 
	void virtual passInputLine(std::string inputLine) {}
	/// @brief Prints the answer
	void virtual printAnswer() {}
public:
	/// @brief Solve the problem
	/// @param input Input File Stream
	void Solve(std::ifstream& input);
};

