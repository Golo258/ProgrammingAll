
#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "utility"// std::pair
#include <sstream>
#include <optional>
#include <variant>
#include <utils/variables.hpp>
#include <string>
#include <regex>

namespace utils {
    namespace parser {
        enum class Trim {
            LEFT,
            RIGHT,
            BOTH
        };
        using BoardResult = std::pair<std::string, int>;
        using LeaderboardResults = std::vector<BoardResult>;
        const std::string white_spaces_group = " \r\n\t\f\v";
        const char score_seperator = '=';

        struct ParseError : public std::runtime_error {
            using std::runtime_error::runtime_error;
        };
        
        std::optional<
            std::pair<std::string, std::string>
        > retrieve_scores_items(std::string buffor_line);
        std::variant<std::string, int> clean_items_parts(
            std::string part
        );
        LeaderboardResults parse_name_score_lines(std::string text);
        void trim_string(std::string& text, Trim side);
    }
}