#ifndef ALIAS_H
#define ALIAS_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

class AliasManager
{
public:
    AliasManager()
    {
        validCommands = {
            "delete"};
    }

    // Hàm để thêm alias
    void addAlias(const std::string &name, const std::string &command)
    {
        if (validCommands.find(command) == validCommands.end())
        {
            std::cerr << "Error: Command '" << command << "' is not supported." << std::endl;
            return;
        }

        if (validCommands.find(name) != validCommands.end())
        {
            std::cerr << "Error: Alias name '" << name << "' conflicts with an existing command." << std::endl;
            return;
        }

        aliases[name] = command;
        std::cout << "Alias added: " << name << " -> " << command << std::endl;
    }

    // Hàm để xóa alias
    void removeAlias(const std::string &name)
    {
        if (aliases.erase(name))
        {
            std::cout << "Alias removed: " << name << std::endl;
        }
        else
        {
            std::cerr << "Alias not found: " << name << std::endl;
        }
    }

    // Hàm để hiển thị tất cả các alias
    void listAliases() const
    {
        for (const auto &alias : aliases)
        {
            std::cout << alias.first << " -> " << alias.second << std::endl;
        }
    }

    // Hàm để tìm và thay thế alias trong lệnh
    std::string resolveAlias(const std::string &command) const
    {
        auto it = aliases.find(command);
        if (it != aliases.end())
        {
            return it->second;
        }
        return command;
    }

private:
    std::unordered_map<std::string, std::string> aliases;
    std::unordered_set<std::string> validCommands;
};

#endif // ALIAS_H
