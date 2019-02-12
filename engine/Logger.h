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

    static void logLevel(const Level level);

    static void log(const Level level, const std::string& message);

    static void debug(const std::string& message);
    static void info(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);

    Logger() = delete;
    ~Logger() = delete;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    static std::mutex _lock;
    static Level _logLevel;
};

}
