#pragma once
#include <string>
#include <format>
#include <iostream>
#include "Core.h"

enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    SUCCESS
};

class ENGINE_API Logger {
public:
    template<typename... Args>
    static void Log(LogLevel level, std::string_view format, Args&&... args) {
        std::string formattedMessage = std::vformat(format, std::make_format_args(args...));

        switch (level) {
        case LogLevel::INFO:
            std::cout << "\033[34m[INFO]:\033[0m " << formattedMessage << std::endl;
            break;
        case LogLevel::WARNING:
            std::cout << "\033[33m[WARNING]:\033[0m " << formattedMessage << std::endl;
            break;
        case LogLevel::ERROR:
            std::cout << "\033[31m[ERROR]:\033[0m " << formattedMessage << std::endl;
            break;
        case LogLevel::SUCCESS:
            std::cout << "\033[32m[SUCCESS]:\033[0m " << formattedMessage << std::endl;
            break;
        }
    }
};

// Macros for logging
#define LOG_INFO(format, ...)    Logger::Log(LogLevel::INFO, format, __VA_ARGS__)
#define LOG_WARNING(format, ...) Logger::Log(LogLevel::WARNING, format, __VA_ARGS__)
#define LOG_ERROR(format, ...)   Logger::Log(LogLevel::ERROR, format, __VA_ARGS__)
#define LOG_SUCCESS(format, ...) Logger::Log(LogLevel::SUCCESS, format, __VA_ARGS__)
