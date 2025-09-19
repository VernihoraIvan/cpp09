#include <string>
#include <cstddef>
#include <sstream>
#include <iostream>

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

int isDateInvalid(const std::string& date) {

    if (date.find_first_not_of("0123456789-") != std::string::npos)
        return 1;

    std::stringstream ss(date);
    int year, month, day;
    char dash;
    ss >> year >> dash >> month >> dash >> day;

    struct tm timeinfo = {};
    timeinfo.tm_year = year - 1900; 
    timeinfo.tm_mon = month - 1;     
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = 0;
    timeinfo.tm_min = 0;
    timeinfo.tm_sec = 0;
    timeinfo.tm_isdst = -1;
    
    if (timeinfo.tm_mon < 0 || timeinfo.tm_mon > 11)
        return 1;
    if (timeinfo.tm_mday < 1 || timeinfo.tm_mday > 31)
        return 1;
    if (timeinfo.tm_year < 0)
        return 1;
    
    time_t timestamp = mktime(&timeinfo);

    std::time_t now = std::time(nullptr); 


    if (timestamp == -1 || timestamp > now)
        return 1;

    return ss.fail();
}

int isValueInvalid(const std::string& value, bool isInput = false)
{
    if (isInput && (std::stod(value) < 0 || std::stod(value) > 1000))
        return 1;
    if (value.find_first_not_of("0123456789.") != std::string::npos)
        return 1;
    return 0;
}