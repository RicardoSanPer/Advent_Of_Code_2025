#include <iostream>

int main(int argc, char *argv[])
{
    //A problem number has to be supplied
    if (argc < 2)
    {
        std::cout << "No problem supplied" << std::endl;
        return 0;
    }

    int selected_problem = 0;

    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        selected_problem *= 10;
        int digit = argv[1][i] - '0';
        
        if (digit < 0 || digit > 9)
        {
            std::cerr << "Invalid number: " << argv[1] << std::endl;
            return 0;
        }

        selected_problem += digit;
    }
    
    std::cout << selected_problem << std::endl;
    
}
