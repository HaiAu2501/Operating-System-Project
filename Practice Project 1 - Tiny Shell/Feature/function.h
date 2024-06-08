#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <sstream>
#include "variables.h"

// Khai báo hàm splitInput
std::vector<std::string> splitInput(const std::string &input);

struct Function
{
    std::string name;
    std::vector<std::string> parameters;
    std::string expression;

    Function() {} // Constructor mặc định
    Function(const std::string &name, const std::vector<std::string> &parameters, const std::string &expression)
        : name(name), parameters(parameters), expression(expression) {}
};

class FunctionManager
{
public:
    void defineFunction(const std::vector<std::string> &args)
    {
        if (args.size() < 5) // function_name ( param_list ) "expression"
        {
            throw std::runtime_error("Usage: function <name>(<params>) \"<expression>\"");
        }

        std::string functionName = args[0]; // "f"
        std::vector<std::string> parameters;

        size_t i = 2; // Start after '('
        while (i < args.size() && args[i] != ")")
        {
            if (args[i] != ",")
            {
                parameters.push_back(args[i]);
            }
            ++i;
        }

        if (i == args.size() || args[i] != ")")
        {
            throw std::runtime_error("Invalid parameter list.");
        }

        // Expression should be the last token
        std::string expression = args.back();                       // "\"x*x\""
        expression = expression.substr(1, expression.length() - 2); // Remove the quotes

        // Định nghĩa hàm
        functions[functionName] = Function(functionName, parameters, expression);

        // Hiển thị thông tin chi tiết về hàm đã được định nghĩa
        std::cout << "Function defined:" << std::endl;
        std::cout << "Name: " << functionName << std::endl;
        std::cout << "Parameters (" << parameters.size() << "): ";
        for (const auto &param : parameters)
        {
            std::cout << param << " ";
        }
        std::cout << std::endl;
        std::cout << "Expression: " << expression << std::endl;
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

        // Thay thế tham số bằng giá trị tương ứng
        std::string evaluatedExpression = function.expression;
        for (size_t i = 0; i < functionArgs.size(); ++i)
        {
            size_t pos = 0;
            while ((pos = evaluatedExpression.find(function.parameters[i], pos)) != std::string::npos)
            {
                evaluatedExpression.replace(pos, function.parameters[i].length(), functionArgs[i]);
                pos += functionArgs[i].length();
            }
        }

        // Tokenize và đánh giá biểu thức
        std::vector<std::string> tokens = splitInput(evaluatedExpression);
        return variableManager.evaluateExpression(tokens);
    }

private:
    std::unordered_map<std::string, Function> functions;
};

#endif // FUNCTION_H
