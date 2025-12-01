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
    std::string dots = "\n----------------------------------------------\n";

    // ------------------------------------------------------
    logger.info() << dots << "STANDARD STREAM INTRODUCTION" << std::endl;
    using Standard = Streams::StandardStream;
    Standard std_stream;
    // std_stream.standard_input(); 
    std_stream.standard_output();

    // ------------------------------------------------------
    logger.info() << dots << "FILE STREAM INTRODUCTION" << std::endl;
    Streams::FileStream file_stream;
    file_stream.write_data_out();
    file_stream.write_data_out_by_append();
    file_stream.read_from_in();

    // ------------------------------------------------------
    logger.info() << dots << "MEMORY STREAM INTRODUCTION" << std::endl;
    Streams::MemoryStream memory_stream;
    memory_stream.load_string_into_buffor();
    memory_stream.load_data_into_buffor();
    memory_stream.read_and_write_data_to_buffor();

    // ------------------------------------------------------
    logger.info() << dots << "FILE SYSTEM MANAGEMENT INTRODUCTION" << std::endl;
    Streams::FileSystemManagment fsystem_management;
    std::filesystem::path file_path = fsystem_management.create_paths();
    fsystem_management.paths_management(file_path);
    // fsystem_management.file_states(file_path);
    // fsystem_management.modification(file_path);
    fsystem_management.get_file_from_resources();

    // ------------------------------------------------------
    logger.info() << dots << "ALIASES AND TYPES INTRODUCTION" << std::endl;
    namespace aliases = Knowledge::AliasesAndTypes;
    aliases::AliasesPlayground aliases_playground;
    aliases_playground.basic_aliases();
    aliases_playground.template_aliases();
    aliases_playground.strong_types();
    aliases_playground.play_with_variant_save_union();
    aliases_playground.play_with_optional();

    // ------------------------------------------------------
    logger.info() << dots << "CASTING INTRODUCTION" << std::endl;
    aliases::CastingPlayground casting_playground;
    casting_playground.implicit_conversion();
    casting_playground.convert_static_cast();
    int x = 10;
    const int* some_var = &x;
    casting_playground.convert_const_cast(some_var);
    logger.debug() << "After casting" << x << "\n";
    casting_playground.convert_reinterpret_cast();
    casting_playground.convert_dynamic_cast();

    // ------------------------------------------------------
    logger.info() << dots << "POINTERS INTRODUCTION" << std::endl;
    aliases::PointersPlayground pointers_playground;
    pointers_playground.basic_pointer();
    pointers_playground.pointer_to_structure();
    pointers_playground.allocate_memory_dynamic();
    pointers_playground.unique_pointer();
    pointers_playground.shared_pointer();

    // ------------------------------------------------------
    namespace enums = aliases::Enums;
    logger.info() << dots << "ENUMS INTRODUCTION" << std::endl;
    enums::EnumPlayground enums_playground;
    enums_playground.basic_enum_attribute_check();
    enums_playground.enum_class_value_retrieval();
    enums_playground.enum_class_hex_attribute_value();
    enums_playground.enum_as_vector_type_iteration();
    enums_playground.mapping_enum_to_string();

    // ------------------------------------------------------
    namespace templates = aliases::Templates;
    logger.info() << dots << "TEMPLATES INTRODUCTION" << std::endl;
    templates::TemplatePlayground template_playground;
    template_playground.basic_redundancy_difference();
    template_playground.template_functions();
    template_playground.template_classes();
    template_playground.template_as_vector_type();

    // ------------------------------------------------------
    namespace compile_time = Knowledge::CompileTime;
    logger.info() << dots << "COMPILE TIME INTRODUCTION" << std::endl;
    compile_time::CompilePlayground compile_playground;
    compile_playground.compile_time_basic_definition();
    compile_playground.compile_time_functions();
    compile_playground.only_compile_time_functions();
    compile_playground.only_compile_time_inicialization();

    // ------------------------------------------------------
    namespace class_know = Knowledge::ClassKnow;
    logger.info() << dots << "CLASSESS INTRODUCTION" << std::endl;
    namespace class_specificators = class_know::Specificators;
    logger.info() << dots << "SPECIFICATORS INTRODUCTION" << std::endl;
    class_specificators::SpecificatorPlayground spec_playground;
    spec_playground.private_spec_introduce();
    spec_playground.public_spec_introduce();
    spec_playground.protected_spec_introduce();
    
    // ------------------------------------------------------
    logger.info() << dots << "LIFE CYCLE INTRODUCTION" << std::endl;
    class_know::LifeCycle::LifeCyclePlayground life_cycle_playground;
    life_cycle_playground.basic_constructor();
    life_cycle_playground.basic_destructor();
    logger.info() << dots << std::endl;
    class_know::GettersAndSetters::demonstrate_gates();
    // ------------------------------------------------------    
    logger.info() << dots << "STRUCTURES INTRODUCTION" << std::endl;
    class_know::Structures::StructuresPlayground struct_playground;
    struct_playground.creation_ways();
    struct_playground.nested_structs();
    // ------------------------------------------------------    
    logger.info() << dots;
    class_know::Inheritance::inheritance_introduction();
    // ------------------------------------------------------    
    logger.info() << dots;
    class_know::Polymorphism::show_polymorphism();
    // ------------------------------------------------------    
    logger.info() << dots << "EXCEPTIONS INTRODUCTION" << std::endl;
    Knowledge::ExceptionsKnow::ExceptionPlayground exception_playground;
    exception_playground.simple_throw();
    exception_playground.custom_throw();
    exception_playground.custom_with_specific_message();
    // ------------------------------------------------------    
    logger.info() << dots << "STRINGS INTRODUCTION" << std::endl;
    std::string text = " some funny tricky text\n";
    Knowledge::StringKnow::StringOperation str_playground(text);
    str_playground.access_string_attributes();

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
    // Knowledge::StringKnow::show_all_string_operation();
    // Knowledge::Functions::show_all_functions();
}

int main() {
    std::cout<< "\n<---------------------------------------->\n";
    // parser_task();
    // knowleadge_playground();
    KNOWLEAGE_INTRODUCTION();
    std::cout << "\n<---------------------------------------->\n";
    return 0;
}

// Patterns
/*----------------AliasesAndTypes::Enums NAMESPACE---------------------------*/
/*----------AliasesAndTypes::CastingPlayground class methods------------*/
