#ifndef FILE_H
#define FILE_H
#include <fstream>
#include <iostream>

void writeFile(const std::vector<std::string> &args)
{
    if (args.size() < 2)
    {
        std::cerr << "Usage: echo \"string\" \"filename\"" << std::endl;
        return;
    }

    std::string content = args[0];
    std::string filename = args[1];

    // Remove quotes from content and filename
    if (content.front() == '\"' && content.back() == '\"')
    {
        content = content.substr(1, content.size() - 2);
    }
    if (filename.front() == '\"' && filename.back() == '\"')
    {
        filename = filename.substr(1, filename.size() - 2);
    }

    std::ofstream file(filename, std::ios::app);
    if (!file)
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    file << content << std::endl;
    file.close();

    if (!file)
    {
        std::cerr << "Failed to write to file: " << filename << std::endl;
    }
    else
    {
        std::cout << "Successfully wrote to file: " << filename << std::endl;
    }
}
#endif