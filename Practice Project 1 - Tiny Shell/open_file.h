#ifndef OPEN_FILE_H
#define OPEN_FILE_H

#include <iostream>
#include <windows.h>
#include <vector>

void openFile(const std::vector<std::string> &args)
{
    if (args.size() != 1)
    {
        std::cout << "Usage: open <file_path>" << std::endl;
        return;
    }
    std::string filePath = args[0];
    ShellExecuteA(NULL, "open", filePath.c_str(), NULL, NULL, SW_SHOW);
}

#endif // OPEN_FILE_H
