// utils/variables.hpp
#pragma once
#include <logger.hpp>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
//----------------------------------

inline Logger logger{std::clog, LogLevel::Debug, true};
inline constexpr const char* APP_NAME = "playground";
inline constexpr bool DEBUG_MODE = true;

//----------------------------------
namespace fs = std::filesystem;

#ifndef PROJECT_ROOT_DIR
    #define PROJECT_ROOT_DIR "."
#endif

inline static fs::path project_root() {
    return fs::path(PROJECT_ROOT_DIR);
}
inline static fs::path resource_path(const fs::path& relative) {
    return project_root() / "resources" / relative;
}

inline std::string load_text(const fs::path& rel){
    auto path = resource_path(rel);
    std::ifstream input(
        path, std::ios::binary
    );
    if (!input) {
        throw std::runtime_error("Cannot open resources: " + path.string());
    }
    return std::string{
        std::istreambuf_iterator<char>{input}, {}
    };
}
//----------------------------------
