#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <sstream>
#include "variables.h"

// Khai báo hàm splitInput
std::vector<std::string> splitInput(const std::string &input);

struct Function
{
    std::string name;
    std::vector<std::string> parameters;
    std::vector<std::string> expressionTokens;

    Function() {} // Constructor mặc định
    Function(const std::string &name, const std::vector<std::string> &parameters, const std::vector<std::string> &expressionTokens)
        : name(name), parameters(parameters), expressionTokens(expressionTokens) {}
};

class FunctionManager
{
public:
    void defineFunction(const std::vector<std::string> &args)
    {
        if (args.size() < 5) // function name ( param_list ) = expression
        {
            throw std::runtime_error("Usage: function <name>(<params>) = <expression>");
        }

        std::string functionName = args[0]; // "f"
        std::vector<std::string> parameters;
        std::unordered_set<std::string> uniqueParams;

        size_t i = 2; // Start after '('
        while (i < args.size() && args[i] != ")")
        {
            if (args[i] != ",")
            {
                if (uniqueParams.find(args[i]) != uniqueParams.end())
                {
                    throw std::runtime_error("Duplicate parameter: " + args[i]);
                }
                if (isInvalidParameter(args[i]))
                {
                    throw std::runtime_error("Invalid parameter: " + args[i]);
                }
                uniqueParams.insert(args[i]);
                parameters.push_back(args[i]);
            }
            ++i;
        }

        if (i == args.size() || args[i] != ")")
        {
            throw std::runtime_error("Invalid parameter list.");
        }

        ++i; // Move past ')'
        if (i == args.size() || args[i] != "=")
        {
            throw std::runtime_error("Syntax error: Expected '=' after parameter list.");
        }

        ++i; // Move past '='
        std::vector<std::string> expressionTokens(args.begin() + i, args.end());

        // Định nghĩa hàm
        functions[functionName] = Function(functionName, parameters, expressionTokens);

        // Nếu hàm không có tham số, thì thông báo lỗi
        if (parameters.empty())
        {
            throw std::runtime_error("Function " + functionName + " must have at least one parameter.");
        }

        // Hiển thị thông tin chi tiết về hàm đã được định nghĩa
        std::cout << "- Function defined!" << std::endl;
        std::cout << "- Name: " << functionName << std::endl;
        std::cout << "- Parameters (" << parameters.size() << "): ";
        for (const auto &param : parameters)
        {
            std::cout << param << " ";
        }
        std::cout << std::endl;
        std::cout << "- Expression: ";
        for (const auto &token : expressionTokens)
        {
            std::cout << token << " ";
        }
        std::cout << std::endl;
    }

    double evaluateFunction(const std::vector<std::string> &args, VariableManager &variableManager)
    {
        if (args.size() < 2)
        {
            throw std::runtime_error("Usage: evaluate <function_name> <args>");
        }

        std::string functionName = args[0];
        std::vector<std::string> functionArgs(args.begin() + 1, args.end());

        if (functions.find(functionName) == functions.end())
        {
            throw std::runtime_error("Function " + functionName + " not defined.");
        }

        Function function = functions[functionName];
        if (functionArgs.size() != function.parameters.size())
        {
            throw std::runtime_error("Incorrect number of arguments for function " + functionName);
        }

        // Thay thế tham số bằng giá trị tương ứng trong các token của biểu thức
        std::vector<std::string> evaluatedTokens = function.expressionTokens;
        for (size_t i = 0; i < functionArgs.size(); ++i)
        {
            for (auto &token : evaluatedTokens)
            {
                if (token == function.parameters[i])
                {
                    token = functionArgs[i];
                }
            }
        }

        // Kiểm tra và thay thế các biến không phải là tham số
        for (auto &token : evaluatedTokens)
        {
            if (!isOperator(token) && !isNumber(token) && !isParenthesis(token))
            {
                if (std::find(function.parameters.begin(), function.parameters.end(), token) == function.parameters.end())
                {
                    std::string value = variableManager.envManager.getEnv(token);
                    if (value.empty())
                    {
                        throw std::runtime_error("Error: Variable " + token + " not set.");
                    }
                    token = value;
                }
            }
        }

        // Đánh giá biểu thức
        return variableManager.evaluateExpression(evaluatedTokens);
    }

private:
    std::unordered_map<std::string, Function> functions;

    bool isOperator(const std::string &token)
    {
        return token == "+" || token == "-" || token == "*" || token == "/";
    }

    bool isNumber(const std::string &token)
    {
        return !token.empty() && std::all_of(token.begin(), token.end(), ::isdigit);
    }

    bool isParenthesis(const std::string &token)
    {
        return token == "(" || token == ")";
    }

    bool isInvalidParameter(const std::string &token)
    {
        return isNumber(token) || isParenthesis(token) || isOperator(token);
    }
};

#endif // FUNCTION_H
