

#include <utils/parse.hpp>

const std::string_view EXAMPLE_RESULT = 
    "Alice:10\n"
    "  Math         :   61\n"
    "# kobi: 52\n"
    " marcin=  12\n"
    " kasztan: bialy\n"
    " 51: bialy\n"
    " 51: 21\n"
    " kasz anka: 83\n";
    
namespace utils::parser {
    LeaderboardResults parse_name_score_lines(
        std::string_view text
    ){
        std::cout << " text: " << text << std::endl;
        BoardResult simple_result = {"Bob", 15};
        LeaderboardResults result;
        result.push_back(simple_result);
        return result;
    }
}