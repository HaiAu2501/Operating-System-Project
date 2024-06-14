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
        // Danh sách các lệnh hỗ trợ
        validCommands = {
            "delete",
            "move",
            "list_tree",
            "create",
            "copy",
            "open",
            "rename",
            "start_foreground",
            "start_background",
            "terminate",
            "list_processes",
            "child",
            "manage_threads",
            "list_children",
            "suspend",
            "resume",
            "after",
            "run",
            "calculator",
            "time",
            "date",
            "uptime",
            "cpuinfo",
            "meminfo",
            "diskinfo",
            "change_color",
            "calculate",
            "function",
            "evaluate",
            "if else",
            "loop",
            "convert",
            "alias",
            "unalias",
            "bookmark",
            "add_path",
            "remove_path",
            "print_env",
            "set_env",
            "unset_env",
            "is_in_path",
            "list_env",
            "save_env",
            "load_env",
            "write_file",
            "read_file",
            "file_size",
            "dancing",
            "tictactoe",
            "duck",
            "cd",
            "dir",
            "pwd",
            "exit",
            "help",
            "history",
            "clear",
            "clear_history"};
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
