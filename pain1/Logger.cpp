#include "Logger.h"

Logger::Logger(LogLevel level, const std::string &outputFilename) : currentLevel(level) {
    if (!outputFilename.empty()) {
        logFile.open(outputFilename, std::ios::out | std::ios::app);
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const std::string &message, LogLevel level) {
    if (level < currentLevel) {
        return; // Skip logging messages below the current log level
    }
    std::stringstream logEntry;
    logEntry << getLevelString(level) << ": " << message << std::endl;
    write(logEntry.str());
}

std::string Logger::getLevelString(LogLevel level) {
    switch (level) {
        case LogLevel::Debug:
            return "[DEBUG]";
        case LogLevel::Info:
            return "[INFO]";
        case LogLevel::Warning:
            return "[WARNING]";
        case LogLevel::Error:
            return "[ERROR]";
        default:
            return "[UNKNOWN]";
    }
}

void Logger::write(const std::string &message) {
    if (logFile.is_open()) {
        logFile << message;
    }
    std::cout << message; // Also write to the console
}
