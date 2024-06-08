#ifndef VARIABLES_H
#define VARIABLES_H

#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include "environment.h"

class VariableManager
{
public:
    EnvironmentManager &envManager;

    VariableManager(EnvironmentManager &envMgr) : envManager(envMgr) {}

    double evaluateExpression(const std::vector<std::string> &tokens)
    {
        std::vector<std::string> infixExpression;

        // Bước 1: Duyệt qua tokens và thay thế các biến bằng giá trị của chúng
        for (const std::string &token : tokens)
        {
            if (isOperator(token) || isParenthesis(token))
            {
                infixExpression.push_back(token);
            }
            else if (isNumber(token))
            {
                infixExpression.push_back(token);
            }
            else
            {
                // Token là toán hạng (biến)
                std::string value = envManager.getEnv(token);
                if (value.empty())
                {
                    throw std::runtime_error("Error: Variable " + token + " not set.");
                }
                infixExpression.push_back(value);
            }
        }

        // Bước 2: Chuyển biểu thức infix sang postfix
        std::vector<std::string> postfixExpression = infixToPostfix(infixExpression);

        // Bước 3: Tính giá trị biểu thức postfix
        return evaluatePostfix(postfixExpression);
    }

private:
    bool isOperator(const std::string &token)
    {
        return token == "+" || token == "-" || token == "*" || token == "/";
    }

    bool isParenthesis(const std::string &token)
    {
        return token == "(" || token == ")";
    }

    bool isNumber(const std::string &token)
    {
        return !token.empty() && std::all_of(token.begin(), token.end(), ::isdigit);
    }

    int getPrecedence(const std::string &op)
    {
        if (op == "+" || op == "-")
            return 1;
        if (op == "*" || op == "/")
            return 2;
        return 0;
    }

    std::vector<std::string> infixToPostfix(const std::vector<std::string> &infix)
    {
        std::vector<std::string> postfix;
        std::stack<std::string> stack;

        for (const std::string &token : infix)
        {
            if (isOperator(token))
            {
                while (!stack.empty() && getPrecedence(stack.top()) >= getPrecedence(token))
                {
                    postfix.push_back(stack.top());
                    stack.pop();
                }
                stack.push(token);
            }
            else if (token == "(")
            {
                stack.push(token);
            }
            else if (token == ")")
            {
                while (!stack.empty() && stack.top() != "(")
                {
                    postfix.push_back(stack.top());
                    stack.pop();
                }
                stack.pop(); // Pop '('
            }
            else
            {
                // Token là toán hạng
                postfix.push_back(token);
            }
        }

        while (!stack.empty())
        {
            postfix.push_back(stack.top());
            stack.pop();
        }

        return postfix;
    }

    double evaluatePostfix(const std::vector<std::string> &postfix)
    {
        std::stack<double> stack;

        for (const std::string &token : postfix)
        {
            if (isOperator(token))
            {
                double b = stack.top();
                stack.pop();
                double a = stack.top();
                stack.pop();

                if (token == "+")
                    stack.push(a + b);
                else if (token == "-")
                    stack.push(a - b);
                else if (token == "*")
                    stack.push(a * b);
                else if (token == "/")
                    stack.push(a / b);
            }
            else
            {
                stack.push(std::stod(token));
            }
        }

        return stack.top();
    }
};

#endif // VARIABLES_H
