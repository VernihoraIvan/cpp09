#include <string>
#include <iostream>
#include <stack>

int isOperator(const std::string& str)
{
    return str == "+" || str == "-" || str == "*" || str == "/";
}
