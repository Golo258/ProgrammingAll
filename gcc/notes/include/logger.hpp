// mini_logger.hpp
#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <string>

// --- /dev/null for stream disabled
struct NullBuf : std::streambuf
{
    int overflow(int c) override { 
        return traits_type::not_eof(c); 
    }
};
inline NullBuf &nullbuf()
{
    static NullBuf nb;
    return nb;
}
inline std::ostream &devnull()
{
    static std::ostream os(&nullbuf());
    return os;
}

enum class LogLevel
{
    Debug = 0,
    Info = 1,
    Warn = 2,
    Error = 3
};

class Logger
{
public:
    explicit Logger(
        std::ostream &out = std::clog,
        LogLevel min_level = LogLevel::Info,
        bool with_time = true
    )
        : _out(out), _min(min_level), _with_time(with_time) {}

    void set_min_level(LogLevel lvl) {
        _min = lvl;
    }
    void set_with_time(bool v) {
        _with_time = v;
    }

    // Wygodne metody:
    std::ostream& debug() { 
        return stream(LogLevel::Debug) << prefix("DEBUG");
    }
    std::ostream& info() {
        return stream(LogLevel::Info) << prefix("INFO "); 
    }
    std::ostream& warn() {
        return stream(LogLevel::Warn) << prefix("WARN "); 
    }
    std::ostream& error() {
        return stream(LogLevel::Error) << prefix("ERROR"); 
    }

private:
    std::ostream &_out;
    LogLevel _min;
    bool _with_time;

    std::ostream& stream(LogLevel lvl)
    {
        return (lvl >= _min)?
            _out :
            devnull();
    }

    std::string prefix(const char *level)
    {
        if (!_with_time){
            return std::string("[") + level + "] ";
        }
        using namespace std::chrono;
        auto now = system_clock::now();
        auto t = system_clock::to_time_t(now);
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
        std::tm tm{};
        localtime_r(&t, &tm);
        std::ostringstream oss;
        oss << '[' << std::put_time(&tm, "%F %T")
            << '.' << std::setw(3) << std::setfill('0') << ms.count()
            << "][" << level << "] ";
        return oss.str();
    }
};
