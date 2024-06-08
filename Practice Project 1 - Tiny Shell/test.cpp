#include <bits/stdc++.h>

std::vector<std::string> splitInput(const std::string &input)
{
    std::vector<std::string> tokens;
    std::string token;
    bool inQuotes = false;

    for (char ch : input)
    {
        if (ch == '\"')
        {
            inQuotes = !inQuotes;
            token += ch;
        }
        else if (isspace(ch) && !inQuotes)
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
        }
        else if ((ch == '(' || ch == ')' || ch == ',' || ch == '+' || ch == '-' || ch == '*' || ch == '/') && !inQuotes)
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(std::string(1, ch));
        }
        else
        {
            token += ch;
        }
    }

    if (!token.empty())
    {
        tokens.push_back(token);
    }

    return tokens;
}

int main()
{
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = splitInput(input);

    for (const std::string &token : tokens)
    {
        std::cout << token << std::endl;
    }

    return 0;
}