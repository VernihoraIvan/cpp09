#include "BitcoinExchange.hpp"
#include "utils.hpp"

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(std::string inputFilename, std::string dbFilename)
{
    _loadDBData(inputFilename, dbFilename);
    _parseInputData(inputFilename);
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

void BitcoinExchange::_parseInputData(const std::string &inputFilename)
{
    std::ifstream inputFile(inputFilename.c_str());
    std::string line;
    while(std::getline(inputFile, line))
    {
        if (line == "date | value")
            continue;
        std::string date = trim(line.substr(0, line.find("|")));
        std::string value = trim(line.substr(line.find("|") + 1));

        // std::cout << "date: " << date << " value: " << value << std::endl;
        if (isDateInvalid(date))
        {
            std::cerr << "Error: invalid date " << date << " in input file " << inputFilename << std::endl;
            continue;
        }
        if (value.empty() || isValueInvalid(value))
        {

            std::cerr << "Error: invalid value " << value << " in input file " << inputFilename << std::endl;
            continue;
        }

        _outputData[date] = std::stod(value) * _data[date];
        // std::cout << date << " | " << _outputData[date] << std::endl;
    }
}



void BitcoinExchange::_loadDBData(const std::string &inputFilename, const std::string &dbFilename)
{
    std::ifstream dbFile(dbFilename.c_str());
    std::ifstream inputFile(inputFilename.c_str());

    if (!inputFile.is_open())
    {
        std::cerr << "Error: could not open inputFile " << inputFilename << std::endl;
        return;
    }
    if (!dbFile.is_open())
    {
        std::cerr << "Error: could not open dbFile " << dbFilename << std::endl;
        return;
    }

    std::string line;
    
    while(std::getline(dbFile, line))
    {
        if (line == "date,exchange_rate")
            continue;
        std::string date = trim(line.substr(0, line.find(",")));
        std::string value = trim(line.substr(line.find(",") + 1));

        if (isDateInvalid(date))
        {
            std::cerr << "Error: invalid date " << date << std::endl;
            continue;
        }

        if (isValueInvalid(value))
        {
            std::cerr << "Error: invalid value " << value << std::endl;
            continue;
        }
       
        _data[date] = std::stod(value);
        
    }
}