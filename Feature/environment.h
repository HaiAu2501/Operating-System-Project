#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <unordered_set>

class EnvironmentManager
{
public:
    // Các lệnh hỗ trợ
    static const std::unordered_set<std::string> supportedCommands;

    // Hàm lấy danh sách các lệnh hỗ trợ
    static const std::unordered_set<std::string> &getSupportedCommands()
    {
        return supportedCommands;
    }

    // Hàm để thêm đường dẫn vào biến môi trường PATH
    void addToPath(const std::string &path)
    {
        std::string currentPath = getEnv("PATH");
        if (currentPath.find(path) == std::string::npos)
        {
            std::string newPath = currentPath + ";" + path;
            setEnv("PATH", newPath);
            std::cout << "Added " << path << " to PATH." << std::endl;
        }
        else
        {
            std::cout << path << " is already in PATH." << std::endl;
        }
    }

    // Hàm để xóa đường dẫn khỏi biến môi trường PATH
    void removeFromPath(const std::string &path)
    {
        std::string currentPath = getEnv("PATH");
        size_t pos = currentPath.find(path);
        if (pos != std::string::npos)
        {
            std::string newPath;
            if (pos > 0 && currentPath[pos - 1] == ';')
            {
                newPath = currentPath.substr(0, pos - 1) + currentPath.substr(pos + path.length());
            }
            else if (pos + path.length() < currentPath.length() && currentPath[pos + path.length()] == ';')
            {
                newPath = currentPath.substr(0, pos) + currentPath.substr(pos + path.length() + 1);
            }
            else
            {
                newPath = currentPath.substr(0, pos) + currentPath.substr(pos + path.length());
            }
            setEnv("PATH", newPath);
            std::cout << "Removed " << path << " from PATH." << std::endl;
        }
        else
        {
            std::cout << path << " is not in PATH." << std::endl;
        }
    }

    // Hàm để in ra giá trị của biến môi trường
    void printEnv(const std::string &var)
    {
        std::string value = getEnv(var);
        if (!value.empty())
        {
            std::cout << var << " = " << value << std::endl;
        }
        else
        {
            std::cout << var << " is not set." << std::endl;
        }
    }

    // Hàm để thiết lập giá trị của biến môi trường
    void setEnv(const std::string &var, const std::string &value)
    {
        // Kiểm tra xem value có phải là một biến môi trường khác hay không
        std::string actualValue = getEnv(value);
        if (!actualValue.empty())
        {
            _putenv_s(var.c_str(), actualValue.c_str());
        }
        else
        {
            _putenv_s(var.c_str(), value.c_str());
        }
    }

    // Hàm để xóa biến môi trường
    void unsetEnv(const std::string &var)
    {
        _putenv_s(var.c_str(), "");
        std::cout << "Unset variable " << var << std::endl;
    }

    // Hàm để kiểm tra xem một đường dẫn có trong PATH hay không
    bool isInPath(const std::string &path)
    {
        std::string currentPath = getEnv("PATH");
        return currentPath.find(path) != std::string::npos;
    }

    // Hàm để liệt kê tất cả các biến môi trường
    void listAllEnv()
    {
        extern char **environ;
        for (char **env = environ; *env; ++env)
        {
            std::cout << *env << std::endl;
        }
    }

    // Hàm để lưu biến môi trường vào file
    void saveEnvToFile(const std::string &filename)
    {
        std::ofstream file(filename);
        if (!file)
        {
            std::cerr << "Could not open file for writing: " << filename << std::endl;
            return;
        }
        extern char **environ;
        for (char **env = environ; *env; ++env)
        {
            file << *env << std::endl;
        }
        file.close();
        std::cout << "Environment variables saved to " << filename << std::endl;
    }

    // Hàm để tải biến môi trường từ file
    void loadEnvFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file)
        {
            std::cerr << "Could not open file for reading: " << filename << std::endl;
            return;
        }
        std::string line;
        while (std::getline(file, line))
        {
            size_t pos = line.find('=');
            if (pos != std::string::npos)
            {
                std::string var = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                setEnv(var, value);
            }
        }
        file.close();
        std::cout << "Environment variables loaded from " << filename << std::endl;
    }

    // Hàm để lấy giá trị của biến môi trường
    std::string getEnv(const std::string &var)
    {
        const char *value = getenv(var.c_str());
        if (value)
        {
            return std::string(value);
        }
        return "";
    }
};

const std::unordered_set<std::string> EnvironmentManager::supportedCommands = {
    "add_path",
    "remove_path",
    "print_env",
    "set_env",
    "unset_env",
    "is_in_path",
    "list_env",
    "save_env",
    "load_env"};

#endif // ENVIRONMENT_H
