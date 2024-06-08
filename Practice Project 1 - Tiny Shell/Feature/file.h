#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <csignal>
#include <conio.h>    // For _getch()
#include <filesystem> // For file size

namespace fs = std::filesystem;

class FileManager
{
public:
    FileManager()
    {
        // Đăng ký xử lý tín hiệu SIGINT (Ctrl+C)
        signal(SIGINT, signalHandler);
    }

    // Hàm để ghi nội dung vào file
    void writeFile(const std::vector<std::string> &args)
    {
        if (args.size() < 2)
        {
            std::cerr << "Usage: write_file <content> <filename>" << std::endl;
            return;
        }

        std::string content = args[0];
        std::string filename = args[1];

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

    // Hàm để đọc file và in ra 5 dòng mỗi lần
    void readFile(const std::string &fileName)
    {
        std::ifstream file(fileName);
        if (!file)
        {
            std::cerr << "Could not open file: " << fileName << std::endl;
            return;
        }

        std::string line;
        int lineCount = 0;

        interrupted = false; // Reset flag trước khi bắt đầu đọc file

        while (std::getline(file, line))
        {
            if (interrupted)
            {
                std::cout << "\nReading interrupted. Returning to shell..." << std::endl;
                interrupted = false; // Reset flag
                return;
            }

            std::cout << line << std::endl;
            lineCount++;

            if (lineCount % 5 == 0)
            {
                std::cout << "[READ MORE] (Press Enter to continue, Ctrl+C to quit)..." << std::endl;
                char ch = _getch();
                if (ch == 3)
                { // Ctrl+C
                    std::cout << "\nReading interrupted. Returning to shell..." << std::endl;
                    return;
                }
            }
        }

        file.close();
        std::cout << "End of file reached. Returning to shell..." << std::endl;
    }

    // Hàm để hiển thị kích thước file
    void showFileSize(const std::string &fileName)
    {
        try
        {
            auto fileSize = fs::file_size(fileName);
            std::cout << "Size of file " << fileName << ": " << fileSize << " bytes" << std::endl;
        }
        catch (const fs::filesystem_error &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

private:
    static bool interrupted;

    // Hàm xử lý tín hiệu SIGINT
    static void signalHandler(int signum)
    {
        interrupted = true;
    }
};

// Khởi tạo biến tĩnh
bool FileManager::interrupted = false;

#endif // FILE_H
