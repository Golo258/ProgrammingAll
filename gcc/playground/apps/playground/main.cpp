// ---------EXTERNAL----------------
#include <string>
//----------INTERNAL----------------
#include <utils/parse.hpp>
#include <docs/knowledge.hpp>
#include <utils/variables.hpp>
#include <apps/leaderboard.hpp>

void logger_example(){
    logger.debug() << "Start aplikacji\n";
    logger.info()  << "Siema, działa loggerowanie\n";
    logger.warn()  << "Uwaga  to tylko demo\n";
    logger.error() << "Błąd testowy\n";
}
    

void parser_task(){
    namespace up = utils::parser;
    const std::string EXAMPLE_INPUT_RESULT = 
    " marcin===  12\n"
    "# kobi= 52\n"
    "  Math         =   61\n"
    " kasztan = bialy\n"
    " 51: bialy\n"
    " 51: 21\n"
    "Alice:10\n"
    " kasz anka: 83\n";
    // LeaderboardResults results = parse_name_score_lines(EXAMPLE_INPUT_RESULT);
    // with_usage of file
    std::string score_results = load_text("scores.txt");
    up::LeaderboardResults results = up::parse_name_score_lines(score_results);
    Leaderboard board;
    for(up::BoardResult result: results){
        logger.info() << "Current result " 
            << result.first << ", "
            << result.second << "\n";
        board.set_score(
            result.first,
            result.second
        );
    }
    board.print(std::cout, 5);
    board.add_or_update("Kamil", 2000);
    board.print(std::cout, 5);
    auto mediana = board.mediana();
    auto average = board.average();
    if (mediana != std::nullopt){
        std::cout << "Mediana: " << *mediana << std::endl;
    }
    if (average != std::nullopt){
        std::cout << "Srednia: " << *average << std::endl;
    }

}
void knowleadge_playground(){
    // Knowledge::StreamsManagement::show_file_stream();
    // Knowledge::StreamsManagement::show_file_system_managment();
    // Knowledge::StreamsManagement::show_streams();
    // Knowledge::Collections::show_all_methods();
    // Knowledge::ClassKnow::demonstrate_classes();
    // Knowledge::StringKnow::show_all_string_operation();
    // Knowledge::ExceptionsKnow::show_all_exceptions();
    // Knowledge::Functions::show_all_functions();
    Knowledge::Structures::all();
}

int main() {
    std::cout<< "\n<---------------------------------------->\n";
    // parser_task();
    knowleadge_playground();
    std::cout << "\n<---------------------------------------->\n";
    return 0;
}