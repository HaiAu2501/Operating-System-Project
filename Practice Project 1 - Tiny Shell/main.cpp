#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <csignal>
#include <windows.h>
#include <thread>
#include "Feature/features.h"

// Tạo đối tượng lưu trữ lịch sử các câu lệnh
CommandHistory commandHistory;

// Tạo đối tượng để quản lý hàm
FunctionManager functionManager;

// Tạo đối tượng quản lý biến môi trường
EnvironmentManager environmentManager;

// Tạo đối tượng quản lý biến
VariableManager variableManager(environmentManager);

// Tạo đối tượng để quản lý file
FileManager fileManager;

// Hàm in ra các thông tin ban đầu khi shell khởi động
void printInitialInfo()
{
    // Lấy PID của chính tiến trình hiện tại (main.exe)
    DWORD pid = GetCurrentProcessId();

    // In ra các thông tin ban đầu
    std::cout << "========================================" << std::endl;
    std::cout << "              Tiny Shell                " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Welcome to Tiny Shell!" << std::endl;
    std::cout << "This is a simple shell program to interact with the Windows operating system." << std::endl;
    std::cout << "PID of Tiny Shell: " << pid << std::endl;
    std::cout << "Type 'help' to see the list of available commands." << std::endl;
    std::cout << "========================================" << std::endl;
}

ConsoleColor currentColor = ConsoleColor::WHITE;

