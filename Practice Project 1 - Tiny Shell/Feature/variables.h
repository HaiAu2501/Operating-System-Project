#ifndef VARIABLES_H
#define VARIABLES_H

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <stdexcept>
#include <stack>
#include <vector>
#include <algorithm>

class VariableManager
{
private:
    std::map<std::string, std::string> variables;

    bool isOperator(char c)
    {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
    }

    int precedence(char op)
    {
        if (op == '+' || op == '-')
            return 1;
        if (op == '*' || op == '/')
            return 2;
        return 0;
    }

    double applyOperation(double a, double b, char op)
    {
        switch (op)
        {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0)
                throw std::runtime_error("Division by zero.");
            return a / b;
        default:
            throw std::runtime_error("Invalid operator.");
        }
    }

    std::vector<std::string> tokenize(const std::string &expression)
    {
        std::vector<std::string> tokens;
        std::string token;
        for (size_t i = 0; i < expression.size(); ++i)
        {
            char c = expression[i];
            if (std::isspace(c))
                continue;

            if (isOperator(c))
            {
                if (!token.empty())
                {
                    tokens.push_back(token);
                    token.clear();
                }
                tokens.push_back(std::string(1, c));
            }
            else
            {
                token += c;
            }
        }
        if (!token.empty())
        {
            tokens.push_back(token);
        }
        return tokens;
    }

    double evaluatePostfix(const std::vector<std::string> &postfix)
    {
        std::stack<double> values;
        for (const std::string &token : postfix)
        {
            if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1])))
            {
                values.push(std::stod(token));
            }
            else if (isOperator(token[0]) && token.size() == 1)
            {
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();
                values.push(applyOperation(a, b, token[0]));
            }
            else
            {
                values.push(std::stod(variables[token]));
            }
        }
        return values.top();
    }

    std::vector<std::string> infixToPostfix(const std::vector<std::string> &tokens)
    {
        std::stack<char> ops;
        std::vector<std::string> postfix;
        for (const std::string &token : tokens)
        {
            if (std::isdigit(token[0]) || (!isOperator(token[0]) && token.size() > 1) || std::isalpha(token[0]))
            {
                postfix.push_back(token);
            }
            else if (token == "(")
            {
                ops.push('(');
            }
            else if (token == ")")
            {
                while (!ops.empty() && ops.top() != '(')
                {
                    postfix.push_back(std::string(1, ops.top()));
                    ops.pop();
                }
                if (!ops.empty())
                    ops.pop();
            }
            else if (isOperator(token[0]))
            {
                while (!ops.empty() && precedence(ops.top()) >= precedence(token[0]))
                {
                    postfix.push_back(std::string(1, ops.top()));
                    ops.pop();
                }
                ops.push(token[0]);
            }
        }
        while (!ops.empty())
        {
            postfix.push_back(std::string(1, ops.top()));
            ops.pop();
        }
        return postfix;
    }

public:
    void setVariable(const std::string &name, const std::string &value)
    {
        variables[name] = value;
    }

    std::string getVariable(const std::string &name)
    {
        return variables[name];
    }

    double evaluateExpression(const std::string &expression)
    {
        std::vector<std::string> tokens = tokenize(expression);
        std::vector<std::string> postfix = infixToPostfix(tokens);
        return evaluatePostfix(postfix);
    }

    bool isAssignment(const std::string &input)
    {
        return input.find('=') != std::string::npos;
    }

    void handleAssignment(const std::string &input)
    {
        std::istringstream iss(input);
        std::string variable, expression;
        if (std::getline(iss, variable, '='))
        {
            std::getline(iss, expression);
            variable.erase(std::remove_if(variable.begin(), variable.end(), ::isspace), variable.end());
            double result = evaluateExpression(expression);
            setVariable(variable, std::to_string(result));
            std::cout << variable << " = " << result << std::endl;
        }
    }
};

#endif // VARIABLES_H
