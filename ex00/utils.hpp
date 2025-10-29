#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

#define VALUE_MAX 1000.0
#define VALUE_MIN 0.0

std::string trim(const std::string& str);
int isDateInvalid(const std::string& date);
int isValueInvalid(const std::string& value, bool isInput);
double parseDouble(const std::string& s);


#endif
