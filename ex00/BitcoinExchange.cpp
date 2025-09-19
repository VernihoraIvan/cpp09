#include "BitcoinExchange.hpp"
#include "utils.hpp"

BitcoinExchange::BitcoinExchange(void)
{
    std::cerr << RED << "Error: provide input and db filenames" << RESET << std::endl;
}

BitcoinExchange::BitcoinExchange(std::string inputFilename, std::string dbFilename)
{
    _loadDBData(dbFilename);
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
    if (this != &other) {
        _data = other._data;
        _outputData = other._outputData;
    }
    return *this;
}

double BitcoinExchange::_findClosestRate(const std::string &date)
{
    if (_data.find(date) != _data.end())
        return _data[date];

    std::map<std::string, double>::iterator it = _data.upper_bound(date);

    if (it == _data.begin())
    {
        std::cerr << RED << "Error: no exchange rate available for date " << date << " or earlier" << RESET << std::endl;
        return -1;
    }

    --it;
    return it->second;
}

void BitcoinExchange::_parseInputData(const std::string &inputFilename)
{
    std::ifstream inputFile(inputFilename.c_str());
    std::string line;

    if (!inputFile.is_open())
    {
        std::cerr << RED << "Error: could not open inputFile " << inputFilename << RESET << std::endl;
        return;
    }

    while (std::getline(inputFile, line))
    {
        if (line == "date | value")
            continue;

        size_t delimeterPos = line.find("|");
        if (delimeterPos == std::string::npos)
        {
            std::cerr << RED << "Error: invalid format in line: " << line << RESET << std::endl;
            continue;
        }

        std::string date = trim(line.substr(0, delimeterPos));
        std::string value = trim(line.substr(delimeterPos + 1));

        if (isDateInvalid(date))
        {
            std::cerr << RED << "Error: invalid date " << date << " in input file " << inputFilename << RESET << std::endl;
            continue;
        }
        if (value.empty() || isValueInvalid(value, true))
        {

            std::cerr << RED << "Error: invalid value " << value << " in input file " << inputFilename << RESET << std::endl;
            continue;
        }

        double rate = _findClosestRate(date);

        if (rate == -1)
            continue;

        _outputData[date] = std::stod(value) * rate;
        std::cout << date << " => " << std::stod(value) << " = " << _outputData[date] << std::endl;
    }
}

void BitcoinExchange::_loadDBData(const std::string &dbFilename)
{
    std::ifstream dbFile(dbFilename.c_str());

    if (!dbFile.is_open())
    {
        std::cerr << RED << "Error: could not open dbFile " << dbFilename << RESET << std::endl;
        return;
    }

    std::string line;

    while (std::getline(dbFile, line))
    {
        if (line == "date,exchange_rate")
            continue;

        size_t delimeterPos = line.find(",");
        if (delimeterPos == std::string::npos)
        {
            std::cerr << RED << "Error: invalid format in line: " << line << RESET << std::endl;
            continue;
        }

        std::string date = trim(line.substr(0, delimeterPos));
        std::string value = trim(line.substr(delimeterPos + 1));

        if (isDateInvalid(date))
        {
            std::cerr << RED << "Error: invalid date " << date << RESET << std::endl;
            continue;
        }

        if (isValueInvalid(value))
        {
            std::cerr << RED << "Error: invalid value " << value << RESET << std::endl;
            continue;
        }

        _data[date] = std::stod(value);
    }
}