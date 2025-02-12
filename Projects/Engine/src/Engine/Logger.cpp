#include <iostream>
#include "Logger.h"

namespace Engine {
    void Logger::Log(const std::string& message, LogLevel level) {
        switch (level) {
        case LogLevel::INFO:
            std::cout << "\033[34m[INFO]:\033[0m " << message << std::endl; // Blue for INFO
            break;
        case LogLevel::WARNING:
            std::cout << "\033[33m[WARNING]:\033[0m " << message << std::endl; // Yellow for WARNING
            break;
        case LogLevel::ERROR:
            std::cout << "\033[31m[ERROR]:\033[0m " << message << std::endl; // Red for ERROR
            break;
        case LogLevel::SUCCESS:
            std::cout << "\033[32m[SUCCESS]:\033[0m " << message << std::endl; // Green for SUCCESS
            break;
        }
    }
}