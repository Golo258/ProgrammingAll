
#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "utility"// std::pair

namespace utils {
    struct ParseError : std::runtime_error {
        using std::runtime_error::runtime_error;
        // do dodania numer linii/ kolumny w komunikacie
    };

    //  z tego możnaby zrobić typ przez alias 
    std::vector<
        std::pair<std::string,int>
    > parse_name_score_lines(std::string_view text);
}