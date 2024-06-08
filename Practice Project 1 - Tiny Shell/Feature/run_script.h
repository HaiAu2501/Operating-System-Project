#ifndef RUN_SCRIPT_H
#define RUN_SCRIPT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstdlib> // For std::getenv

void executeCommand(const std::string &command, const std::vector<std::string> &args);

std::vector<std::string> splitInput(const std::string &input);

std::string resolvePath(const std::string &path)
{
    // Check if the path is absolute
    if (std::filesystem::path(path).is_absolute())
    {
        return path;
    }

    // Check if the file exists in the current directory
    if (std::filesystem::exists(path))
    {
        return std::filesystem::absolute(path).string();
    }

    // Check in PATH environment variable
    const char *pathEnv = std::getenv("PATH");
    if (pathEnv)
    {
        std::vector<std::string> paths;
        std::string pathEnvStr(pathEnv);
        std::string delimiter = ";"; // Use ';' as the delimiter for Windows PATH

        size_t pos = 0;
        std::string token;
        while ((pos = pathEnvStr.find(delimiter)) != std::string::npos)
        {
            token = pathEnvStr.substr(0, pos);
            paths.push_back(token);
            pathEnvStr.erase(0, pos + delimiter.length());
        }
        paths.push_back(pathEnvStr);

        for (const auto &p : paths)
        {
            std::filesystem::path filePath = std::filesystem::path(p) / path;
            if (std::filesystem::exists(filePath))
            {
                return std::filesystem::absolute(filePath).string();
            }
        }
    }

    // Return the original path if no resolution found
    return path;
}

void runScript(const std::vector<std::string> &args)
{
    if (args.size() != 1)
    {
        std::cout << "Usage: run <script_file_path>" << std::endl;
        return;
    }

    std::string scriptPath = resolvePath(args[0]);
    std::ifstream scriptFile(scriptPath);
    if (!scriptFile)
    {
        std::cout << "Unable to open script file: " << scriptPath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(scriptFile, line))
    {
        std::vector<std::string> tokens = splitInput(line);
        if (!tokens.empty())
        {
            std::string command = tokens[0];
            tokens.erase(tokens.begin());
            executeCommand(command, tokens);
        }
    }
    scriptFile.close();
}

#endif // RUN_SCRIPT_H
