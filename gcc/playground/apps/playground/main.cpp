// ---------EXTERNAL----------------
#include <string>
//----------INTERNAL----------------
#include <utils/logger.hpp>
#include <utils/parse.hpp>
#include <docs/knowledge.hpp>


void logger_example(){
    Logger log{std::clog, LogLevel::Debug, true};
    log.debug() << "Start aplikacji\n";
    log.info()  << "Siema, działa logowanie\n";
    log.warn()  << "Uwaga  to tylko demo\n";
    log.error() << "Błąd testowy\n";
}
int main() {
    Logger log{std::clog, LogLevel::Debug, true};
    // Strumienie, zabawa
    log.info() << "\n<======================================>\n";
    // Knowledge::StreamsManagement::standard_stream();
    // Knowledge::StreamsManagement::show_file_stream();
    std::string_view example_results = 
    "Alice:10\n"
    "  Math         :   61\n"
    "# kobi: 52\n"
    " marcin=  12\n"
    " kasztan: bialy\n"
    " 51: bialy\n"
    " 51: 21\n"
    " kasz anka: 83\n";
    // using namespace utils::parser;
    // LeaderboardResults results = parse_name_score_lines(example_results);
    // Knowledge::Collections::show_all_methods();
    // Knowledge::StringKnow::show_all_string_operation();
    Knowledge::ClassKnow::demonstrate_classes();
    log.info() << "\n<======================================>\n";
    return 0;
}