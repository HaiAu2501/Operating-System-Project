#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "variables.h"

// Khai báo hàm executeCommand từ main
void executeCommand(const std::string &command, const std::vector<std::string> &args);

std::vector<std::string> splitInput(const std::string &input);

bool evaluateCondition(const std::string &condition, VariableManager &variableManager)
{
    // Loại bỏ mọi dấu cách trong biểu thức điều kiện
    std::string cleanCondition;
    for (char c : condition)
    {
        if (!isspace(c))
        {
            cleanCondition += c;
        }
    }

    // Tìm toán tử trong biểu thức điều kiện
    size_t opPos = cleanCondition.find_first_of("<>!=");
    if (opPos == std::string::npos)
    {
        throw std::runtime_error("Invalid condition: No operator found.");
    }

    // Lấy toán hạng trước và sau toán tử
    std::string leftOperand = cleanCondition.substr(0, opPos);
    std::string op;
    size_t nextPos = opPos + 1;
    if (cleanCondition[opPos] == '!' || cleanCondition[opPos] == '=')
    {
        op = cleanCondition.substr(opPos, 2);
        nextPos = opPos + 2;
    }
    else
    {
        op = cleanCondition.substr(opPos, 1);
    }
    std::string rightOperand = cleanCondition.substr(nextPos);

    // Đánh giá giá trị các toán hạng
    double leftValue = variableManager.evaluateExpression(leftOperand);
    double rightValue = variableManager.evaluateExpression(rightOperand);

    // Đánh giá biểu thức điều kiện
    if (op == "<")
    {
        return leftValue < rightValue;
    }
    else if (op == ">")
    {
        return leftValue > rightValue;
    }
    else if (op == "<=")
    {
        return leftValue <= rightValue;
    }
    else if (op == ">=")
    {
        return leftValue >= rightValue;
    }
    else if (op == "==")
    {
        return leftValue == rightValue;
    }
    else if (op == "!=")
    {
        return leftValue != rightValue;
    }
    else
    {
        throw std::runtime_error("Invalid operator in condition.");
    }
}

void executeConditional(const std::string &args, VariableManager &variableManager)
{
    size_t colonPos = args.find(":");
    size_t elsePos = args.find("else");
    if (colonPos == std::string::npos || elsePos == std::string::npos)
    {
        throw std::runtime_error("Invalid if-else statement.");
    }

    // Lấy biểu thức điều kiện giữa "(" và ")"
    size_t conditionStart = args.find("(") + 1;
    size_t conditionEnd = args.find(")");
    if (conditionStart == std::string::npos || conditionEnd == std::string::npos || conditionEnd <= conditionStart)
    {
        throw std::runtime_error("Invalid if-else statement: Invalid condition.");
    }
    std::string condition = args.substr(conditionStart, conditionEnd - conditionStart);

    // Lấy lệnh trong vế if
    size_t ifCommandStart = colonPos + 1;
    size_t ifCommandEnd = elsePos;
    std::string ifCommand = args.substr(ifCommandStart, ifCommandEnd - ifCommandStart);
    ifCommand = ifCommand.substr(ifCommand.find_first_not_of(" "), ifCommand.find_last_not_of(" ") - ifCommand.find_first_not_of(" ") + 1);

    // Lấy lệnh trong vế else
    size_t elseCommandStart = elsePos + 4;
    std::string elseCommand = args.substr(elseCommandStart);
    elseCommand = elseCommand.substr(elseCommand.find_first_not_of(" "), elseCommand.find_last_not_of(" ") - elseCommand.find_first_not_of(" ") + 1);

    // Tách command và args cho vế if
    std::vector<std::string> ifTokens = splitInput(ifCommand);
    if (ifTokens.empty())
    {
        throw std::runtime_error("Invalid if command.");
    }
    std::string ifCmd = ifTokens[0];
    ifTokens.erase(ifTokens.begin());

    for (const auto &token : ifTokens)
    {
        std::cout << token << " ";
    }
    std::cout << std::endl;

    // Tách command và args cho vế else
    std::vector<std::string> elseTokens = splitInput(elseCommand);
    if (elseTokens.empty())
    {
        throw std::runtime_error("Invalid else command.");
    }
    std::string elseCmd = elseTokens[0];
    elseTokens.erase(elseTokens.begin());

    for (const auto &token : elseTokens)
    {
        std::cout << token << " ";
    }
    std::cout << std::endl;

    // Thực thi lệnh dựa trên kết quả của biểu thức điều kiện
    if (evaluateCondition(condition, variableManager))
    {
        std::cout << "Executing if command: " << ifCmd << std::endl;
        executeCommand(ifCmd, ifTokens);
    }
    else
    {
        std::cout << "Executing else command: " << elseCmd << std::endl;
        executeCommand(elseCmd, elseTokens);
    }
}

#endif // CONDITIONAL_H
