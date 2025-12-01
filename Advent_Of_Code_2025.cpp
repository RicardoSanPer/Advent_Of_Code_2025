#include <iostream>
#include <fstream>
#include <string>

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
    
    std::string line;

    while (std::getline(fileinput, line))
    {
        std::cout << line << std::endl;
    }

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
