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

class KnowleadgeIntroduction{
    std::string dots = "\n----------------------------------------------\n";
    const char ENDL = '\n';

    public:
        void show_stream_management(){
            namespace Streams = Knowledge::StreamsManagement;
            // ------------------------------------------------------
            logger.info() << dots 
                << "STANDARD STREAM INTRODUCTION" << ENDL;
            using Standard = Streams::StandardStream;
            Standard std_stream;
            std_stream.standard_output();
            // ------------------------------------------------------
            logger.info() << dots 
                << "FILE STREAM INTRODUCTION" << ENDL;
            Streams::FileStream file_stream;
            file_stream.write_data_out();
            file_stream.write_data_out_by_append();
            file_stream.read_from_in();
            // ------------------------------------------------------
            logger.info() << dots 
                << "FILE SYSTEM MANAGEMENT INTRODUCTION" << ENDL;
            Streams::FileSystemManagment fsystem_management;
            std::filesystem::path file_path = fsystem_management.create_paths();
            fsystem_management.paths_management(file_path);
            fsystem_management.file_states(file_path);
            fsystem_management.modification(file_path);
            fsystem_management.get_file_from_resources();
        };
    
        void show_aliases_and_types(){
            logger.info() << dots 
                << "ALIASES AND TYPES INTRODUCTION" << std::endl;
            namespace aliases = Knowledge::AliasesAndTypes;
            aliases::AliasesPlayground aliases_playground;
            aliases_playground.basic_aliases();
            aliases_playground.template_aliases();
            aliases_playground.strong_types();
            aliases_playground.play_with_variant_save_union();
            aliases_playground.play_with_optional();
            // ------------------------------------------------------
            logger.info() << dots 
                << "CASTING INTRODUCTION" << std::endl;
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
            logger.info() << dots 
                << "POINTERS INTRODUCTION" << std::endl;
            aliases::PointersPlayground pointers_playground;
            pointers_playground.basic_pointer();
            pointers_playground.pointer_to_structure();
            pointers_playground.allocate_memory_dynamic();
            pointers_playground.unique_pointer();
            pointers_playground.shared_pointer();
            // ------------------------------------------------------
            namespace enums = aliases::Enums;
            logger.info() << dots 
                << "ENUMS INTRODUCTION" << std::endl;
            enums::EnumPlayground enums_playground;
            enums_playground.basic_enum_attribute_check();
            enums_playground.enum_class_value_retrieval();
            enums_playground.enum_class_hex_attribute_value();
            enums_playground.enum_as_vector_type_iteration();
            enums_playground.mapping_enum_to_string();
            // ------------------------------------------------------
            namespace templates = aliases::Templates;
            logger.info() << dots 
                << "TEMPLATES INTRODUCTION" << std::endl;
            templates::TemplatePlayground template_playground;
            template_playground.basic_redundancy_difference();
            template_playground.template_functions();
            template_playground.template_classes();
            template_playground.template_as_vector_type();
        }

        void show_compile_time(){
            namespace compile_time = Knowledge::CompileTime;
            logger.info() << dots 
                << "COMPILE TIME INTRODUCTION" << std::endl;
            compile_time::CompilePlayground compile_playground;
            compile_playground.compile_time_basic_definition();
            compile_playground.compile_time_functions();
            compile_playground.only_compile_time_functions();
            compile_playground.only_compile_time_inicialization();
        }
        
