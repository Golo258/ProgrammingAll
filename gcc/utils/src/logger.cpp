// modules/utils/logger.cpp

#include <logger.hpp>

std::string Logger::prefix(const char* level) {
    if (!_with_time) 
        return std::string("[") + level + "] ";

    std::ostringstream oss;
    oss << "[" << level << "] ";
    return oss.str();
}