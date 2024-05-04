#include <windows.h>
#include <iostream>
#include <iomanip>  // For std::setw and std::setfill
#include <sstream>  // For std::stringstream

std::string FormatDateTime(const SYSTEMTIME& st) {
    std::stringstream ss;
    // Example format: Fri Sep 13 17:45:12 UTC 2019
    // Note: This example does not handle locale and timezone conversions to UTC or other timezones.

    // Array of weekday names
    const char* weekdays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    // Array of month names
    const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    // Format the date and time
    ss << weekdays[st.wDayOfWeek] << " " << months[st.wMonth - 1] << " "
       << std::setw(2) << std::setfill('0') << st.wDay << " "
       << std::setw(2) << std::setfill('0') << st.wHour << ":"
       << std::setw(2) << std::setfill('0') << st.wMinute << ":"
       << std::setw(2) << std::setfill('0') << st.wSecond << " UTC "
       << st.wYear;

    return ss.str();
}

int main() {
    SYSTEMTIME st;
    GetLocalTime(&st);  // Retrieves the current local date and time

    std::string formattedDate = FormatDateTime(st);
    std::cout << formattedDate << std::endl;

    return 0;
}
