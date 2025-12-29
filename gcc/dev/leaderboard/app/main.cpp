

#include <parse.hpp>
#include <leaderboard.hpp>
#include <variables.hpp>

namespace bp = board::parser;

const std::string BOARD_DUMMY_DATA =  
    " marcin===  12\n"
    "# kobi= 52\n"
    "  Math         =   61\n"
    " kasztan = bialy\n"
    " 51: bialy\n"
    " 51: 21\n"
    "Alice:10\n"
    " coup er: 83\n";

int main() {
    Leaderboard board;
    bp::LeaderboardResults dummy_data_results = bp::parse_name_score_lines(BOARD_DUMMY_DATA);

    std::string score_results = load_text("scores.txt");
    bp::LeaderboardResults scores_file_results = bp::parse_name_score_lines(score_results);
    for(bp::BoardResult result: scores_file_results) {
        logger.info() 
            << "[BOARD RESULT]: t" 
            << result.first << ", " << result.second << "\n";
        board.set_score(result.first, result.second);
    }
    board.print(std::cout, 5);
    board.add_or_update("Kamil", 2000);
    board.print(std::cout, 5);
    auto mediana = board.mediana();
    auto average = board.average();
    if (mediana != std::nullopt) {
        std::cout << "Mediana: " << *mediana << std::endl;
    }
    if (average != std::nullopt) {
        std::cout << "Srednia: " << *average << std::endl;
    }

}
