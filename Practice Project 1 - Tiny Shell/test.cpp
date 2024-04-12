#include <iostream>
#include <string>

int main()
{
    std::string command;
    while (true)
    {
        std::cout << "myshell> ";
        std::getline(std::cin, command);

        if (command == "exit")
        {
            break;
        }
        else if (command == "pwd")
        {
            system("cd");
        }
        else
        {
            system(command.c_str());
        }
    }
    return 0;
}
