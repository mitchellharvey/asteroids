#include <iostream>

#include "engine/Logger.h"

namespace thirstyfish { 

    std::mutex Logger::_lock;
    Logger::Level Logger::_logLevel = Logger::Level::DEBUG;

    void Logger::LogLevel(const Level level) {
        std::lock_guard<std::mutex> lock(Logger::_lock);
        Logger::_logLevel = level;
    }

    void Logger::Log(const Level level, const std::string& message) {
        static const char* type[] = {
            "DEBUG", "INFO", "WARNING", "ERROR"
        };

        std::lock_guard<std::mutex> lock(Logger::_lock);

        if (level >= Logger::_logLevel) {
            uint8_t idx = static_cast<uint8_t>(level);
            std::cout << "[" << type[idx] << "] " << message << std::endl;
        }
    }

    void Logger::Debug(const std::string& message) {
        Log(Level::DEBUG, message);
    }

    void Logger::Info(const std::string& message) {
        Log(Level::INFO, message);
    }

    void Logger::Warning(const std::string& message) {
        Log(Level::WARNING, message);
    }

    void Logger::Error(const std::string& message) {
        Log(Level::ERROR, message);
    }

}
