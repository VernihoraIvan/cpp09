#include "BitcoinExchange.hpp"
#include "utils.hpp"

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(std::string filename, std::string dbFilename)
{
    _loadInputData(filename, dbFilename);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    *this = other;
}

BitcoinExchange::~BitcoinExchange(void)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    _data = other._data;
    return *this;
}


void BitcoinExchange::_loadDBData(const std::string &filename, const std::string &dbFilename)
{
    std::ifstream dbFile(dbFilename.c_str());
    std::ifstream inputFile(filename.c_str());

    if (!inputFile.is_open())
    {
        std::cerr << "Error: could not open inputFile " << dbFilename << std::endl;
        return;
    }
    if (!dbFile.is_open())
    {
        std::cerr << "Error: could not open dbFile " << filename << std::endl;
        return;
    }

    std::string line;
    
    while(std::getline(dbFile, line))
    {
        if (line == "date,exchange_rate")
            continue;
        std::string date = trim(line.substr(0, line.find(",")));
        std::string value = trim(line.substr(line.find(",") + 1));

        if (isDateValid(date))
        {
            std::cerr << "Error: invalid date " << date << std::endl;
            continue;
        }

        if (isValueValid(value))
        {
            std::cerr << "Error: invalid value " << value << std::endl;
            continue;
        }
       
        _data[date] = std::stod(value);
        
    }
}