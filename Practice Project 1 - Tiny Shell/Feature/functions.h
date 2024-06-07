#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <algorithm>
#include "variables.h"

class FunctionManager
{
private:
    std::map<std::string, std::function<double(const std::vector<double> &)>> functions;

    std::vector<std::string> split(const std::string &s, char delimiter)
    {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter))
        {
            tokens.push_back(token);
        }
        return tokens;
    }

    std::function<double(const std::vector<double> &)> parseFunction(const std::string &parameters, const std::string &expression)
    {
        std::vector<std::string> paramList = split(parameters, ',');

        for (auto &param : paramList)
        {
            param.erase(std::remove_if(param.begin(), param.end(), ::isspace), param.end());
        }

        return [paramList, expression, this](const std::vector<double> &args) -> double
        {
            if (args.size() != paramList.size())
                throw std::runtime_error("Argument count mismatch.");

            VariableManager localVars;
            for (size_t i = 0; i < paramList.size(); ++i)
            {
                localVars.setVariable(paramList[i], std::to_string(args[i]));
            }
            return localVars.evaluateExpression(expression);
        };
    }

public:
    void defineFunction(const std::string &name, const std::string &parameters, const std::string &expression)
    {
        functions[name] = parseFunction(parameters, expression);
    }

    double evaluateFunction(const std::string &name, const std::vector<double> &args)
    {
        auto it = functions.find(name);
        if (it != functions.end())
        {
            return it->second(args);
        }
        throw std::runtime_error("Function not defined.");
    }

    bool isFunctionDefinition(const std::string &input)
    {
        return input.find("function") == 0;
    }

    void handleFunctionDefinition(const std::string &input)
    {
        size_t pos = input.find(' ');
        if (pos == std::string::npos)
            throw std::runtime_error("Invalid function definition syntax.");

        size_t pos2 = input.find('(', pos);
        if (pos2 == std::string::npos)
            throw std::runtime_error("Invalid function definition syntax.");

        std::string name = input.substr(pos + 1, pos2 - pos - 1);
        size_t pos3 = input.find(')', pos2);
        if (pos3 == std::string::npos)
            throw std::runtime_error("Invalid function definition syntax.");

        std::string parameters = input.substr(pos2 + 1, pos3 - pos2 - 1);
        size_t pos4 = input.find("return", pos3);
        if (pos4 == std::string::npos)
            throw std::runtime_error("Invalid function definition syntax.");

        std::string expression = input.substr(pos4 + 6);
        defineFunction(name, parameters, expression);

        // Thêm thông báo sau khi định nghĩa hàm
        std::vector<std::string> paramList = split(parameters, ',');
        std::cout << "Function " << name << " defined with " << paramList.size() << " parameters." << std::endl;
    }
};

#endif // FUNCTIONS_H