        void show_classes_knowleadge() {
            namespace class_know = Knowledge::ClassKnow;
            logger.info() << dots 
                << "CLASSESS INTRODUCTION" << std::endl;
            namespace class_specificators = class_know::Specificators;
            logger.info() << dots << "SPECIFICATORS INTRODUCTION" << std::endl;
            class_specificators::SpecificatorPlayground spec_playground;
            spec_playground.private_spec_introduce();
            spec_playground.public_spec_introduce();
            spec_playground.protected_spec_introduce();
            
            // ------------------------------------------------------
            logger.info() << dots 
                << "LIFE CYCLE INTRODUCTION" << std::endl;
            class_know::LifeCycle::LifeCyclePlayground life_cycle_playground;
            life_cycle_playground.basic_constructor();
            life_cycle_playground.basic_destructor();
            logger.info() << dots << std::endl;
            class_know::GettersAndSetters::demonstrate_gates();
            // ------------------------------------------------------    
            logger.info() << dots 
                << "STRUCTURES INTRODUCTION" << std::endl;
            class_know::Structures::StructuresPlayground struct_playground;
            struct_playground.creation_ways();
            struct_playground.nested_structs();
            // ------------------------------------------------------    
            logger.info() << dots;
            class_know::Inheritance::inheritance_introduction();
            // ------------------------------------------------------    
            logger.info() << dots;
            class_know::Polymorphism::show_polymorphism();
        }

        void show_exceptions_knowledge(){
            logger.info() << dots 
                << "EXCEPTIONS INTRODUCTION" << std::endl;
            Knowledge::ExceptionsKnow::ExceptionPlayground exception_playground;
            exception_playground.simple_throw();
            exception_playground.custom_throw();
            exception_playground.custom_with_specific_message();
        }
        void show_string_knowledge(){
            logger.info() << dots 
                << "STRINGS INTRODUCTION" << std::endl;
            std::string text = " some funny \t tricky text";
            Knowledge::StringKnow::StringOperation str_playground(text);
            str_playground.access_string_attributes();
            str_playground.modification_without_return();
            str_playground.modification_with_return();
            // ------------------------------------------------------    
            logger.info() << dots 
                << "REGEX INTRODUCTION" << std::endl;
            Knowledge::RegexKnowledge::RegexPlayground regex_playground;
            regex_playground.sign_classes();
            regex_playground.anchors();
            regex_playground.qualifiers();
            regex_playground.groups_alternatives();
            regex_playground.signs_sets();
            regex_playground.match();
            regex_playground.search();
            regex_playground.replace_match();
        }

        void show_collections_knowledge(){
            logger.info() << dots 
                << "COLLECTIONS INTRODUCTION" << std::endl;
            Knowledge::Collections::VectorPlayground vector_playground;
            // ------------------------------------------------------    
            logger.info() << dots << "VECTOR INTRODUCTION" << std::endl;
            vector_playground.creation_ways();
            vector_playground.access_and_safety();
            vector_playground.modification_and_memory();
            vector_playground.iteration();
            vector_playground.sort_and_algorithms();
            
            // ------------------------------------------------------    
            logger.info() << dots 
                << "MAP INTRODUCTION" << std::endl;
            Knowledge::Collections::MapPlayground map_playground;
            map_playground.creation();
            map_playground.access_and_safety();
            map_playground.modification_and_merging();
            map_playground.iteration();
            map_playground.custom_sorting_behavior();
            map_playground.pair_usage_scenarios();
        }

        void show_functions_knowledge(){
            logger.info() << dots 
                << "LAMBDA FUNCTION INTRODUCTION" << std::endl;
            Knowledge::Functions::LambdaPlayground lambda_playground;
            lambda_playground.syntax_and_basics();
            lambda_playground.capture_mechanisms();
            lambda_playground.std_function_wrapper();
            lambda_playground.modern_lambdas();
            // ------------------------------------------------------    
            logger.info() << dots 
                << "UTILIY FUNCS INTRODUCTION" << std::endl;
            Knowledge::Functions::UtilityPlayground utiliy_playground;
            utiliy_playground.char_operations();
            utiliy_playground.numeric_operations();
        }
};

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

int main() {
    KnowleadgeIntroduction introduction = KnowleadgeIntroduction();
    // introduction.show_stream_management();
    introduction.show_aliases_and_types();
    introduction.show_compile_time();
    introduction.show_classes_knowleadge();
    introduction.show_exceptions_knowledge();
    introduction.show_string_knowledge();
    introduction.show_functions_knowledge();
    return 0;
}



