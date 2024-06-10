#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <csignal>
#include <conio.h>
#include <filesystem>

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
            std::cerr << "Usage: write_file <content> <filename> [~HEAD | ~FOOT | ~LINE N]" << std::endl;
            return;
        }

        std::string content = args[0];
        std::string filename = args[1];

        if (args.size() == 2)
        {
            // Mặc định ghi vào cuối file
            std::ofstream file(filename, std::ios::app);
            if (!file)
            {
                std::cerr << "Failed to open file: " << filename << std::endl;
                return;
            }

            file << content << std::endl;
            file.close();
        }
        else if (args.size() == 3 || (args.size() == 4 && args[2] == "~LINE"))
        {
            std::string position = args[2];
            std::ifstream file_in(filename);
            if (!file_in)
            {
                std::cerr << "Failed to open file: " << filename << std::endl;
                return;
            }

            std::vector<std::string> lines;
            std::string line;
            while (std::getline(file_in, line))
            {
                lines.push_back(line);
            }
            file_in.close();

            if (position == "~HEAD")
            {
                lines.insert(lines.begin(), content);
            }
            else if (position == "~FOOT")
            {
                lines.push_back(content);
            }
            else if (position == "~LINE")
            {
                if (args.size() != 4)
                {
                    std::cerr << "Usage: write_file <content> <filename> ~LINE N" << std::endl;
                    return;
                }
                size_t line_number = std::stoi(args[3]) - 1;
                if (line_number < lines.size())
                {
                    lines.insert(lines.begin() + line_number, content);
                }
                else
                {
                    lines.push_back(content);
                }
            }

            std::ofstream file_out(filename);
            if (!file_out)
            {
                std::cerr << "Failed to open file for writing: " << filename << std::endl;
                return;
            }

            for (const auto &l : lines)
            {
                file_out << l << std::endl;
            }
            file_out.close();
        }
        else
        {
            std::cerr << "Invalid number of arguments." << std::endl;
        }

        std::cout << "Successfully wrote to file: " << filename << std::endl;
    }

    // Hàm để đọc file
    void readFile(const std::vector<std::string> &args)
    {
        if (args.size() < 1 || args.size() > 4)
        {
            std::cerr << "Usage: read_file <filename> [~HEAD N | ~FOOT N | ~RANGE M N | ~LINE N]" << std::endl;
            return;
        }

        std::string filename = args[0];
        std::ifstream file(filename);
        if (!file)
        {
            std::cerr << "Could not open file: " << filename << std::endl;
            return;
        }

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();

        if (args.size() == 1)
        {
            // Mặc định đọc toàn bộ file, 5 dòng một lần và hỏi người dùng ấn Enter để tiếp tục hoặc Ctrl+C để thoát
            printLinesWithPause(lines, 0, lines.size());
        }
        else
        {
            std::string position = args[1];
            if (position == "~HEAD")
            {
                if (args.size() != 3)
                {
                    std::cerr << "Usage: read_file <filename> ~HEAD N" << std::endl;
                    return;
                }
                size_t num_lines = std::stoi(args[2]);
                printLines(lines, 0, std::min(num_lines, lines.size()));
            }
            else if (position == "~FOOT")
            {
                if (args.size() != 3)
                {
                    std::cerr << "Usage: read_file <filename> ~FOOT N" << std::endl;
                    return;
                }
                size_t num_lines = std::stoi(args[2]);
                printLines(lines, std::max(lines.size() - num_lines, (size_t)0), lines.size());
            }
            else if (position == "~RANGE")
            {
                if (args.size() != 4)
                {
                    std::cerr << "Usage: read_file <filename> ~RANGE M N" << std::endl;
                    return;
                }
                size_t start_line = std::stoi(args[2]) - 1;
                size_t end_line = std::stoi(args[3]) - 1;
                if (start_line <= end_line && end_line < lines.size())
                {
                    printLines(lines, start_line, end_line + 1);
                }
                else
                {
                    std::cerr << "Invalid line range." << std::endl;
                }
            }
            else if (position == "~LINE")
            {
                if (args.size() != 3)
                {
                    std::cerr << "Usage: read_file <filename> ~LINE N" << std::endl;
                    return;
                }
                size_t line_number = std::stoi(args[2]) - 1;
                if (line_number < lines.size())
                {
                    printLines(lines, line_number, line_number + 1);
                }
                else
                {
                    std::cerr << "Line number out of range." << std::endl;
                }
            }
            else
            {
                std::cerr << "Invalid position format." << std::endl;
            }
        }
    }

    // Hàm để hiển thị kích thước file và số lượng dòng
    void showFileSize(const std::string &fileName)
    {
        try
        {
            auto fileSize = fs::file_size(fileName);
            std::ifstream file(fileName);
            size_t lineCount = 0;
            std::string line;
            while (std::getline(file, line))
            {
                lineCount++;
            }
            std::cout << "Size of file " << fileName << ": " << fileSize << " bytes" << std::endl;
            std::cout << "Number of lines in file " << fileName << ": " << lineCount << std::endl;
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

    // Hàm để in các dòng từ start đến end-1
    void printLines(const std::vector<std::string> &lines, size_t start, size_t end)
    {
        for (size_t i = start; i < end; ++i)
        {
            std::cout << lines[i] << std::endl;
        }
        std::cout << "End of reading. Returning to shell..." << std::endl;
    }

    // Hàm để in các dòng từ start đến end-1 với tạm dừng
    void printLinesWithPause(const std::vector<std::string> &lines, size_t start, size_t end)
    {
        for (size_t i = start; i < end; ++i)
        {
            std::cout << lines[i] << std::endl;
            if (interrupted)
            {
                std::cout << "\nReading interrupted. Returning to shell..." << std::endl;
                interrupted = false; // Reset flag
                return;
            }

            if ((i + 1) % 5 == 0 && i + 1 < end)
            {
                std::cout << "[READ MORE] (Press any key to continue, Ctrl+C to quit)..." << std::endl;
                char ch = _getch();
                if (ch == 3)
                { // Ctrl+C
                    std::cout << "\nReading interrupted. Returning to shell..." << std::endl;
                    return;
                }
            }
        }
        std::cout << "End of reading. Returning to shell..." << std::endl;
    }
};

// Khởi tạo biến tĩnh
bool FileManager::interrupted = false;

#endif // FILE_H
