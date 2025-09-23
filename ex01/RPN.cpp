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
    std::stack<double> stack;

    for (size_t i = 0; i < expression.length(); i++)
    {
        if (std::isspace(expression[i]))
            continue;
        if (isdigit(expression[i]))
        {
            stack.push(static_cast<double>(expression[i] - '0'));
        }
        else if (isOperator(std::string(1, expression[i])) )
        {
            if (stack.size() < 2)
                throw std::runtime_error("Error: not enough operands");
            double b = stack.top();
            stack.pop();
            double a = stack.top();
            stack.pop();
            switch (expression[i])
            {
                case '+':
                    stack.push(a + b);
                    break;
                case '-':
                    stack.push(a - b);
                    break;
                case '*':
                    stack.push(a * b);
                    break;
                case '/':
                    if (b == 0)
                        throw std::runtime_error("Error: division by zero");
                    stack.push(a / b);
                    break;
            }
            continue;
        }
        else
            throw std::runtime_error("Error: invalid character");
    }
    if (stack.size() != 1)
        throw std::runtime_error("Error: not enough operands");
    std::cout << stack.top() << std::endl;
    return;
}