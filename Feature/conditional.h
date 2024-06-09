#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include <string>
#include <vector>
#include <stdexcept>
#include "variables.h"

// Hàm này sẽ kiểm tra điều kiện và thực thi các lệnh tương ứng với kết quả của điều kiện
void handleIfElse(const std::vector<std::string> &args, VariableManager &variableManager)
{
    if (args.empty() || args[0] != "(")
    {
        throw std::runtime_error("Syntax error: Expected '(' after 'if'");
    }

    // Xác định các phần của câu lệnh if-else
    std::vector<std::string> leftExpression;
    std::vector<std::string> rightExpression;
    std::string op;
    std::vector<std::string> ifCommand;
    std::vector<std::string> elseCommand;

    size_t i = 1;
    while (i < args.size() && args[i] != "!" && args[i] != "<" && args[i] != ">" && args[i] != "=" && args[i] != "==" && args[i] != "!=" && args[i] != "<=" && args[i] != ">=")
    {
        leftExpression.push_back(args[i]);
        ++i;
    }

    if (i == args.size())
    {
        throw std::runtime_error("Syntax error: Expected comparison operator in if condition");
    }

    op = args[i];
    if (op == "<" || op == ">")
    {
        if (i + 1 < args.size() && args[i + 1] == "=")
        {
            op += "=";
            ++i;
        }
    }
    else if (op == "=")
    {
        if (i + 1 < args.size() && args[i + 1] == "=")
        {
            op += "=";
            ++i;
        }
        else
        {
            throw std::runtime_error("Syntax error: Expected '=' after '='");
        }
    }

    ++i;

    while (i < args.size() && args[i] != ")")
    {
        rightExpression.push_back(args[i]);
        ++i;
    }

    if (i == args.size() || args[i] != ")")
    {
        throw std::runtime_error("Syntax error: Expected ')' in if condition");
    }

    ++i;

    if (i == args.size() || args[i] != ":")
    {
        throw std::runtime_error("Syntax error: Expected ':' after if condition");
    }

    ++i;

    while (i < args.size() && args[i] != "else")
    {
        ifCommand.push_back(args[i]);
        ++i;
    }

    if (i < args.size() && args[i] == "else")
    {
        ++i;
        while (i < args.size())
        {
            elseCommand.push_back(args[i]);
            ++i;
        }
    }

    // Tính giá trị của biểu thức điều kiện
    double leftValue = variableManager.evaluateExpression(leftExpression);
    double rightValue = variableManager.evaluateExpression(rightExpression);

    bool conditionResult = false;
    if (op == "==")
    {
        conditionResult = (leftValue == rightValue);
    }
    else if (op == "!=")
    {
        conditionResult = (leftValue != rightValue);
    }
    else if (op == "<")
    {
        conditionResult = (leftValue < rightValue);
    }
    else if (op == "<=")
    {
        conditionResult = (leftValue <= rightValue);
    }
    else if (op == ">")
    {
        conditionResult = (leftValue > rightValue);
    }
    else if (op == ">=")
    {
        conditionResult = (leftValue >= rightValue);
    }

    if (conditionResult)
    {
        if (!ifCommand.empty())
        {
            std::string ifCommandStr = ifCommand[0];
            ifCommand.erase(ifCommand.begin());
            executeCommand(ifCommandStr, ifCommand);
        }
    }
    else
    {
        if (!elseCommand.empty())
        {
            std::string elseCommandStr = elseCommand[0];
            elseCommand.erase(elseCommand.begin());
            executeCommand(elseCommandStr, elseCommand);
        }
    }
}

#endif // CONDITIONAL_H
