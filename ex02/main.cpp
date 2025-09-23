#include <string>
#include <iostream>
#include "PmergeMe.hpp"

#define RED "\033[31m"
#define RESET "\033[0m"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << RED << "Error: wrong amount of arguements" << RESET << std::endl;
        std::cerr << "Usage: ./PmergeMe <sequence>" << std::endl;
        return 1;
    }
    PmergeMe pmergeMe;

    try
    {
        pmergeMe.parseAndStore(argc, argv);
        pmergeMe.executeSort();
        pmergeMe.printResults();
    }
    catch(const std::exception& e)
    {
        std::cerr << RED << e.what() << RESET << std::endl;
    }
    
    return 0;
}