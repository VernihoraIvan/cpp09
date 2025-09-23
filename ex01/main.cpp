#include <string>
#include <iostream>
#include "RPN.hpp"

#define RED "\033[31m"
#define RESET "\033[0m"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << RED << "Error: wrong amount of arguements" << RESET << std::endl;
        return 1;
    }

    std::string filename(argv[1]);
    try
    {
        RPN::process(filename);
    }
    catch (const std::exception &e)
    {
        std::cerr << RED << e.what() << RESET << std::endl;
    }
    return 0;
}