

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <cmath>

class BitcoinExchange
{
    public:
        BitcoinExchange(void);
        ~BitcoinExchange(void);
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        BitcoinExchange(std::string filename, std::string dbFilename);
    
    private:
        void _parseInputData(const std::string &inputFilename);
        void _loadDBData(const std::string &dbFilename);
        double _findClosestRate(const std::string &date);

        std::map<std::string, double> _data;
        std::map<std::string, double> _outputData;

        
};

#endif
