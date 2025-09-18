

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
        void _loadInputData(const std::string &filename, const std::string &dbFilename);
        void _loadDBData(const std::string &filename, const std::string &dbFilename);

        std::map<std::string, double> _data;

        
};

#endif
