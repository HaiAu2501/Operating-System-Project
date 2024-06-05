// history.h
#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Lưu trữ lịch sử các câu lệnh đã nhập vào
class CommandHistory
{
private:
    std::vector<std::string> history;
    const std::string historyFile = "history.txt";

public:
    // Thêm câu lệnh vào lịch sử
    void add(const std::string &command)
    {
        history.push_back(command);
        // Ghi lịch sử vào file
        std::ofstream outFile(historyFile, std::ios::app);
        if (outFile.is_open())
        {
            outFile << command << std::endl;
            outFile.close();
        }
    }

    // Hiển thị lịch sử các câu lệnh
    void show() const
    {
        for (const std::string &cmd : history)
        {
            std::cout << cmd << std::endl;
        }
    }

    // Tải lịch sử từ file (nếu có)
    void load()
    {
        std::ifstream inFile(historyFile);
        if (inFile.is_open())
        {
            std::string line;
            while (std::getline(inFile, line))
            {
                history.push_back(line);
            }
            inFile.close();
        }
    }

    // Xóa lịch sử
    void clear()
    {
        history.clear();
        // Xóa nội dung của file
        std::ofstream outFile(historyFile, std::ios::trunc);
        if (outFile.is_open())
        {
            outFile.close();
        }
    }
};

#endif // HISTORY_H
