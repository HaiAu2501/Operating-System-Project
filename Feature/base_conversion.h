#ifndef BASE_CONVERSION_H
#define BASE_CONVERSION_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cctype>

// Hàm kiểm tra tính hợp lệ của số theo hệ cơ số
bool isValidNumberForBase(const std::string &number, int base)
{
    for (char digit : number)
    {
        if (std::isdigit(digit))
        {
            if (digit - '0' >= base)
            {
                return false;
            }
        }
        else
        {
            if (std::toupper(digit) - 'A' + 10 >= base)
            {
                return false;
            }
        }
    }
    return true;
}

// Hàm chuyển đổi số từ hệ cơ số này sang hệ cơ số khác
std::string convertBase(const std::string &number, int fromBase, int toBase)
{
    // Kiểm tra tính hợp lệ của số theo hệ cơ số ban đầu
    if (!isValidNumberForBase(number, fromBase))
    {
        throw std::runtime_error("Invalid number for the given base: " + number + " for base " + std::to_string(fromBase));
    }

    // Hàm trợ giúp chuyển đổi số từ bất kỳ hệ cơ số nào sang hệ cơ số 10
    auto toDecimal = [](const std::string &num, int base) -> long long
    {
        long long value = 0;
        for (char digit : num)
        {
            if (std::isdigit(digit))
                value = value * base + (digit - '0');
            else
                value = value * base + (std::toupper(digit) - 'A' + 10);
        }
        return value;
    };

    // Hàm trợ giúp chuyển đổi số từ hệ cơ số 10 sang bất kỳ hệ cơ số nào khác
    auto fromDecimal = [](long long num, int base) -> std::string
    {
        std::string result;
        const char digits[] = "0123456789ABCDEF";
        while (num > 0)
        {
            result += digits[num % base];
            num /= base;
        }
        std::reverse(result.begin(), result.end());
        return result.empty() ? "0" : result;
    };

    long long decimalValue = toDecimal(number, fromBase);
    return fromDecimal(decimalValue, toBase);
}

// Hàm xử lý lệnh chuyển đổi hệ cơ số
void handleBaseConversion(const std::vector<std::string> &args)
{
    if (args.size() != 5 || args[1] != "from" || args[3] != "to")
    {
        std::cerr << "Usage: convert <number> from <from_base> to <to_base>" << std::endl;
        return;
    }

    std::string number = args[0];
    int fromBase = std::stoi(args[2]);
    int toBase = std::stoi(args[4]);

    if (fromBase < 2 || fromBase > 36 || toBase < 2 || toBase > 36)
    {
        std::cerr << "Base must be between 2 and 36." << std::endl;
        return;
    }

    try
    {
        std::string result = convertBase(number, fromBase, toBase);
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

#endif // BASE_CONVERSION_H
