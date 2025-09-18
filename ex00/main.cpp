#include <string>
#include <iostream>
#include "BitcoinExchange.hpp"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: wrong amount of arguements" << std::endl;
        return 1;
    }

    std::string filename(argv[1]);
    BitcoinExchange btc(filename, "assets/data.csv");
    // btc.loadData(argv[1]);
    return 0;
}