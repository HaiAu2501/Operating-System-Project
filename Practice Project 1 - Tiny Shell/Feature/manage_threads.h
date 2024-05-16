#ifndef MANAGE_THREADS_H
#define MANAGE_THREADS_H

#include <iostream>
#include <vector>
#include <thread>
#include <windows.h>

// Biến chung (critical resource)
int sharedVariable = 0;

// Semaphore để kiểm soát truy cập vào biến chung
HANDLE semaphore;

// Hàm để mỗi luồng sử dụng tài nguyên găng
DWORD WINAPI threadFunction(LPVOID lpParam)
{
    int threadId = *reinterpret_cast<int *>(lpParam);

    for (int i = 0; i < 5; ++i)
    {
        // Chờ để lấy quyền truy cập vào tài nguyên găng
        WaitForSingleObject(semaphore, INFINITE);

        // Sử dụng tài nguyên găng
        std::cout << "Thread " << threadId << " is accessing the shared variable." << std::endl;
        sharedVariable++;
        std::cout << "Shared variable is now: " << sharedVariable << std::endl;

        // Nhả quyền truy cập vào tài nguyên găng
        ReleaseSemaphore(semaphore, 1, NULL);

        // Giả lập thời gian xử lý
        Sleep(1000);
    }

    return 0;
}

// Hàm để tạo và quản lý các luồng
void createAndManageThreads(int numThreads)
{
    // Tạo Semaphore với giá trị ban đầu là 1 và giới hạn là 1
    semaphore = CreateSemaphore(NULL, 1, 1, NULL);
    if (semaphore == NULL)
    {
        std::cerr << "CreateSemaphore error: " << GetLastError() << std::endl;
        return;
    }

    std::vector<HANDLE> threads(numThreads);
    std::vector<int> threadIds(numThreads);

    // Tạo các luồng
    for (int i = 0; i < numThreads; ++i)
    {
        threadIds[i] = i + 1;
        threads[i] = CreateThread(NULL, 0, threadFunction, &threadIds[i], 0, NULL);
        if (threads[i] == NULL)
        {
            std::cerr << "CreateThread error: " << GetLastError() << std::endl;
            return;
        }
    }

    // Chờ tất cả các luồng kết thúc
    WaitForMultipleObjects(numThreads, threads.data(), TRUE, INFINITE);

    // Đóng các handle của luồng
    for (int i = 0; i < numThreads; ++i)
    {
        CloseHandle(threads[i]);
    }

    // Đóng Semaphore
    CloseHandle(semaphore);
}

// Hàm xử lý lệnh manage_threads
void handleManageThreadsCommand(const std::vector<std::string> &args)
{
    if (args.size() != 1)
    {
        std::cout << "Usage: manage_threads <numThreads>" << std::endl;
    }
    else
    {
        int numThreads = std::stoi(args[0]);
        createAndManageThreads(numThreads);
    }
}

#endif // MANAGE_THREADS_H
