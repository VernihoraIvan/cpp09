#include "RPN.hpp"
#include "utils.hpp"
#include <stack>
#include <sstream>
#include <cstdlib>
#include <cerrno>
#include <iostream>

RPN::RPN()
{
}
RPN::RPN(const RPN &other)
{
    (void)other;
}
RPN &RPN::operator=(const RPN &other)
{
    (void)other;
    return *this;
}
RPN::~RPN()
{
}

void RPN::process(const std::string &expression)
{
    // std::stack<int> stack;

    if (!isValidExpression(expression))
        throw std::invalid_argument("Invalid expression");
}