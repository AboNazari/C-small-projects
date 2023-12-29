#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

enum class LogLevel {
    Debug,
    Info,
    Warning,
    Error
};

class Logger {
public:
    Logger(LogLevel level = LogLevel::Info, const std::string &outputFilename = "");

    void log(const std::string &message, LogLevel level);

    ~Logger();

private:
    std::ofstream logFile;
    LogLevel currentLevel;

    static std::string getLevelString(LogLevel level);

    void write(const std::string &message);
};

#endif // LOGGER_H
