#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <csignal>
#include <windows.h>
#include <thread>
#include "Feature/features.h"

CommandHistory commandHistory;
FunctionManager functionManager;
EnvironmentManager environmentManager;
VariableManager variableManager(environmentManager);
FileManager fileManager;
ProcessManager processManager;
DirectoryManager directoryManager;
SystemUtils systemUtils;
AliasManager aliasManager;
BookmarkManager bookmarkManager;
ConsoleColor currentColor = ConsoleColor::WHITE;

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

// Hàm thực thi lệnh
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
        directoryManager.deleteDirectory(args);
    }
    else if (command == "move")
    {
        directoryManager.moveDirectory(args);
    }
    else if (command == "open")
    {
        fileManager.openFile(args);
    }
    else if (command == "exit")
    {
        exitShell();
        PostQuitMessage(0); // Exit the program
    }
    else if (command == "list_tree")
    {
        directoryManager.listDirectoryTree(args);
    }
    else if (command == "create")
    {
        directoryManager.createDirectory(args);
    }
    else if (command == "copy")
    {
        directoryManager.copyDirectory(args);
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
        fileManager.renameFile(args);
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
    else if (command == "start_foreground")
    {
        processManager.startProcessForeground(args);
    }
    else if (command == "start_background")
    {
        processManager.startProcessBackground(args);
    }
    else if (command == "terminate")
    {
        processManager.terminateProcess(args);
    }
    else if (command == "list_processes")
    {
        processManager.listProcesses(args);
    }
    else if (command == "list_children")
    {
        processManager.printAllChildProcesses(args);
    }
    else if (command == "child")
    {
        processManager.startChildProcess();
    }
    else if (command == "countdown")
    {
        processManager.startCountdownProcess();
    }
    else if (command == "manage_threads")
    {
        handleManageThreadsCommand(args);
    }
    else if (command == "time")
    {
        systemUtils.showSystemTime(args);
    }
    else if (command == "date")
    {
        systemUtils.showSystemDate(args);
    }
    else if (command == "uptime")
    {
        systemUtils.showSystemUptime(args);
    }
    else if (command == "cpuinfo")
    {
        systemUtils.showCPUInfo(args);
    }
    else if (command == "meminfo")
    {
        systemUtils.showMemoryInfo(args);
    }
    else if (command == "diskinfo")
    {
        systemUtils.showDiskInfo(args);
    }
    else if (command == "calculator")
    {
        systemUtils.showCalculator(args);
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
    else if (command == "tictactoe")
    {
        processManager.startTicTacToe();
    }
    else if (command == "duck")
    {
        processManager.startDuck();
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
    else if (command == "loop")
    {
        if (args.size() < 1)
        {
            std::cout << "Usage: loop <number_of_iterations> <command1> & <command2> & ..." << std::endl;
        }
        else
        {
            handleLoop(args);
        }
    }
    else if (command == "suspend")
    {
        processManager.suspendProc(args);
    }
    else if (command == "resume")
    {
        processManager.resumeProc(args);
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
        // // Nếu có đúng 2 tham số thì thiết lập biến môi trường
        // if (args.size() == 2)
        // {
        //     environmentManager.setEnv(args[0], args[1]);
        // }
        // // Nếu có nhiều hơn 2 tham số thì phần tử thứ 2 trở đi sẽ là biểu thức cần tính toán
        // else if (args.size() > 2)
        // {
        //     std::vector<std::string> expression(args.begin() + 1, args.end());
        //     try
        //     {
        //         int result = variableManager.evaluateExpression(expression);
        //         environmentManager.setEnv(args[0], std::to_string(result));
        //     }
        //     catch (const std::exception &e)
        //     {
        //         std::cout << "Error: " << e.what() << std::endl;
        //     }
        // } // Nếu không có tham số nào thì thông báo lỗi
        // else
        // {
        //     std::cout << "Usage: set_env <variable> <value> or set_env <variable> <expression>" << std::endl;
        // }

        // Nếu có đúng 3 tham số và tham số thứ 2 là dấu bằng (=) thì thiết lập biến môi trường
        if (args.size() == 3 && args[1] == "=")
        {
            environmentManager.setEnv(args[0], args[2]);
        }
        // Nếu có nhiều hơn 3 tham số thì phần tử thứ 2 trở đi sẽ là biểu thức cần tính toán
        else if (args.size() > 3)
        {
            std::vector<std::string> expression(args.begin() + 2, args.end());
            try
            {
                int result = variableManager.evaluateExpression(expression);
                environmentManager.setEnv(args[0], std::to_string(result));
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        // Nếu không có tham số nào thì thông báo lỗi
        else
        {
            std::cout << "Usage: set_env <variable> = <value> or set_env <variable> = <expression>" << std::endl;
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
        try
        {
            fileManager.writeFile(args);
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    else if (command == "read_file")
    {
        try
        {
            fileManager.readFile(args);
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << std::endl;
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
    else if (command == "convert")
    {
        handleBaseConversion(args);
    }
    else if (command == "bookmark")
    {
        if (args.size() == 3 && args[0] == "add")
        {
            bookmarkManager.addBookmark(args[1], args[2]);
        }
        else if (args.size() == 2 && args[0] == "remove")
        {
            bookmarkManager.removeBookmark(args[1]);
        }
        else if (args.size() == 1 && args[0] == "list")
        {
            bookmarkManager.listBookmarks();
        }
        else if (args.size() == 2 && args[0] == "go")
        {
            bookmarkManager.goBookmark(args[1]);
        }
        else if (args.size() == 1 && args[0] == "home")
        {
            bookmarkManager.goHomeDirectory();
        }
        else
        {
            std::cerr << "Usage: bookmark [add <name> <path> | remove <name> | list | go <name> | home]" << std::endl;
        }
    }
    else if (command == "alias")
    {
        if (args.empty())
        {
            aliasManager.listAliases();
        }
        else if (args.size() == 3)
        {
            aliasManager.addAlias(args[0], args[2]);
        }
        else
        {
            std::cerr << "Usage: alias <name> = <command> or alias" << std::endl;
        }
    }
    else if (command == "unalias")
    {
        if (!args.empty())
        {
            aliasManager.removeAlias(args[0]);
        }
        else
        {
            std::cerr << "Usage: unalias <name>" << std::endl;
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
            if (!inQuotes) // End of quoted string
            {
                tokens.push_back(token);
                token.clear();
            }
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

    // Nếu tokens không rỗng thì giải quyết alias
    if (!tokens.empty())
    {
        tokens[0] = aliasManager.resolveAlias(tokens[0]);
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
