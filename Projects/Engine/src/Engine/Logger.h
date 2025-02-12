#pragma once
#include <string>
#include "Core.h"

namespace Engine {
    enum class ENGINE_API LogLevel {
        INFO,
        WARNING,
        ERROR,
        SUCCESS
    };

    class ENGINE_API Logger {
    public:
        static void Log(const std::string& message, LogLevel level);
    };
}