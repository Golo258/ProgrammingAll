// ---------EXTERNAL----------------
#include <string>
//----------INTERNAL----------------
#include <docs/knowledge.hpp>
#include <utils/variables.hpp>
// ----------------------------
#include <apps/board_app/parse.hpp>
#include <apps/board_app/leaderboard.hpp>

void logger_example(){
    logger.debug() << "Start aplikacji\n";
    logger.info()  << "Siema, działa loggerowanie\n";
    logger.warn()  << "Uwaga  to tylko demo\n";
    logger.error() << "Błąd testowy\n";
}
    
void KNOWLEAGE_INTRODUCTION() {
    namespace Streams = Knowledge::StreamsManagement;
    // ------------------------------------------------------
    logger.info() << "STANDARD STREAM INTRODUCTION" << std::endl;
    using Standard = Streams::StandardStream;
    Standard std_stream;
    // std_stream.standard_input(); 
    std_stream.standard_output();
    // ------------------------------------------------------
    logger.info() << "FILE STREAM INTRODUCTION" << std::endl;
    Streams::FileStream file_stream;
    file_stream.write_data_out();
    file_stream.write_data_out_by_append();
    file_stream.read_from_in();
    // ------------------------------------------------------
    logger.info() << "MEMORY STREAM INTRODUCTION" << std::endl;
    Streams::MemoryStream memory_stream;
    memory_stream.load_string_into_buffor();
    memory_stream.load_data_into_buffor();
    memory_stream.read_and_write_data_to_buffor();
    logger.info() << "FILE SYSTEM MANAGEMENT INTRODUCTION" << std::endl;
    Streams::FileSystemManagment fsystem_management;
    std::filesystem::path file_path = fsystem_management.create_paths();
    fsystem_management.paths_management(file_path);
    fsystem_management.file_states(file_path);
    // fsystem_management.modification(file_path);
    fsystem_management.get_file_from_resources();
}

void parser_task(){
    namespace bp = board::parser;
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
    bp::LeaderboardResults results = bp::parse_name_score_lines(score_results);
    Leaderboard board;
    for(bp::BoardResult result: results){
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
    // Knowledge::Collections::show_all_methods();
    // Knowledge::ClassKnow::demonstrate_classes();
    // Knowledge::StringKnow::show_all_string_operation();
    // Knowledge::ExceptionsKnow::show_all_exceptions();
    // Knowledge::Functions::show_all_functions();
    // Knowledge::Structures::all();
    // Knowledge::Preprocesor::all();
    // Knowledge::AliasesAndTypes::casting_example();
    // Knowledge::AliasesAndTypes::pointer_example();
    // Knowledge::AliasesAndTypes::enums_example();
    // Knowledge::AliasesAndTypes::check_optional();
    // Knowledge::AliasesAndTypes::Templates::show_tamples();

}

int main() {
    std::cout<< "\n<---------------------------------------->\n";
    // parser_task();
    // knowleadge_playground();
    KNOWLEAGE_INTRODUCTION();
    std::cout << "\n<---------------------------------------->\n";
    return 0;
}