// modules/utils/logger.cpp

#include <utils/logger.hpp>
std::string Logger::prefix(const char* level) {
    if (!_with_time) 
        return std::string("[") + level + "] ";

    using namespace std::chrono;
    auto now = system_clock::now();
    auto t   = system_clock::to_time_t(now);
    auto ms  = duration_cast<milliseconds>(
        now.time_since_epoch()
    ) % 1000;

    std::tm tm{};
    #if defined(_WIN32)
        localtime_s(&tm, &t);
    #else
        localtime_r(&t, &tm);
    #endif
    std::ostringstream oss;
    oss << '[' << std::put_time(&tm, "%F %T")
        << '.' << std::setw(3) 
        << std::setfill('0') << ms.count()
        << "][" << level << "] ";
    return oss.str();
}