void executeCommand(const std::string &command, const std::vector<std::string> &args)
{
    if (command == "change_color")
    {
        if (!args.empty())
        {
            currentColor = parseColor(args[0]);
            setColor(currentColor);
            std::cout << "Color changed to " << args[0] << std::endl;
        }
        else
        {
            std::cout << "Usage: change_color <color_name>" << std::endl;
        }
        return; // Ensure the color change command exits the function
    }
    if (command == "delete")
    {
        deleteDirectory(args);
    }
    else if (command == "move")
    {
        moveDirectory(args);
    }
    else if (command == "open")
    {
        openFile(args);
    }
    else if (command == "exit")
    {
        exitShell();
        PostQuitMessage(0); // Exit the program
    }
    else if (command == "list_tree")
    {
        listDirectoryTree(args);
    }
    else if (command == "create")
    {
        createDirectory(args);
    }
    else if (command == "copy")
    {
        copyDirectory(args);
    }
    else if (command == "run")
    {
        runScript(args);
    }
    else if (command == "help")
    {
        showHelp(args);
    }
    else if (command == "rename")
    {
        renameFile(args);
    }
    else if (command == "cd")
    {
        changeDirectory(args);
    }
    else if (command == "dir")
    {
        listDirectoryContents(args);
    }
    else if (command == "pwd")
    {
        printWorkingDirectory(args);
    }
    else if (command == "start")
    {
        startProcess(args);
    }
    else if (command == "start_foreground")
    {
        handleStartForegroundCommand(args);
    }
    else if (command == "start_background")
    {
        handleStartBackgroundCommand(args);
    }
    else if (command == "terminate")
    {
        terminateProcess(args);
    }
    else if (command == "list_processes")
    {
        listProcesses(args);
    }
    else if (command == "list_children")
    {
        printAllChildProcesses(args);
    }
    else if (command == "start_child")
    {
        startChildProcess();
    }
    else if (command == "start_countdown")
    {
        startCountdownProcess();
    }
    else if (command == "manage_threads")
    {
        handleManageThreadsCommand(args);
    }
    else if (command == "time")
    {
        showSystemTime(args);
    }
    else if (command == "date")
    {
        showSystemDate(args);
    }
    else if (command == "uptime")
    {
        showSystemUptime(args);
    }
    else if (command == "cpuinfo")
    {
        showCPUInfo(args);
    }
    else if (command == "meminfo")
    {
        showMemoryInfo(args);
    }
    else if (command == "diskinfo")
    {
        showDiskInfo(args);
    }
    else if (command == "calculator")
    {
        showCalculator(args);
    }
    else if (command == "history")
    {
        commandHistory.show();
    }
    else if (command == "clear_history")
    {
        commandHistory.clear();
    }
    else if (command == "clear")
    {
        clearScreen();
    }
    else if (command == "calculate")
    {
        // Nếu có tham số truyền vào thì thực hiện tính toán
        if (!args.empty())
        {
            // Gọi hàm evaluateExpression từ biến variableManager để tính toán biểu thức
            try
            {
                double result = variableManager.evaluateExpression(args);
                std::cout << result << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        else
        {
            std::cout << "Usage: calculate <expression>" << std::endl;
        }
    }
    else if (command == "dancing")
    {
        dancing();
    }
    else if (command == "playing")
    {
        startTicTacToe();
    }
    else if (command == "duck")
    {
        startDuck();
    }
    else if (command == "function")
    {
        try
        {
            functionManager.defineFunction(args);
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    else if (command == "evaluate")
    {
        try
        {
            double result = functionManager.evaluateFunction(args, variableManager);
            std::cout << result << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    else if (command == "if")
    {
        if (args.size() < 1)
        {
            std::cout << "Usage: if (<condition>): <command> else <command>" << std::endl;
        }
        else
        {
            handleIfElse(args, variableManager);
        }
    }
    // else if (command == "function")
    // {
    //     std::string functionDefinition = "function ";
    //     for (const std::string &arg : args)
    //     {
    //         functionDefinition += arg + " ";
    //     }
    //     try
    //     {
    //         functionManager.handleFunctionDefinition(functionDefinition);
    //     }
    //     catch (const std::exception &e)
    //     {
    //         std::cout << "Error: " << e.what() << std::endl;
    //     }
    // }
    // else if (command == "evaluate")
    // {
    //     if (args.size() >= 2)
    //     {
    //         std::string functionName = args[0];
    //         std::vector<double> funcArgs;
    //         for (size_t i = 1; i < args.size(); ++i)
    //         {
    //             funcArgs.push_back(std::stod(args[i]));
    //         }
    //         try
    //         {
    //             double result = functionManager.evaluateFunction(functionName, funcArgs);
    //             std::cout << result << std::endl;
    //         }
    //         catch (const std::exception &e)
    //         {
    //             std::cout << "Error: " << e.what() << std::endl;
    //         }
    //     }
    //     else
    //     {
    //         std::cout << "Usage: evaluate <function_name> <arg1> <arg2> ..." << std::endl;
    //     }
    // }
    // else if (command == "if")
    // {
    //     std::string conditionArgs;
    //     for (const std::string &arg : args)
    //     {
    //         conditionArgs += arg + " ";
    //     }
    //     executeConditional(conditionArgs, variableManager);
    // }
    else if (command == "suspend")
    {
        suspendProc(args);
    }
    else if (command == "resume")
    {
        resumeProc(args);
    }
    else if (command == "add_path")
    {
        if (!args.empty())
        {
            environmentManager.addToPath(args[0]);
        }
        else
        {
            std::cout << "Usage: add_path <path>" << std::endl;
        }
    }
    else if (command == "remove_path")
    {
        if (!args.empty())
        {
            environmentManager.removeFromPath(args[0]);
        }
        else
        {
            std::cout << "Usage: remove_path <path>" << std::endl;
        }
    }
    else if (command == "print_env")
    {
        if (!args.empty())
        {
            environmentManager.printEnv(args[0]);
        }
        else
        {
            std::cout << "Usage: print_env <variable>" << std::endl;
        }
    }
    else if (command == "set_env")
    {
        if (args.size() >= 2)
        {
            environmentManager.setEnv(args[0], args[1]);
        }
        else
        {
            std::cout << "Usage: set_env <variable> <value>" << std::endl;
        }
    }
    else if (command == "unset_env")
    {
        if (!args.empty())
        {
            environmentManager.unsetEnv(args[0]);
        }
        else
        {
            std::cout << "Usage: unset_env <variable>" << std::endl;
        }
    }
    else if (command == "list_env")
    {
        environmentManager.listAllEnv();
    }
    else if (command == "is_in_path")
    {
        if (!args.empty())
        {
            bool result = environmentManager.isInPath(args[0]);
            std::cout << args[0] << (result ? " is" : " is not") << " in PATH." << std::endl;
        }
        else
        {
            std::cout << "Usage: is_in_path <path>" << std::endl;
        }
    }
    else if (command == "save_env")
    {
        if (!args.empty())
        {
            environmentManager.saveEnvToFile(args[0]);
        }
        else
        {
            std::cout << "Usage: save_env <filename>" << std::endl;
        }
    }
    else if (command == "load_env")
    {
        if (!args.empty())
        {
            environmentManager.loadEnvFromFile(args[0]);
        }
        else
        {
            std::cout << "Usage: load_env <filename>" << std::endl;
        }
    }
    else if (command == "write_file")
    {
        fileManager.writeFile(args);
    }
    else if (command == "read_file")
    {
        if (!args.empty())
        {
            fileManager.readFile(args[0]);
        }
        else
        {
            std::cout << "Usage: read_file <file_name>" << std::endl;
        }
    }
    else if (command == "file_size")
    {
        if (!args.empty())
        {
            fileManager.showFileSize(args[0]);
        }
        else
        {
            std::cout << "Usage: file_size <file_name>" << std::endl;
        }
    }
    else
    {
        std::cout << "Unknown command: " << command << std::endl;
    }
}

// Hàm này để tách input thành các tokens, mỗi token là một phần của input
/* Ví dụ:
 | Input: calcualte 1 + 2 => tokens: ["calculate", "1", "+", "2"]
 | Input write_file "Hello World" "output.txt" => tokens: ["write_file", "Hello World", "output.txt"]
 |
 | [!] Một số trường hợp khi toán tử (các dấu ngoặc, +, -, *, /) không có khoảng trắng ở giữa,
 | cần phải tách ra thành các token riêng biệt.
 | Ví dụ: calculate (1+2) => tokens: ["calculate", "(", "1", "+", "2", ")"]
 |
 | [!] Một số trường hợp khi có dấu ngoặc kép, cần phải giữ nguyên nội dung trong dấu ngoặc.
 | Và nếu gặp dấu phẩy (,) thì cũng cần phải tách ra thành token riêng biệt.
 | Ví dụ: function f(x, y) "x + y" => tokens: ["function", "f", "(", "x", ",", "y", ")", "\"x + y\""]
 */
std::vector<std::string> splitInput(const std::string &input)
{
    std::vector<std::string> tokens;
    std::string token;
    bool inQuotes = false;

    for (char ch : input)
    {
        if (ch == '\"')
        {
            inQuotes = !inQuotes;
            token += ch;
        }
        else if (isspace(ch) && !inQuotes)
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
        }
        else if ((ch == '(' || ch == ')' || ch == ',' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '<' || ch == '>') && !inQuotes)
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(std::string(1, ch));
        }
        else
        {
            token += ch;
        }
    }

    if (!token.empty())
    {
        tokens.push_back(token);
    }

    return tokens;
}

int main()
{
    //  In ra thông tin ban đầu khi shell khởi động
    printInitialInfo();

    commandHistory.load(); // Tải lịch sử từ file (nếu có)

    std::string input;

    signal(SIGINT, SIG_IGN);

    while (true)
    {
        setColor(ConsoleColor::YELLOW);
        std::cout << "tiny_shell> ";
        resetColor();

        setColor(currentColor);

        std::getline(std::cin, input);

        if (std::cin.fail() || std::cin.eof())
        {
            std::cin.clear();
            std::cout << std::endl;
            continue;
        }

        // Ghi câu lệnh vào lịch sử
        commandHistory.add(input);

        // splitInput để tách input thành các tokens
        std::vector<std::string> tokens = splitInput(input);

        if (tokens.empty())
            continue;

        // Lấy lệnh từ tokens, là phần tử đầu tiên
        /* Ví dụ:
         | Input: calculate 1 + 2 => tokens: ["calculate", "1", "+", "2"] => command: "calculate"
         | Input write_file "Hello World" "output.txt" => tokens: ["write_file", "Hello World", "output.txt"] => command: "write_file"
         | Thành phần này quyết định hành động tiếp theo sẽ được thực hiện.
         */
        std::string command = tokens[0];

        // Xóa lệnh ra khỏi tokens => tokens chỉ còn các tham số của lệnh
        tokens.erase(tokens.begin());

        // Xử lý các lệnh còn lại
        executeCommand(command, tokens);
    }
    return 0;
}
