#include <iostream>
#include <fstream>
#include <string>

#include "Problem.h"
#include "Day1.h"
#include "Day2.h"
#include "Day3.h"
#include "Day4.h"
#include "Day5.h"
#include "Day6.h"
#include "Day7.h"
#include "Day8.h"
#include "Day9.h"
#include "Day10.h"
#include "Day11.h"

int extractProblemNumber(char *argv[]);

int main(int argc, char *argv[])
{
    //A problem number has to be supplied
    if (argc < 2)
    {
        std::cerr << "No problem supplied" << std::endl;
        return 0;
    }
    //An input file has to be supplied
    if (argc < 3)
    {
        std::cerr << "No input file provided" << std::endl;
        return 0;
    }

    int selected_problem = extractProblemNumber(argv);
    //Problem number must be valid
    if (selected_problem < 1)
    {
        std::cerr << "Invalid problem number: " << argv[1] << std::endl;
        return 0;
    }

    std::ifstream fileinput(argv[2], std::ios::in);
    //If file couldnt be opened
    if (!fileinput.is_open())
    {
        std::cerr << "Could not open file: " << argv[2] << std::endl;
        return 0;
    }

    Problem *problem = nullptr;
    //Select problem to solve
    switch (selected_problem)
    {
        case 1: problem = new Day1(); break;
        case 2: problem = new Day2(); break;
        case 3: problem = new Day3(); break;
        case 4: problem = new Day4(); break;
        case 5: problem = new Day5(); break;
        case 6: problem = new Day6(); break;
        case 7: problem = new Day7(); break;
        case 8: problem = new Day8(); break;
        case 9: problem = new Day9(); break;
        case 10: problem = new Day10(); break;
        case 11: problem = new Day11(); break;
        default:
        {
            std::cerr << "Something went wrong with instancing the problem" << std::endl;
            fileinput.close();
            return 0;
        }
    }

    //Solve problem
    problem->Solve(fileinput);
    delete problem;
    fileinput.close();
}

/// @brief Extracts the numeric value of the first command line argument, assuming it is an positive integer
/// @param argv Command line arguments
/// @return Numeric value, -1 if it is not a positive integer
int extractProblemNumber(char* argv[])
{
    int value = 0;

    //Iterate through each digit until \0
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        value *= 10;
        int digit = argv[1][i] - '0';

        if (digit < 0 || digit > 9)
        {
            return -1;
        }

        value += digit;
    }
    return value;
}
