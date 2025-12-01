#include <iostream>

int extractProblemNumber(char *argv[]);

int main(int argc, char *argv[])
{
    //A problem number has to be supplied
    if (argc < 2)
    {
        std::cout << "No problem supplied" << std::endl;
        return 0;
    }

    int selected_problem = extractProblemNumber(argv);

    if (selected_problem < 1)
    {
        std::cerr << "Invalid problem number: " << argv[1] << std::endl;
        return 0;
    }
    
    std::cout << selected_problem << std::endl;
    
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
