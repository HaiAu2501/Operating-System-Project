#ifndef SUSPEND_AND_RESUME_H
#define SUSPEND_AND_RESUME_H

#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

using namespace std;

void suspendProc(const vector<string> &args)
{
    if (args.size() != 1)
    {
        cerr << "Usage: suspend <PID>\n";
        return;
    }
    DWORD dwProcessId = stoul(args[0]);

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        cerr << "System error!\n";
        return;
    }

    THREADENTRY32 te;
    te.dwSize = sizeof(THREADENTRY32);

    if (!Thread32First(hSnapshot, &te))
    {
        CloseHandle(hSnapshot);
        cerr << "System error!\n";
        return;
    }

    do
    {
        if (te.th32OwnerProcessID == dwProcessId)
        {
            HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
            if (hThread != NULL)
            {
                SuspendThread(hThread);
                CloseHandle(hThread);
            }
            else
            {
                cerr << "System error!\n";
                return;
            }
        }
    } while (Thread32Next(hSnapshot, &te));

    CloseHandle(hSnapshot);
}

void resumeProc(const vector<string> &args)
{
    if (args.size() != 1)
    {
        cerr << "Usage: resume <PID>\n";
        return;
    }
    DWORD dwProcessId = stoul(args[0]);

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        cerr << "System error!\n";
        return;
    }

    THREADENTRY32 te;
    te.dwSize = sizeof(THREADENTRY32);

    if (!Thread32First(hSnapshot, &te))
    {
        CloseHandle(hSnapshot);
        cerr << "System error!\n";
        return;
    }

    do
    {
        if (te.th32OwnerProcessID == dwProcessId)
        {
            HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);
            if (hThread != NULL)
            {
                ResumeThread(hThread);
                CloseHandle(hThread);
            }
            else
            {
                cerr << "System error!\n";
                return;
            }
        }
    } while (Thread32Next(hSnapshot, &te));

    CloseHandle(hSnapshot);
}

#endif