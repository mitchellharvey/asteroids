#pragma once

#include <string>
#include <mutex>

namespace thirstyfish { 

class Logger {
public:
    enum class Level : uint8_t {
        DEBUG = 0,
        INFO,
        WARNING,
        ERROR
    };

    static void LogLevel(const Level level);

    static void Log(const Level level, const std::string& message);

    static void Debug(const std::string& message);
    static void Info(const std::string& message);
    static void Warning(const std::string& message);
    static void Error(const std::string& message);

    Logger() = delete;
    ~Logger() = delete;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    static std::mutex _lock;
    static Level _logLevel;
};

}
