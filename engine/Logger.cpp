#include <iostream>

#include "engine/Logger.h"

namespace thirstyfish { 

std::mutex Logger::_lock;
Logger::Level Logger::_logLevel = Logger::Level::DEBUG;

void Logger::logLevel(const Level level) {
    std::lock_guard<std::mutex> lock(Logger::_lock);
    Logger::_logLevel = level;
}

void Logger::log(const Level level, const std::string& message) {
    static const char* type[] = {
        "DEBUG", "INFO", "WARNING", "ERROR"
    };

    std::lock_guard<std::mutex> lock(Logger::_lock);

    if (level >= Logger::_logLevel) {
        uint8_t idx = static_cast<uint8_t>(level);
        std::cout << "[" << type[idx] << "] " << message << std::endl;
    }
}

void Logger::debug(const std::string& message) {
    log(Level::DEBUG, message);
}

void Logger::info(const std::string& message) {
    log(Level::INFO, message);
}

void Logger::warning(const std::string& message) {
    log(Level::WARNING, message);
}

void Logger::error(const std::string& message) {
    log(Level::ERROR, message);
}

}
