#ifndef ENVIRONMENT_VALUE_H
#define ENVIRONMENT_VALUE_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

#include <windows.h>
#include <shlwapi.h>

void getEnv(const vector<string> &args) {
    if (args.size() != 1) {
        cerr << "Usage: get_env <environment_value_name>\n";
        return;
    }
    LPCSTR varName = args[0].c_str();

    CHAR buffer[SHRT_MAX];
    DWORD bufferSize = sizeof(buffer) / sizeof(CHAR);

    DWORD ret = GetEnvironmentVariable(varName, buffer, bufferSize);

    if (ret == 0) {
        cerr << "Failed to get the environment variable or the variable does not exist.\n";
    }
    else {
        cout << "The value of " << varName << " is: " << buffer << "\n";
    }
}

void setEnv(const vector<string> &args) {
    if (args.size() != 2) {
        cerr << "Usage: set_env <environment_value_name> <environment_value_value>\n";
        return;
    }
    LPCSTR varName = args[0].c_str();
    LPCSTR varValue = args[1].c_str();
    
    BOOL ret = SetEnvironmentVariable(varName, varValue);

    if (!ret) {
        cerr << "Failed to set the environment variable.\n";
    }
    else {
        cout << "Environment variable " << varName << " set to " << varValue << "\n";
    }
}

void addPath(const vector<string> &args) {
    if (args.size() != 1) {
        cerr << "Usage: add_path <environment_value_value>\n";
        return;
    }
    
    LPCSTR newPath = args[0].c_str();

    CHAR buffer[SHRT_MAX];
    DWORD bufferSize = sizeof(buffer) / sizeof(CHAR);

    DWORD ret = GetEnvironmentVariable("PATH", buffer, bufferSize);
    if (ret == 0) {
        cerr << "Failed to get PATH or the PATH does not exist.\n";
        return;
    }

    if (StrStr(buffer, newPath) != NULL) {
        cout << "The path " << newPath << " is already in the PATH environment variable.\n";
        return;
    }
    
    StrCat(buffer, ";");
    StrCat(buffer, newPath);

    BOOL setResult = SetEnvironmentVariable("PATH", buffer);
    if (!setResult)
    {
        cerr << "Failed to set the PATH environment variable.\n";
    }
    else
    {
        cout << "PATH environment variable updated successfully.\n";
    }
}

void printEnv(const vector<string> &args) {
    if (!args.empty()) {
        cerr << "Usage: print_env\n";
        return;
    }
    LPCH envStrings = GetEnvironmentStrings();
    if (envStrings == NULL) {
        cerr << "Failed to get environment strings.\n";
        return;
    }

    LPCH current = envStrings;

    while (*current) {
        cout << current << '\n';
        
        while (*current) {
            ++current;
        }
        
        ++current;
    }

    FreeEnvironmentStrings(envStrings);
}

#endif