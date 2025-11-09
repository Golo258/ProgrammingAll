// ---------EXTERNAL----------------
#include <string>
//----------INTERNAL----------------
#include <utils/parse.hpp>
#include <docs/knowledge.hpp>
#include <utils/variables.hpp>


void logger_example(){
    logger.debug() << "Start aplikacji\n";
    logger.info()  << "Siema, działa loggerowanie\n";
    logger.warn()  << "Uwaga  to tylko demo\n";
    logger.error() << "Błąd testowy\n";
}
    


void parser_task(){
    using namespace utils::parser;
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
    LeaderboardResults results = parse_name_score_lines(score_results);

}
void knowleadge_playground(){
    // Knowledge::StreamsManagement::show_file_stream();
    Knowledge::StreamsManagement::show_file_system_managment();
    // Knowledge::Collections::show_all_methods();
    // Knowledge::ClassKnow::demonstrate_classes();
    // Knowledge::StringKnow::show_all_string_operation();
    // Knowledge::ExceptionsKnow::show_all_exceptions();
}

int main() {
    Logger log{std::clog, LogLevel::Debug, true};
    log.info() << "\n<======================================>\n";
    // parser_task();
    knowleadge_playground();
    log.info() << "\n<======================================>\n";
    return 0;
}