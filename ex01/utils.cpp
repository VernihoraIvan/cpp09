#include <string>
#include <iostream>
#include <stack>

int isOperator(const std::string& str)
{
    return str == "+" || str == "-" || str == "*" || str == "/";
}

bool isValidExpression(const std::string& expression)
{
    std::stack<double> stack;

    for (size_t i = 0; i < expression.length(); i++)
    {
        if (std::isspace(expression[i]))
            continue;
        if (isdigit(expression[i]))
        {
            std::cout << "isdigit: " << expression[i] << std::endl;
            stack.push(static_cast<double>(expression[i] - '0'));
        }
        else if (isOperator(std::string(1, expression[i])) )
        {
            std::cout << "isOperator: " << expression[i] << std::endl;
            if (stack.size() < 2)
                return false;
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
                    stack.push(a / b);
                    break;
            }
            continue;
        }
        else
            return false;
    }
    if (stack.size() != 1)
        return false;
    std::cout << stack.top() << std::endl;
    return true;
}