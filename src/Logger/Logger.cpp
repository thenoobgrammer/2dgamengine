#include "Logger.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>
#ifdef _WIN32
#include <windows.h>
#endif

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";

std::vector<LogEntry> Logger::messages;

std::string getFormattedDate() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%d/%b/%Y");
    return ss.str();
}

void setColor(int color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
#else
#endif
}

void Logger::Log(const std::string& message) {
    LogEntry logEntry;
    logEntry.type = LOG_INFO;
    logEntry.message = "LOG [" + getFormattedDate() + "]: " + message;
    setColor(10);
    std::cout << logEntry.message << "\n";
    messages.push_back(logEntry);
}

void Logger::Warn(const std::string& message) {
    LogEntry logEntry;
    logEntry.type = LOG_WARNING;
    logEntry.message = "LOG [" + getFormattedDate() + "]: " + message;
    setColor(14);
    std::cout << logEntry.message << "\n";
    messages.push_back(logEntry);
}

void Logger::Err(const std::string& message) {
    LogEntry logEntry;
    logEntry.type = LOG_ERROR;
    logEntry.message = "LOG [" + getFormattedDate() + "]: " + message;
    setColor(12);
    std::cout << logEntry.message << "\n";
    messages.push_back(logEntry);
}