
#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "utility"// std::pair

namespace utils {
    namespace parser {
        using BoardResult = std::pair<std::string, int>;
        using LeaderboardResults = std::vector<BoardResult>;
    
        struct ParseError : std::runtime_error {
            using std::runtime_error::runtime_error;
            // do dodania numer linii/ kolumny w komunikacie
        };
        
        LeaderboardResults parse_name_score_lines(std::string_view text);

    }
}