// ------------------------
#include <knowledge.hpp>

#pragma region KNOWLEDGE
namespace Knowledge{
    /*---------------------------------------------------------------------------------------*/
    #pragma region STREAMS_MANAGEMENT
    namespace StreamsManagement{

        #pragma region STANDARD_STREAM_CLASS
        
            void StandardStream::print_list(std::ostream& os, const std::vector<int>& items) {
                int index = 1;
                for (const auto& item: items) {
                    os << index++ << ") value: " 
                    << item << ENDL;
                }
            }

            std::vector<std::string> StandardStream::read_lines(std::istream& is) {
                std::vector<std::string> lines;
                std::string line;
                while(std::getline(is, line)) {
                    lines.push_back(line);
                }
                return lines;
            }

            void StandardStream::standard_output() {
                /* output - czyli dane wychodzą gdzieś
                    - funkcja nie zna celu wyjśca wtedy mamy ostream jako parametr
                */
                std::vector<int> numbs{1, 15, 61, 211};
                std::ofstream out("numbers_list.txt");
                std::ostringstream mem;
                print_list(out, numbs);
                print_list(mem, numbs);
                logger.info() << "Memory buffor: " << ENDL << mem.str();
                std::ifstream in("numbers_list.txt");
                std::istringstream stream_mem("a\nb\nc\n");
                auto lines = read_lines(in);
                auto mem_lines = read_lines(stream_mem);
                std::filesystem::remove("numbers_list.txt");
            }

            void StandardStream::standard_input() {
                logger.debug() << "Enter some number" << ENDL; //  pisanie do stdout - terminala 
                int number;
                /*  czyta z stdin - z klawiatury
                        czeka aż user wpisze, i przekonwertuje na dany typ
                    zła konwersja to bląd i cin ustawia flage błędu na failbit
                */ 
                std::cin >> number; 
                if (!std::cin) {
                    std::cin.clear();  // czyści buffor
                    std::cin.ignore(); // wyrzucenie śmieci z buffora
                    std::cerr          //  cerr - od razu wypisze bez buforowania
                        << "Provided number is not a integer";
                    return;
                }
                else {
                    logger.debug() << "Provided number: [" << number << "]." << ENDL; 
                    std::clog // clog do informacji diagnostycznych
                        << "[LOG-INFO] User provide number: " 
                        << number << ENDL;
            }
        }
        
        #pragma endregion STANDARD_STREAM_CLASS
        /*---------------------------------------------------------------------------------------*/
        #pragma region FILE_STREAM_CLASS
            
            void FileStream::write_data_out() {
                /* tworzy nowy plik albo czyści , domyślne tryby
                    std::ios::out | std::ios::trunc */
                std::ofstream out("notes.txt");
                if(!out) {
                    logger.debug() << "Cannot open for override";
                    return;
                }
                out << "[INFO] File stream in here!\n [NEXT] end\n<->";
                std::filesystem::remove("notes.txt");
            }  // out.close(); // after went out of func
            
            void FileStream::write_data_out_by_append() {
                std::ofstream append_out("notes.txt", std::ios::app); // dopisuje std::ios::app - append
                if(!append_out) {
                    logger.debug() << "Cannot open to append";
                    return;
                }
                append_out << "\n[NEW] one and last";
            }
            
            void FileStream::read_from_in() {
                std::ifstream in("notes.txt");
                if (!in) {
                    std::cerr << "Cannot open notes.txt" << ENDL;
                    return;
                }
                std::string line;
                int index = 0;
                /* getline() - pojedyncze pobranie to 
                    std::string first_line;
                    std::getline(in, first_line);
                    bierze z buffora pierwszą linie i wstawia w zmienną 
                */
                while (std::getline(in, line)) {
                    logger.debug() << "Line " << index++ << " content: " << line << ENDL; 
                }
                std::filesystem::remove("notes.txt");
            }
        
        #pragma endregion FILE_STREAM_CLASS
        /*---------------------------------------------------------------------------------------*/
        #pragma region MEMORY_STREAM_CLASS
        
            void MemoryStream::load_string_into_buffor() {
                std::string text = "12 34 5 61\n";
                /* Tekst trafia do buffora
                    bo chcesz na nim potem robić jakieś rzeczy
                    jakbyś czytał plik 
                */
                std::istringstream in(text);
                int a,b ,c, d;
                in >> a >> b >> c >> d;
                logger.debug() << "a=" << a 
                        << ", b=" << b 
                        << ", c=" << c 
                        << ", d=" << d << ENDL;
            }

            void MemoryStream::load_data_into_buffor() {
                std::ostringstream out;
                out << "Result: " << 27 << ENDL;
                std::string text = out.str(); // pobiera z buffora
                logger.debug() << "Content after loading from buffor " << text << ENDL;
            } 

            void MemoryStream::read_and_write_data_to_buffor() {
                std::stringstream sstream;
                sstream << "123 451";
                int first, second;
                sstream >> first >> second;
                logger.debug() << (first + second) << ENDL;
            }
        
        #pragma endregion MEMORY_STREAM_CLASS
        /*---------------------------------------------------------------------------------------*/
        #pragma region FILE_SYSTEM_MANAGEMENT_CLASS
        
            fs::path FileSystemManagment::create_paths() {
                /*  tworzenie ścieżek
                    operator / - składa ścieżki */
                fs::path user_path = "/home/user";
                fs::path scores_path = user_path / "home" / "scores.txt";
                return scores_path;
            }

            void FileSystemManagment::paths_management(fs::path path) {
                logger.info() << "Getting basic elements of paths: (slices)" << ENDL;
                logger.debug() << "[PATHS PARTS]" << ENDL
                    << "Filename: "   << path.filename()    << ENDL
                    << "Identifier: " << path.stem()        << ENDL
                    << "Extension: "  << path.extension()   << ENDL
                    << "Parent : "    << path.parent_path() << ENDL;
                
                /*  absolute - nie sprawdza czy istnieje 
                    cannonical - rzuca wyjatek
                    weakly_cannonical - nie rzuca  */
                fs::path absolute = fs::absolute(path);
                fs::path cannonical = fs::weakly_canonical(path);
                logger.debug()
                    << "[FULL PATHS]" << ENDL
                    << "  Absolute path : " << absolute    << ENDL
                    << "  Canonical     : " << cannonical  << "\n" << ENDL;
                /* aktualne środowisko pracy */
                // bierzące katalogi, gdzie jesteśmy
                logger.debug()
                    << "  Current path  : " << fs::current_path()       << ENDL
                    << "  Temp dir      : " << fs::temp_directory_path() << ENDL;
            }

            void FileSystemManagment::file_states(fs::path path) {
                logger.info() << "[FILE STATES]" << ENDL;
                /*Czy istnieje i jakim jest plikiem*/
                bool exists   = fs::exists(path);
                bool is_file  = fs::is_regular_file(path);
                bool is_dir   = fs::is_directory(path);
                bool is_empty = fs::is_empty(path);
                logger.debug()
                    << "  Exists        : " << std::boolalpha << exists << ENDL
                    << "  Is file       : " << is_file << ENDL
                    << "  Is directory  : " << is_dir << ENDL
                    << "  Is empty      : " << is_empty << ENDL;

                std::uintmax_t file_size = fs::file_size(path);
                if (exists) {
                    /* czas ostatniej akutalizacji:
                        auto path_time = fs::last_write_time(path);
                    czy wskazują na ten sam obiekt
                        fs::equivalent(path, fs::path("other.txt")); */
                }
            }

            void FileSystemManagment::modification(fs::path file_path) {
                logger.info() << "[FILE SYSTEM MANAGEMENT MODIFCATION]" << ENDL;
                bool already_exists = fs::create_directory(file_path);
                bool dirs_exists    = fs::create_directories(file_path);

                fs::remove(file_path);
                fs::remove_all(file_path);

                fs::rename(file_path / "old.txt", fs::path("other.txt") / "new.txt" );
                fs::rename(file_path / "dir1", fs::path("other.txt") / "dir2/dir1_moved");

                fs::copy(
                    file_path, fs::path("other/files"),
                    fs::copy_options::overwrite_existing 
                );
                for (const auto& file: fs::directory_iterator(file_path)) {
                    const fs::path& path = file.path();
                }

                for(const auto& file_rec: fs::recursive_directory_iterator(file_path)) {\
                    const fs::path& path = file_rec.path();
                }

                // nadawanie uprawnień
                auto status = fs::status(file_path);
                fs::permissions(
                    file_path, 
                    fs::perms::owner_read | fs::perms::owner_write,
                    fs::perm_options::add
                );
            }

            void FileSystemManagment::get_file_from_resources() {
                try {
                    auto path = resource_path("scores.txt");
                    logger.info() << "Config path: " << path << ENDL; 
                    std::string loaded_text = load_text("scores.txt");
                    logger.info() << "Config path text: " << loaded_text<< ENDL; 
                }
                catch (const std::exception& ex) {
                    logger.error() << "Error while reading resources: " << ex.what() << ENDL; 
                }
            }
        
        #pragma endregion FILE_SYSTEM_MANAGEMENT_CLASS
    }
    #pragma endregion STREAMS_MANAGEMENT
    /*---------------------------------------------------------------------------------------*/
    #pragma region ALIASES_AND_TYPES
    namespace AliasesAndTypes {

        #pragma region ALIASES_PLAYGROUND_CLASS
        
            void AliasesPlayground::basic_aliases() {
                logger.info() << "BASIC ALIASES" << ENDL;
                typedef unsigned long int UL_int;
                using Ldouble = long double;
                using Callback = void(*)(int);
                UL_int bts_id = 1256125;
                Ldouble meta_numb = 512.512095102518260166;
                Callback cb = [](int x) {
                    logger.debug() << "Callback called with x = " << x << ENDL;
                };

                logger.debug() 
                    << "UL_int bts_id = " << bts_id << ENDL
                    << "Ldouble meta_numb = " << meta_numb << ENDL;

                cb(12);
            }
            
            void AliasesPlayground::template_aliases() {
                logger.info() << "TEMPLATE ALIASES" << ENDL;
                TypeVec<int> numbers{1,5,612,26};
                StringMap<double> factors{
                    {"pi", 3.51251},
                    {"e", 2.61241}
                };
                logger.debug() << "TypeVec<int> numbers:" << ENDL;
                for (int numb : numbers) {
                    logger.debug() << "  " << numb << ENDL;
                }

                logger.debug() << "StringMap<double> factors:" << ENDL;
                for (const auto& [key, value]: factors) {
                    logger.debug() << " " << key << "-" << value << ENDL;
                }
            }
            
            void AliasesPlayground::strong_types() {
                logger.info() << "STRONG TYPES" << ENDL;
                UserIdAlias id1 = 10;
                UserIdAlias id2 = 20;

                UserId strong1{10};
                UserId strong2{20};

                logger.debug()
                    << "UserIdAlias u1 = " << id1 << ENDL
                    << "UserIdAlias u2 = " << id2 << ENDL
                    << "UserId strong1.value = " << strong1.value << ENDL
                    << "UserId strong2.value = " << strong2.value << ENDL;
            }
        
            void AliasesPlayground::play_with_variant_save_union() {
                logger.info() << "VARIANT PLAYGROUND" << ENDL; 
                std::variant<std::string, int, double> values;
                bool holds_integer = std::holds_alternative<int>(values);
                int variant_index = values.index();
                values = 1;
                logger.debug() << 
                    "Does hold it integer " << std::boolalpha << holds_integer << ENDL;
                if (holds_integer) {
                    logger.debug() 
                        << "Variant holds int type, which is index nr" << variant_index << ENDL
                        << "Value of integer is" <<  std::get<int>(values) << ENDL;
                    if (auto val = std::get_if<std::string>(&values)) {
                        logger.debug() << *val;
                    }
                }
                std::visit(
                    [](auto&& value) {
                        logger.info() << "Received from variant: " << value << ENDL; 
                    },
                    values
                );
            }

            void AliasesPlayground::play_with_optional() {
                std::optional<int> numb = 42;
                std::optional<int> other = std::nullopt;
                bool has_numb_value = numb.has_value();
                if (has_numb_value) {
                    logger.info()
                        << "Value via .value(): " << numb.value() << ENDL
                        << "Value via *numb   : " << *numb << ENDL;
                }
                int number = numb.value_or(-1);
                logger.info() << "Number (value_or): " << number << ENDL;
                numb.reset();
                numb.emplace(51);
            }
        
        #pragma endregion ALIASES_PLAYGROUND_CLASS
        /*---------------------------------------------------------------------------------------*/
        #pragma region CASTING_PLAYGROUND_CLASS
        
            void CastingPlayground::implicit_conversion() {
                double pi_double = 3.14562;
                int converted_pi = pi_double;
                logger.debug()
                    << "Implicit convert: "<<  converted_pi << ENDL;
            }

            void CastingPlayground::convert_static_cast() {
                double var = 3.1561261;
                int static_var = static_cast<int>(var); 
                logger.debug()
                    << "Static convert: "<<  static_var << ENDL;
            }

            void CastingPlayground::convert_const_cast(const int* value) {
                int* pointer = const_cast<int*>(value);
                *pointer = 99; // nie polecane, ale możliwe
                logger.debug()
                    << *pointer << ENDL;
            }

            void CastingPlayground::convert_reinterpret_cast() {
                int value = 65;
                char* ptr = reinterpret_cast<char*>(&value);
                logger.debug()
                    << *ptr << ENDL;
            }

            void CastingPlayground::convert_dynamic_cast() {
                Base* base = new Derived;
                Derived* derived = dynamic_cast<Derived*>(base);
                if (derived) {
                    derived->say();
                }
            }

        #pragma endregion CASTING_PLAYGROUND_CLASS
        /*---------------------------------------------------------------------------------------*/
        #pragma region POINTERS_PLAYGROUND_CLASS
        
            void PointersPlayground::basic_pointer() {
                /*  numb = wartosc 
                    ptr - adres pamieci
                    *ptr - dereferencja - idz pod adres i wex wartosc
                    -> to to samo co (*pointer).metoda()
                */
                int numb = 412;
                int* numb_ptr = &numb; // &adres
                logger.debug() << "Numb " << numb << ENDL;
                logger.debug() << "Numb address " << numb_ptr << ENDL;
                *numb_ptr = 100;
                logger.debug() << "Dereference after chage: " << *numb_ptr << ENDL;
            }

            void PointersPlayground::pointer_to_structure() {
                Person woman(21);
                Person* struct_ptr = &woman;
                struct_ptr->introduce();
            }

            void PointersPlayground::allocate_memory_dynamic() {
                int* ptr = new int(10); // tworzy int w pamieci
                logger.debug() << *ptr << ENDL;
                delete ptr;
            }

            void PointersPlayground::unique_pointer() {
                std::unique_ptr<Person> marek = 
                    std::make_unique<Person>(51);
                logger.debug()
                    << "Person " << marek->_age << " is doing something" << ENDL;
                // auto f2 = marek; compilation fail
                auto f2 = std::move(marek);
            }
    
            void PointersPlayground::shared_pointer() {
                std::shared_ptr<Connection> sql_db, mongo_db;
                sql_db = std::make_shared<Connection>();
                sql_db->name = "SQL db";
                sql_db->accounts = 1;
                mongo_db = sql_db; // współdzielenie jednego obiektu
                mongo_db->accounts = 2;
                logger.debug()
                    << "Mongo db: " << mongo_db->name << ENDL
                    << "SQL amount: " << sql_db->accounts << ENDL
                    << "Using the connection" << ENDL;
            }

        #pragma endregion POINTERS_PLAYGROUND_MCLASS        /*---------------------------------------------------------------------------------------*/
        /*---------------------------------------------------------------------------------------*/
        #pragma region ENUMS_PLAYGROUND_NAMESPACE
        namespace Enums {

            #pragma region ENUMS_PLAYGROUND_CLASS
                
                std::string EnumPlayground::request_method_to_string(RequestMethod method) {
                    switch (method) {
                        case RequestMethod::GET:    return "GET";
                        case RequestMethod::POST:   return "POST";
                        case RequestMethod::DELETE: return "DELETE";
                        default:                    return "UNKNOWN";
                    }
                }

                std::optional<RequestMethod> EnumPlayground::string_to_request_method(const std::string& method_str) {
                    if (method_str == "GET")    return  RequestMethod::GET;
                    if (method_str == "POST")   return  RequestMethod::POST; 
                    if (method_str == "DELETE") return  RequestMethod::DELETE;
                    return std::nullopt;
                }
                
                void EnumPlayground::basic_enum_attribute_check() {
                    logger.info() << "[Basic enum attribute check]" << ENDL;
                    Status well = WARNING;
                    Status status_by_number = (Status)100;
                    if (well == ERROR || status_by_number == ERROR)
                        logger.debug()
                            << "There occurs an error" << ENDL;
                    else
                        logger.debug()
                            << "Value: " << well 
                            << " and its ok" << ENDL;
                    // są konflikty z innymi
                }
                
                void EnumPlayground::enum_class_value_retrieval() {
                    logger.info() << "[Enum class value retrieval]" << ENDL;
                    RequestMethod method = RequestMethod::GET;
                    int method_code = static_cast<int>(method);
                    logger.debug() 
                        << "Request method code: " 
                            << method_code << ENDL;
                }
                
                void EnumPlayground::enum_class_hex_attribute_value() {
                    logger.info() << "[Class hex value]" << ENDL;
                    Color color = Color::GREEN;
                    logger.debug() 
                        << "Hex color: "
                        << std::hex << static_cast<uint8_t>(color) 
                        << ENDL;
                }

                void EnumPlayground::enum_as_vector_type_iteration() {
                    logger.info() << "[Vector<Enum type> iteration]" << ENDL;
                    constexpr std::array<RequestMethod, 3> all_requests = {
                        RequestMethod::GET,
                        RequestMethod::DELETE,
                        RequestMethod::POST
                    };
                    for (auto request: all_requests) {
                        logger.debug() 
                            << "Request: (int) " << static_cast<int>(request)
                            << ", As (string) " << request_method_to_string(request)
                            << ENDL;
                    }
                }

                void EnumPlayground::mapping_enum_to_string() {
                    logger.info() << "[Mapping enum]" << ENDL;
                    RequestMethod method = RequestMethod::GET;
                    std::string method_str = request_method_to_string(method);
                    logger.info()
                        << "Converted method to string: " << method_str
                        << ENDL;
                    RequestMethod get_method = RequestMethod::GET;
                    auto mapped_from_string = string_to_request_method(method_str);
                    if (mapped_from_string != std::nullopt) {
                        RequestMethod mapped_value = mapped_from_string.value();
                        logger.debug() << "Method: " << static_cast<int>(mapped_value) << ENDL;
                    }
                }
                
            #pragma endregion ENUMS_PLAYGROUND_CLASS
        }
        #pragma endregion ENUMS_PLAYGROUND_NAMESPACE
        /*---------------------------------------------------------------------------------------*/
        #pragma region TEMPLATES_PLAYGROUND_NAMESPACE
        namespace Templates {

            #pragma region TEMPLATES_PLAYGROUND_CLASS

                void TemplatePlayground::basic_redundancy_difference() {
                    logger.debug() << "[Templates] basic_redundancy_difference()" << ENDL;
                    //  zduplikowane podejście - dwie osobne funkcje do dodawanie
                    int sum_int = add_int(1,1);
                    double sum_double = add_double(1.5, 1.5);
                    logger.debug()
                        << "add_int(1, 1) = " << sum_int << ENDL
                        << "add_double(1.5, 1.5) = " << sum_double << ENDL;

                    // z użyciem templata
                    int generic_int = generic_add(1,2);
                    double generic_double = generic_add(1.5, 15.7);
                    std::string generic_string = generic_add(
                        std::string("Hi "), std::string("there")
                    );
                    logger.debug()
                        << "generic_add<int>(1, 2) = " << generic_int << ENDL
                        << "generic_add<double>(1.5, 15.7) = " << generic_double << ENDL
                        << "generic_add<std::string>(\"Hi \", \"there\") = "
                        << generic_string << ENDL;
                }

                void TemplatePlayground::template_functions() {
                    logger.info() << "[Templates] template_functions" << ENDL; 
                    /*  automatyczna dedukacja typu - int
                        jawne typowanie <typ>*/
                    auto bigger = max_of(5, 9); 
                    auto longer = max_of<std::string>("his", "yo");
                    logger.debug()
                        << "max_of(5, 9) = " << bigger << ENDL
                        << "max_of<string>(\"his\", \"yo\") = " << longer << ENDL;
                    
                    auto different_types = add_different(12.51, 125);
                    logger.debug()
                        << "add_different(12, 515.5125) = " << different_types << ENDL;
                }
                
                void TemplatePlayground::template_classes() {
                    logger.info() << "[Templates] classes: " << ENDL;
                    GenericBox<int> health(100);
                    GenericBox<double> accuracy(51.5);
                    GenericBox<std::string> nickname("Johny");
                    logger.debug() 
                        << "HP: ["   << health.get()   << "] | "
                        << "ACC: ["  << accuracy.get() << "] | " 
                        << "Nick: [" << nickname.get() << "] " << ENDL;
                    // Para typów generycznych
                    GenericPair<std::string, int> player_score("Golo", 125);
                    logger.debug() 
                        << "Key: "   << player_score.get_key() << ": " 
                        << "Value: " << player_score.get_value() << ENDL;
                }

                void TemplatePlayground::template_as_vector_type() {
                    logger.debug() << "[Templates] template_as_vector_type " << ENDL;
                    GenericItemsContainer<int> numbers(5);
                    numbers.add(10);
                    numbers.add(1256);
                    logger.debug() << "All numbers reserved:" << ENDL;
                    numbers.print_all_items();
                    GenericItemsContainer<int> numbers_inicialized{10, 1256};
                    logger.debug() << "Numbers initialized:" << ENDL;
                    numbers_inicialized.print_all_items();
                    logger.debug() << "Numbers filled with zeros:" << ENDL;
                    GenericItemsContainer<int> filled_zeros(3, 0);
                    filled_zeros.print_all_items();

                    logger.debug()
                        << "Active containers: "
                        << GenericItemsContainer<int>::get_active_containers() << ENDL;
                }
            
            #pragma endregion TEMPLATES_PLAYGROUND_CLASS
        }
        #pragma endregion TEMPLATES_PLAYGROUND_NAMESPACE
    }
    #pragma endregion ALIASES_AND_TYPES
    /*---------------------------------------------------------------------------------------*/
    #pragma region NAMESPACES_KNOWLEDGE
    namespace NameSpacesKnow {

        #pragma region NAMESPACES_OBJECTS
            
            namespace Begin{
                void print() {
                    logger.debug() << "Namespace Begin " << ENDL;
                }
            }
            
            namespace End{
                void print() {
                    logger.debug() << "Namespace End " << ENDL;
                }
            }

            void Out::Inner::read() { 
                logger.debug() << "Reading in Inner" << ENDL;
            }

            void Out::Inner::write() {
                logger.debug() << "Writing in Inner" << ENDL;
            }

            struct API::Vector_v1{
                float x;
                float y;
            };

            void API::append_list(Vector_v1 vector) {
                logger.debug() << "Appending to list from inline" << ENDL;
            }

            class API::v2::Vector_v2 {
                float x;
                float y;
                public:
                    float get_x() {
                        return x;
                    }
                    float get_y() {
                        return y;
                    }
            };

            void API::v2::append_list(Vector_v2 vector) {
                logger.debug() << "Appending to list from api v2" << ENDL;
            }

        #pragma endregion NAMESPACES_OBJECTS
    }
    #pragma endregion NAMESPACES_KNOWLEDGE
    /*---------------------------------------------------------------------------------------*/
    #pragma region COMPILE_TIME_NAMESPACE
    namespace CompileTime {

        #pragma region COMPILE_TIME_PLAYGROUND
        
            void CompilePlayground::compile_time_basic_definition() {
                logger.info() << "[COMPILE BASICS]" << ENDL;
                //  constexpr vs c const 
                const int const_value = 512;
                logger.debug()
                    << "const int value: " << const_value << ENDL;
                    // << wartosc nie zmienna, ale nie w comple time

                constexpr int board_number = 125;
                constexpr std::array<int, 4> numbers {
                    151, 625, 5125, board_number 
                }; 
                logger.debug() 
                    << "constexpr int board_number" << board_number ; 

                for (auto& numb: numbers) {
                    logger.debug()
                        << "Value from compile numbers: " << numb << ENDL;
                }
                // mogą działać w runtime
                int x = 561226;
                int runtime_sum = board_number + x;
                logger.debug()
                    << "runtime_sum = board_number + x = " << runtime_sum << ENDL;
            }
            
            void CompilePlayground::compile_time_functions() {
                logger.info() << "[COMPILE TIME FUNCTIONS ]" << ENDL;
                constexpr int fac_result_ct = factorial(12);
                logger.debug() 
                    << "constexpr func factorial(5): "
                    << fac_result_ct << ENDL;
                int run_time_value = 51;
                int fac_result_rt = factorial(run_time_value);
                logger.debug()
                    << "constexpr func factorial(rt_value): "
                    << fac_result_rt << ENDL;
            }
            
            void CompilePlayground::only_compile_time_functions() {
                logger.info() << "[CONSTEVAL FUNCTIONS]" << ENDL;
                #if __cplusplus >= 202002L // C++ 20
                    constexpr int id = make_id(51);
                    int x = 5;
                    // int id_rt = make_id(x); // nie, bo wymaga ct value 
                    logger.debug()
                        << "constexpr make_id(7): "
                        << id << ENDL;
                #endif
            }
            
            void CompilePlayground::only_compile_time_inicialization() {
                logger.info() << "[CONSTINIT EXPLANATION]" << ENDL;
                #if __cplusplus >= 202002L
                    logger.debug() <<
                        "Var counter already inicialized in ct: "
                        << GLOBAL_COUNTER << ENDL;
                    // moze byc zmienialna
                    GLOBAL_COUNTER++;
                    logger.debug()
                        << "Po zmianie: "
                        << GLOBAL_COUNTER << ENDL;
                #endif
            }
            
            void CompilePlayground::compile_time_in_classes() {
                logger.info() << "[CONSTEXPR IN CLASSES]" << ENDL;
                constexpr Point p1(3, 4);            // compile-time obiekt
                constexpr int len = p1.length_squared(); // compile-time obliczenie
                logger.debug()
                    << "compile time point length: "
                    << len << ENDL;

                // --- runtime obiekt ---
                int a = 5;
                Point p2(a, 10);     // runtime konstrukcja
                int len2 = p2.length_squared(); // runtime wywołanie
                logger.debug()
                    << "run time point length: "
                    <<  len2 << ENDL;

            }

        #pragma endregion COMPILE_TIME_PLAYGROUND
    }
    #pragma endregion COMPILE_TIME_NAMESPACE
    /*---------------------------------------------------------------------------------------*/
    #pragma region PREPROCESSOR_NAMESPACE
    namespace Preprocesor {

        #pragma region PREPROCESSOR_METHODS
        
            double circle_area(double radius) {
                return PI * radius * radius; 
            }

            void all() {
                double area = circle_area(5);
                logger.debug() << "Area: " << area << ENDL;
                // usage of SQUARE macro
                logger.debug() << SQUARE(4) << ENDL;
                LOG("Program startuje!");
            }
        
        #pragma endregion PREPROCESSOR_METHODS
    }
    #pragma endregion PREPROCESSOR_NAMESPACE
    /*---------------------------------------------------------------------------------------*/
    #pragma region CLASS_KNOWLEDGE_NAMESPACE
    namespace ClassKnow {

        #pragma region SPECIFICATORS_NAMESPACE
        namespace Specificators {

            #pragma region PRIVATE_SPECIFICATOR_CLASS
            
                void PrivateSpecificator::start() {
                    velocity = 50; // this.velocity
                }

                void PrivateSpecificator::compare(const PrivateSpecificator& diff) {
                    logger.debug() 
                        << "Comparing: [" << velocity - diff.velocity 
                        << "]" << ENDL;  
                    velocity = diff.velocity;
                }
                
                void SpecificatorPlayground::private_spec_introduce() {
                    logger.info() << "[PRIVATE SPECIFICATOR]" << ENDL;
                    PrivateSpecificator priv_spec_a, priv_spec_b;
                    priv_spec_a.start();
                    logger.debug()
                        << "Bład Kompilacji jesli próbujemy"
                        << " dostać sie do atrybutu klasy " << ENDL;
                    /*
                        Błąd kompilacji, nie można dostać się do prywatnego atrybutu
                        second.velocity = 12;  
                    */
                    priv_spec_a.compare(priv_spec_b);
                }

            #pragma endregion PRIVATE_SPECIFICATOR_CLASS
            /*---------------------------------------------------------------------------------------*/
            #pragma region PUBLIC_SPECIFICATOR_CLASS
            
                void PublicSpecificator::set_and_show() {
                    scores = 51.2;
                    logger.info() << "Scores: " << scores << ENDL;
                }
            
                void SpecificatorPlayground::public_spec_introduce() {
                    logger.info() << "[PUBLIC SPECIFICATOR]" << ENDL;
                    PublicSpecificator allowed;
                    allowed.set_and_show();
                    allowed.scores = 12.5;
                    logger.debug() 
                        << "Dostep do wszystkich metod i pól klasy" << ENDL;
                }

            #pragma endregion PUBLIC_SPECIFICATOR_CLASS
            /*---------------------------------------------------------------------------------------*/
            #pragma region PROTECTED_SPECIFICATOR_CLASS

                void ProtectedSpecificator::show_shield() const {
                    logger.debug() << "Shield value: " << shield << ENDL;
                }

                void ProtectedChild::damage() {
                    shield -= 10; // has access
                    show_shield(); // has access
                }
                
                void SpecificatorPlayground::protected_spec_introduce() {
                    logger.info() << "[PROTECTED SPECIFICATOR]" << ENDL;
                    ProtectedSpecificator family;
                    family.show_shield();
                    ProtectedChild child;
                    child.damage();
                    logger.debug() 
                        << "Dostep do pól przez klasy dziedziczące " << ENDL;
                    // child.shield -= 10;  jak z private, błąd komplacji
                }

            #pragma endregion PROTECTED_SPECIFICATOR_CLASS
        }
        #pragma endregion SPECIFICATORS_NAMESPACE
    /*---------------------------------------------------------------------------------------*/
        #pragma region LIFE_CYCLE_NAMESPACE
        namespace LifeCycle {

            #pragma region CONSTRUCTOR_CLASS
                
                Constructor::Constructor() {
                    _name = "none";
                    logger.info() << "Default object created" << ENDL;
                }

                Constructor::Constructor(std::string name) {
                    _name = name;
                    logger.info() 
                        << "Object with " << name << " name created" << ENDL;
                }

                Constructor::Constructor(std::string name, int threshold)
                    : _name(name), _threshold(threshold) {
                    logger.info() 
                        << "Object inicialized with list (" 
                        << name << ", " 
                        << threshold <<  " params created" << ENDL;
                }

                void Constructor::introduce() {
                    logger.debug()
                        << "Constructor attributes: ["
                        << _name << ", "
                        << _threshold << "]" << ENDL;
                }

            #pragma endregion CONSTRUCTOR_CLASS
            /*---------------------------------------------------------------------------------------*/
            #pragma region DESTRUCTOR_CLASS
                
                Destructor::Destructor() {
                    _notes_file_hook.open("notes.txt");
                    if (!_notes_file_hook) {
                        std::cerr << "Cannot open notes.txt file" << ENDL;
                        return;
                    }
                    else{
                        logger.info() << "Hook to file notes.txt applicated" << ENDL;
                    }
                }

                Destructor::Destructor(std::string path) {
                    _notes_file_hook.open(path);
                    if (!_notes_file_hook) {
                        std::cerr << "Cannot open " << path << "path" << ENDL;
                        return;
                    }
                    else{
                        logger.info() << "Hook to file " << path << "applicated" << ENDL;
                    }
                }

                Destructor::~Destructor() {
                    if(_notes_file_hook.is_open()) {
                        _notes_file_hook.close();
                        logger.info() << "Hook closed properly" << ENDL;
                    }
                    logger.debug() << "Hook deleted" << ENDL;
                }

            #pragma endregion DESTRUCTOR_CLASS
            /*---------------------------------------------------------------------------------------*/
            #pragma region LIFE_CYCLE_PLAYGROUND_CLASS
                
                void LifeCyclePlayground::basic_constructor() {
                    logger.info() << "[CONSTRUCTOR INTRODUCTION]" << ENDL;
                    Constructor default_one;
                    Constructor with_parameter("Pretty");
                    Constructor inicialized_list("Not bad", 15);
                    default_one.introduce();
                    with_parameter.introduce();
                    inicialized_list.introduce();
                }

                void LifeCyclePlayground::basic_destructor() {
                    logger.info() << "[DESTRUCTOR INTRODUCTION]" << ENDL;
                    Destructor destructor;
                    Destructor destructor_with_param("other.json");
                    logger.debug()
                        << "Destroy object after reach the score" << ENDL;
                }

            #pragma endregion LIFE_CYCLE_PLAYGROUND_CLASS
        }
        #pragma endregion LIFE_CYCLE_NAMESPACE
        /*---------------------------------------------------------------------------------------*/
        #pragma region GETTERS_AND_SETTERS_NAMESPACE
        namespace GettersAndSetters {

            #pragma region ACCESS_GATES_CLASS
                
                AccessGates::AccessGates(int amount, int item) {
                    if (amount < 0) {
                        throw std::invalid_argument(
                            "Amount of vector elements cannot be negative"
                        );
                    }
                    _amount = amount;
                    _gates.resize(_amount);
                    _gates.push_back(item); 
                }

                int AccessGates::get_amount() const {
                    return _amount;
                }

                std::vector<int> AccessGates::get_gates() const {
                    return _gates;
                }

                void AccessGates::set_amount(int new_amount) {
                    if (new_amount < 0) {
                        std::cerr << "Vector cannot have negative amount of elements" << ENDL;
                        return;
                    }
                    _amount = new_amount;
                    _gates.resize(_amount);
                }

                void AccessGates::set_gates(std::vector<int>& new_gates) {
                    _gates.resize(new_gates.size()); // dospasowanie rozmiaru
                    for (std::size_t id = 0; id < new_gates.size(); id++) {
                        try{
                            // raise Exception if not have index
                            _gates.at(id) = new_gates.at(id); 
                        }
                        catch(const std::out_of_range& range_exception) {
                            std::cerr << "Element " << new_gates.at(id) << " has index out of range" << ENDL;
                            logger.error() << "Exception " << range_exception.what() << ENDL;
                        }
                    }
                }

                void demonstrate_gates() {
                    logger.debug() << "[Getters & Setters INTRODUCTION]" << ENDL;
                    AccessGates gates(5, 12);
                    logger.debug() 
                        << "Gates amount: " << gates.get_amount() << ENDL
                        << "Size of gates: " << gates.get_gates().size() << ENDL;
                    gates.set_amount(15);
                    std::vector<int> new_gates{15, 62, 73, 21};
                    gates.set_gates(new_gates);
                    logger.debug() 
                        << "Gates item: " << gates.get_gates().at(1) << ENDL;
                }

            #pragma endregion ACCESS_GATES_CLASS
        }
        #pragma endregion GETTERS_AND_SETTERS_NAMESPACE
        /*---------------------------------------------------------------------------------------*/
        #pragma region STRUCTURES_NAMESPACE
        namespace Structures {

            #pragma region STRUCTURES_PLAYGROUND

                void Employee::print() const {
                    logger.debug() << name 
                        << " (" << age << " lat) - " 
                        << salary << " PLN" << ENDL;
                }

                Employee::Employee(std::string name, int age, double salary)
                  : name(std::move(name)), age(age), salary(salary) {
                    logger.debug() 
                        << "Employee ["   << name   << ", " << age    << ", " 
                        << salary << ", " << "] - created successfully" << ENDL;
                }
            
                void Stats::show_stats() const {
                    logger.debug() 
                        << "Stats: [HP: " << hp
                        << " | ATK: " << attack
                        << " | DEF: " << defense << "]" << ENDL;
                }

                void Player::introduce() const {
                    logger.debug() 
                        << "Player: " << name 
                        << " (lvl " << level << ")" << ENDL;
                    stats.show_stats();
                }

                void StructuresPlayground::creation_ways() {
                    logger.info() << "[Structure creation]" << ENDL;
                    Employee default_one;
                    // mamy dostep wiec możemy ustawiać wartości
                    default_one.name = "default_one";
                    default_one.age = 31;
                    default_one.salary = 512612.55;
                    logger.info() 
                        << "Employee " << default_one.name 
                        << " earns " << default_one.salary << " PLN" << ENDL;
                    // poprzez liste inicjalizacyjną
                    Employee list_init{"Mark", 53, 4666.66};
                    list_init.print();
                    // braced initialization
                    Employee braced_init = {"Basia", 22, 7200.0};
                    braced_init.print();
                    // z konstruktorem
                    Employee with_constructor("John", 21, 215.22);
                    with_constructor.print();
                }
            
                void StructuresPlayground::nested_structs() {
                    logger.info() << "[NEsted Structures]" << ENDL;
                    // zagnieżdżone struktury
                    Stats base_stats{100, 25, 10};
                    Player mage{"Lord", 7, base_stats};
                    // inicjalizacja pojedyncza 
                    Player warior{"Odyn",7, {120, 40, 15}};
                    mage.introduce();
                    warior.introduce();
                    mage.stats.hp = 50; // zmiana statystyk
                    mage.stats.show_stats();
                }

            #pragma endregion STRUCTURES_PLAYGROUND
        }
        #pragma endregion STRUCTURES_NAMESPACE
        /*---------------------------------------------------------------------------------------*/
        #pragma region INHERITANCE_NAMESPACE
        namespace Inheritance {

            #pragma region INHERITANCE_CLASSES

                Animal::Animal(int legs)
                    : _legs(legs) {
                    logger.debug() << "Animal created" << ENDL;
                }

                Dog::Dog() : Animal(4) {
                    // default value for base construct
                    _name = "Burek";
                    logger.debug() 
                        << "Default dog created" << ENDL;
                }

                Dog::Dog(std::string name)
                    : Animal(4), _name(std::move(name))  {
                    logger.debug() 
                        << "Regular dog created" << ENDL;
                }

                Dog::Dog(int legs, std::string name)
                    : Animal(legs), _name(std::move(name)) {
                    logger.debug() 
                        << "Dog with amount of legs" << ENDL;
                }

                void Dog::introduce() {
                    logger.debug() 
                        << "Dog " << _name 
                        << ", legs: " << count_legs() << ENDL; 
                }
            
                void inheritance_introduction() {
                    logger.info() << "[INHERITANCE INTRODUCTION]" << ENDL;
                    Inheritance::Dog burek;
                    burek.introduce();    
                    Inheritance::Dog drago("Drago");
                    drago.introduce();       
                    Inheritance::Dog diff(3, "Damaged");
                    diff.introduce();
                }
                
            #pragma endregion INHERITANCE_CLASSES
        }
        #pragma endregion INHERITANCE_NAMESPACE
        /*---------------------------------------------------------------------------------------*/
        #pragma region POLIMORPHISM_NAMESPACE
        namespace Polymorphism {
            
            #pragma region POLIMORPHIS_CLASSES_AND_INTERFACES

                void broadcast(const Notifications& notifications, const std::string& message) {
                    for (const auto& notify: notifications) {
                        notify->send(message);
                    }
                }

                void pipeline(
                    const std::vector<std::unique_ptr<IProcessor>>& steps,
                    const std::string& input_text)
                {
                    for (const auto& step: steps) {
                        step->process(input_text);
                    }
                }

                void show_polymorphism() {
                    logger.debug() << "[Polymorhpysm INTROCUTION]" << ENDL;
                    Notifications notifications;
                    notifications.push_back(
                        std::make_unique<EmailNotification>("golo338@gmail.com")
                    );
                    notifications.push_back(
                        std::make_unique<SmsNotification>("golo338@gmail.com")
                    );
                    logger.debug()
                        << "Brodcast is starting" << ENDL;
                    broadcast(notifications, "Senor, como esta uested?");
                    // --------------
                    logger.debug()
                        << "Interface pipeline started:" << ENDL;
                    std::vector<std::unique_ptr<IProcessor>> steps;
                    steps.push_back(std::make_unique<Compressor>());
                    steps.push_back(std::make_unique<Encryptor>());
                    steps.push_back(std::make_unique<Logger>());

                    pipeline(steps, "Confidential data");
                }
            
            #pragma endregion POLIMORPHIS_CLASSES_AND_INTERFACES
        }
        #pragma endregion POLIMORPHISM_NAMESPACE
    }
    #pragma endregion CLASS_KNOWLEDGE_NAMESPACE
    /*---------------------------------------------------------------------------------------*/
    #pragma region EXCEPTIONS_KNOWLEDGE_NAMESPACE
    namespace ExceptionsKnow {
        #pragma region EXCEPTIONS_PLAYGROUND_CLASS

            ExceptionHandling::ExceptionHandling(int arg) : _arg(arg) {
                throwing_one();
            }

            CustomWithFields::CustomWithFields(
                std::string message,
                int code,
                std::string function,
                std::string file_name,
                int line
            ): _message(std::move(message)), _code(code), 
                _file(std::move(file_name)), _line(line)
            {
                std::ostringstream exception_message; // bufor do wiadomosci
                exception_message 
                    << "[Code: " << _code << " ]" << ENDL
                    << "[Message (" << _message << ")" 
                    << " called in function " << _function
                    << "() in file" << _file << " at line " << _line << ENDL;
                    
                _what = exception_message.str();
            }

            void ExceptionHandling::throwing_one() {
                if (_arg < 0) {
                    throw std::invalid_argument("Arg must be >= 0");
                }
                else if (_arg == 5) {
                    throw CustomException("Should not be 5");
                }
                else {
                    THROW_CUSTOM("Other exception type", 1111);
                }
            }
            
            void ExceptionPlayground::simple_throw() {
                logger.debug() 
                    << "Forced Invalid Argument Exception: " << ENDL;
                try {
                    ExceptionHandling handling(-2);
                }
                catch(const std::invalid_argument& arg_err) {
                    logger.error() 
                        << "Argument error: " 
                            << arg_err.what() << ENDL;
                }
                catch(const std::exception& reg_err) {
                    logger.error() 
                        << "Other error: " 
                            << reg_err.what() << ENDL;
                }
                catch(...) {
                    logger.error() << "Unknown error" << ENDL;
                }
            }

            void ExceptionPlayground::custom_throw() {
                logger.debug() 
                    << "Custom Exception Handling: " << ENDL;
                try {
                    ExceptionHandling handling_custom(5);
                }
                catch(const CustomException::exception& custom_err) {
                    logger.error() << "Custom error: " << custom_err.what() << ENDL;
                }
            }

            void ExceptionPlayground::custom_with_specific_message() {
                try {
                    ExceptionHandling handling_custom(12);
                }
                catch(const CustomWithFields& custom_adv_err) {
                    logger.error() << "Custom error: " << custom_adv_err.what() << ENDL;
                }
        }
        
        #pragma endregion EXCEPTIONS_PLAYGROUND_CLASS
    }
    #pragma endregion EXCEPTIONS_KNOWLEDGE_NAMESPACE
    /*---------------------------------------------------------------------------------------*/
    #pragma region STRING_KNOWLEDGE_NAMESPACE
    namespace StringKnow {

        #pragma region STRING_OPERATION_CLASS

            StringOperation::StringOperation(std::string base)
                : base_text(base) {}
        
            void StringOperation::access_string_attributes() {
                logger.info() << "[Access to strings]" << ENDL;
                int word_buffor_size = base_text.size();
                int word_length = base_text.length();
                bool is_word_empty = base_text.empty();
                char first_word_sign = base_text.front();
                const char* inner_buffor_pointer = base_text.data();
                const char* save_ended_with_null = base_text.c_str();
                logger.debug()
                    << "Buffor size: "    << word_buffor_size     << ENDL
                    << "Word Length: "    << word_length          << ENDL
                    << "Is text empty: "  << is_word_empty        << ENDL
                    << "String index: "   << base_text[0]         << ENDL
                    << "First char/id: "  << first_word_sign      << ENDL
                    << "Last char/id: "   << base_text.back()     << ENDL
                    << "Inner pointer: "  << inner_buffor_pointer << ENDL
                    << "Sav=ly ended:"    << inner_buffor_pointer << ENDL;
                
                // formatowanie +20
                #if __has_include(<format>) && __cplusplus >= 202002L
                    #include <format>
                    std::string message = std::format("{} {}", "data", "data");
                #endif
            }

            void StringOperation::modification_without_return() {
                logger.info() << "[String modification without return]" << ENDL;
                std::string backup = base_text;
                log_modification(
                    "push_back() dopisanie znaku na koncu",
                    backup,
                    [](std::string& str) { str.push_back('!'); }
                );
                log_modification(
                    "+= dodawanie słów do siebie",
                    backup,
                    [](std::string& str) { str += "and more | "; }
                );
                log_modification(
                    "append(str, 10) dodawanie ze sprecyzowaniem długości dodawanej",
                    backup,
                    [](std::string& str) { str.append("add at | the end", 10); }
                );
                log_modification(
                    "insert(str, 10), wrzucenie w dane miejsce",
                    backup,
                    [](std::string& str) { str.insert(5, "in the middle | "); }
                );
                log_modification(
                    "erase(0, 4), czyszczenie <od, do>",
                    backup,
                    [](std::string& str) { str.erase(0, 4); }
                );
                log_modification(
                    "replace(1, 5, str), podmiana fragmentu na innych",
                    backup,
                    [](std::string& str) { str.replace(1, 5, "some"); }
                );
            }

            void StringOperation::modification_with_return() {
                logger.info() << "[String modification with return]" << ENDL; 
                // base_text.clear();
                std::string str_fragment = base_text.substr(0, 5); 
                logger.debug() 
                    << "substr(from, to) bierze frament, wycina  i zwraca go:  "
                    << str_fragment << ENDL;
                std::string small_frgament = base_text.substr(4, 2);
                logger.debug() 
                    << "substr(4, 2): " << small_frgament << ENDL;
                
                std::string from_to_the_rest = base_text.substr(7);
                logger.debug()
                    << "substr(6), od do konca: " << from_to_the_rest << ENDL;

                base_text.reserve(256); // rezerwacja pamieci - zmienia capacity
                char a_sign = 'A';
                char lower_case = std::tolower(a_sign);
                char upper_case = std::toupper(lower_case);
            }

            void StringOperation::searching() {
                logger.info() << "[Searching inside string]" << ENDL;
                logger.debug()
                    << "find(char) zwraca pozycje wystapienia znaku" << ENDL;
                auto sign_position = base_text.find('=');
                if (sign_position != std::string::npos) {
                    std::string before_eq = base_text.substr(0, sign_position);            // [0, pos)
                    std::string after_eq  = base_text.substr(sign_position + 1);
                    logger.debug() 
                        << "Before sign: " << before_eq << ENDL
                        << "After sign: "  << after_eq << ENDL;
                }
                logger.debug()
                    << "find(char, nr) szuka znaku, ale od konkretnej pozycji" << ENDL;
                size_t dash_pos = base_text.find('-', 15);
                if (dash_pos != std::string::npos) {
                    logger.debug()
                        << "Found '-' at position: " << dash_pos << ENDL
                        << "Fragment from there: " << base_text.substr(dash_pos) << ENDL;
                } 
                logger.debug() << "Find variants:" << ENDL;
                size_t pos_from_end = base_text.rfind('='); 
                if (pos_from_end != std::string::npos) {
                    logger.debug()
                        << "Last = at position " << pos_from_end << ENDL
                        << "Tail after last '=':" << base_text.substr(pos_from_end + 1) << ENDL;
                }
                size_t first_set = base_text.find_first_of(",;=");
                if (first_set != std::string::npos) {
                    logger.debug()
                        << "First one of [',', ';', '='] at: " << first_set
                        << " (char: '" << base_text[first_set] << "')" << ENDL;
                }

                size_t first_not_ws = base_text.find_first_not_of("\r \n");
                if (first_not_ws != std::string::npos) {
                    logger.debug()
                        << "First non whitespace at: " << first_not_ws
                        << " (char: '" << base_text[first_not_ws] << "')" << ENDL;
                }
                // find_last_of | .find_last_not_of  tak samo tylko ostatni
                
                // boolean - true jesli zaczyna sie
                #if __cplusplus >= 202002L
                    bool starts_conf = base_text.starts_with("conf");
                    bool ends_yaml   = base_text.ends_with(".yaml");
                    logger.debug()
                        << "starts_with(conf): " << std::boolalpha << starts_conf << ENDL
                        << "ends_with(.yaml): "  << std::boolalpha << ends_yaml   << ENDL;
                #endif
                // base_text.contains("fig") 
            }

            void StringOperation::triming_white_spaces() {
                const std::string_view white_spaces_group = " \t\r\n";
                size_t left_position = base_text.find_first_not_of(white_spaces_group);
                size_t right_position = base_text.find_last_not_of(white_spaces_group);
                logger.info() << "Whitespace from left found in position: " << left_position << ENDL;
                logger.info() << "Whitespace from right found in position: " << right_position << ENDL;
                std::string_view left_trimmed_string = (
                    left_position == std::string_view::npos
                ) 
                    ? std::string_view{} 
                    : base_text.substr(left_position);
                std::string_view right_trimmed_string = (
                    right_position == std::string_view::npos
                )    
                    ? std::string_view{}
                    : base_text.substr(0, right_position + 1); 
                logger.info() << "Left trimmed: " << left_trimmed_string << ENDL;
                logger.info() << "Right trimmed: " << right_trimmed_string << ENDL;
            }

        #pragma endregion STRING_OPERATION_CLASS
    }
    #pragma endregion STRING_KNOWLEDGE_NAMESPACE
    /*---------------------------------------------------------------------------------------*/
    #pragma region REGEX_KNOWLEDGE_NAMESPACE
    namespace RegexKnowledge {

        #pragma region REGEX_PLAYGROUND_CLASS
        /* Klasy regexowe:
            Typy:
                regex - wzorzec, skompilowany regex
                smatch - dopasowanie do stringa
                cmatch - dopasowanie do c-stringa const char*
            Funkcje:
                regex_match  - sprawdza czy cały string pasuje do wzorca
                regex_search - szuka wzorca gdziekolwiek w stringu
                regex_replace - zamienia dopasowane fragment na innych text
        */

            void RegexPlayground::sign_classes() {
                /*
                | Wzorzec | Znaczenie                        | Przykład dopasowania |
                | ------- | -------------------------------- | -------------------- |
                | `\d`    | cyfra (0–9)                      | `5`, `3`, `0`        |
                | `\D`    | wszystko, co NIE jest cyfrą      | `a`, `_`, `#`        |
                | `\w`    | znak „słowa”: litera, cyfra, `_` | `A`, `z`, `5`, `_`   |
                | `\W`    | wszystko poza `\w`               | `-`, `?`, `/`        |
                | `\s`    | whitespace: spacja, tab, \n, \r  | `' '`, `\t`          |
                | `\S`    | nie-whitespace                   | `a`, `5`, `_`        |
                */
                logger.info() << dots << "[Regex sign classes]" << ENDL;
                std::string text = "User42 id=77";
                std::regex digits(R"(\d+)");
                if (std::regex_search(text, digits)) {
                    logger.debug() << "Found digits" << ENDL;
                }
                std::regex word_or_char(R"(\W+)");
                if (std::regex_search(text, word_or_char)) {
                    logger.debug() << "Found word characters" << ENDL;
                }
                std::regex white_spaces(R"(\s+)");
                if (std::regex_search(text, white_spaces)) {
                    logger.debug() << "Found whitespace" << ENDL;
                }
                
            }
        
            void RegexPlayground::anchors() {
                /*
                | Wzorzec | Znaczenie        |
                | ------- | ---------------- |
                | `^`     | początek stringa |
                | `$`     | koniec stringa   |
                */
                logger.info() << dots << "[Regex anchors]" << ENDL;
                std::string good = "HelloWorld";
                std::string bad  = "123Hello";

                std::regex starts_hello(R"(^Hello)");
                std::regex ends_world(R"(World$)");

                if (std::regex_match(good, starts_hello))
                    logger.debug() << "'good' starts with Hello" << ENDL;

                if (!std::regex_match(bad, starts_hello))
                    logger.debug() << "'bad' does NOT start with Hello" << ENDL;

                if (std::regex_match(good, ends_world))
                    logger.debug() << "'good' ends with World" << ENDL;
            }

            void RegexPlayground::qualifiers() {
                /*
                | Wzorzec | Znaczenie             |
                | ------- | --------------------- |
                | `*`     | 0 lub więcej          |
                | `+`     | 1 lub więcej          |
                | `?`     | 0 lub 1 (opcjonalnie) |
                | `{n}`   | dokładnie n razy      |
                | `{n,}`  | co najmniej n razy    |
                | `{n,m}` | od n do m razy        |
                */
                logger.info() << dots << "[Regex qualifiers]" << ENDL;
                std::regex zero_or_more(R"(go*)"); // g, go, goo, gooo
                std::regex one_or_more(R"(go+)");
                std::regex optional(R"(colou?r)"); // color OR colour

                std::string ex1 = "goooal";
                std::string ex2 = "color";
                std::string ex3 = "colour";

                if (std::regex_search(ex1, one_or_more))
                    logger.debug() << "Found 'go+' pattern" << ENDL;

                if (std::regex_search(ex2, optional))
                    logger.debug() << "'color' matches colour/ color variant" << ENDL;

                if (std::regex_search(ex3, optional))
                    logger.debug() << "'colour' matches colour/ color variant" << ENDL;

                // {n,m}
                std::regex exactly_three(R"(a{3})"); // exactly "aaa"
                if (std::regex_search("caaaab", exactly_three))
                    logger.debug() << "Found exactly 'aaa'" << ENDL;
            } 

            void RegexPlayground::groups_alternatives() {
                /*
                | Wzorzec     | Znaczenie                                   |                   |
                | ----------- | ------------------------------------------- | ----------------- |
                | `( ... )`   | grupa (możesz ją odwoływać jako `$1`, `$2`) |                   |
                | `a          | b`                                          | albo `a` albo `b` |
                | `(?: ... )` | grupa bez przechwytywania                   |                   |
                */
                logger.info() << dots << "[Regex groups & alternatives]" << ENDL;
                std::string people = "Jan:10, Ala:20, Olek:30";
                // ( ... ) – grupy przechwytywujące
                std::regex pair(R"((\w+):(\d+))");
                std::smatch m;
                if (std::regex_search(people, m, pair)) {
                    logger.debug()
                        << "Name: " << m[1] << ", score: " << m[2] << ENDL;
                }
                // Alternatywa: a|b|c
                std::regex alt(R"(Jan|Ala|Olek)");
                if (std::regex_search(people, alt))
                    logger.debug() << "Found name using alternation" << ENDL;
                // (?: ... ) – grupa bez przechwytywania
                std::regex noncap(R"((?:Jan|Ala):\d+)");
                if (std::regex_search(people, noncap))
                    logger.debug() << "Found using non-capturing group" << ENDL;
            }
            
            void RegexPlayground::signs_sets() {
                /*
                | Wzorzec  | Znaczenie               |
                | -------- | ----------------------- |
                | `[abc]`  | a LUB b LUB c           |
                | `[a-z]`  | małe litery a–z         |
                | `[A-Z]`  | wielkie litery          |
                | `[0-9]`  | tylko cyfry             |
                | `[^abc]` | wszystko oprócz a, b, c |
                */
                logger.info() << dots << "[Regex sign sets]" << ENDL;
                std::string sample = "FileA.txt";

                // [A-Z] – wielka litera A-Z
                std::regex capital(R"([A-Z])");
                if (std::regex_search(sample, capital))
                    logger.debug() << "Found capital letter" << ENDL;

                // [^abc] – znak nie będący a, b, c
                std::regex not_abc(R"([^abc])");
                if (std::regex_search("z", not_abc))
                    logger.debug() << "'z' is NOT a, b, or c" << ENDL;

                // [0-9] – cyfry
                std::regex digits(R"([0-9]+)");
                if (std::regex_search("Room42", digits))
                    logger.debug() << "Found digits in string" << ENDL;
            }
            
            void RegexPlayground::signs_escape() {
                /*
                    | Znak     | Musisz pisać |
                    | -------- | ------------ |
                    | `.`      | `\.`         |
                    | `*`      | `\*`         |
                    | `+`      | `\+`         |
                    | `?`      | `\?`         |
                    | `(`, `)` | `\(`, `\)`   |
                    | `{`, `}` | `\{`, `\}`   |
                    | `[`      | `\[`         |
                    | `\`      | `\\`         |
                */
                logger.info() << dots << "[Regex escaping]" << ENDL;
                std::string file = "config.yaml";

                // \. – literalna kropka
                std::regex ext(R"(\.yaml$)");
                if (std::regex_search(file, ext))
                    logger.debug() << "File ends with .yaml" << ENDL;

                // \+ – literalny plus
                std::regex plus(R"(\+)");
                if (std::regex_search("a+b", plus))
                    logger.debug() << "Found literal plus" << ENDL;

                // \? – literalny znak zapytania
                std::regex q(R"(\?)");
                if (std::regex_search("Is this ok?", q))
                    logger.debug() << "Found literal question mark" << ENDL;
            }

            void RegexPlayground::match() {
                logger.info() << dots << "[Regex FULL match]" << ENDL;
                // 1. Email – cały string musi pasować
                std::string email = "admin@example.com";
                std::regex email_pattern(R"(^\w+@\w+\.\w+$)");
                if (std::regex_match(email, email_pattern)) {
                    logger.debug() << "Email is valid" << ENDL;
                } else {
                    logger.debug() << "Invalid email format" << ENDL;
                }
                // 2. Data YYYY-MM-DD
                std::string date = "2025-12-02";
                std::regex date_pattern(R"(^\d{4}-\d{2}-\d{2}$)");

                if (std::regex_match(date, date_pattern)) {
                    logger.debug() << "Correct date format" << ENDL;
                }
                // 3. Tylko litery i cyfry
                std::string name = "User42";
                std::regex alnum(R"(^[A-Za-z0-9]+$)");
                if (std::regex_match(name, alnum))
                    logger.debug() << "Name contains only letters and digits" << ENDL;
            }
            
            void RegexPlayground::search() {
                logger.info() << dots << "[Regex SEARCH]" << ENDL;

                std::string log_line = "User: admin logged at 2025-12-02 with id=42";

                // 1. Szukanie daty wewnątrz tekstu
                std::regex date(R"(\d{4}-\d{2}-\d{2})");
                if (std::regex_search(log_line, date))
                    logger.debug() << "Found date in log line" << ENDL;

                // 2. Wyciąganie grup (user + id)
                std::regex info(R"(User:\s*(\w+).*id=(\d+))");
                std::smatch m;
                if (std::regex_search(log_line, m, info)) {
                    logger.debug() << "User: " << m[1] << ENDL;
                    logger.debug() << "Id:   " << m[2] << ENDL;
                }

                // 3. Iterowanie po wielu dopasowaniach
                std::string scores = "Jan:10, Ala:20, Olek:30";
                std::regex pair(R"((\w+):(\d+))");
                for (std::sregex_iterator it(
                        scores.begin(),
                        scores.end(),
                        pair
                    ), end; it != end; ++it) {
                    logger.debug()
                        << "Name: " << (*it)[1]
                        << ", Score: " << (*it)[2] << ENDL;
                }
            }

            void RegexPlayground::replace_match() {
                logger.info() << dots << "[Regex REPLACE]" << ENDL;
                // --- 1. Prosta zamiana słowa ---
                std::string text = "Ala ma kota";
                std::regex r_name(R"(Ala)");
                std::string changed = std::regex_replace(text, r_name, "Ola");
                logger.debug() << "Changed: " << changed << ENDL; // Ola ma kota

                // --- 2. Zamiana z użyciem grup ---
                std::string vars = "x=10; y=20; z=30;";
                std::regex group(R"((\w)=(\d+))");

                // $1 – nazwa, $2 – liczba
                std::string formatted = std::regex_replace(vars, group, "$1 -> $2");
                logger.debug() << "Formatted vars: " << formatted << ENDL;
                // x -> 10; y -> 20; z -> 30;

                // --- 3. Maskowanie hasła ---
                std::string log = "login ok, password=SuperSecret123";
                std::regex pass(R"(password=\w+)");
                std::string masked = std::regex_replace(log, pass, "password=******");
                logger.debug() << "Masked: " << masked << ENDL;
            }

        #pragma endregion REGEX_PLAYGROUND_CLASS
    }
    #pragma endregion REGEX_KNOWLEDGE_NAMESPACE
    /*---------------------------------------------------------------------------------------*/
    #pragma region COLLECTIONS_KNOWLEDGE_NAMESPACE
    namespace Collections {

        #pragma region VECTOR_PLAYGROUND_CLASS

            void VectorPlayground::creation_ways() {
                logger.info() << "[Vector - CREATION WAYS]" << ENDL;
                std::vector<int> empty_vector; 
                log_vector_state("Empty vector", empty_vector);

                std::vector<int> init_with_zeros(5); 
                log_vector_state("Initialized with zeros", init_with_zeros);

                std::vector<int> filled_with_same_numbers(5, 42);
                log_vector_state("Initialized with 42 5 times", filled_with_same_numbers);
                
                std::vector<int> inicialized_by_list{1,5,7,12};
                log_vector_state("Init list {5, 42}", inicialized_by_list);

                std::vector<int> zeros_copy = init_with_zeros;
                log_vector_state("Copy of zeros init", zeros_copy);
                
            }
            
            void VectorPlayground::access_and_safety() {
                logger.info() << "[Vector -- ACCESS && SAFETY]" << ENDL;
                std::vector<int> data = {10, 21, 34, 56, 73};
                
                logger.debug() 
                    << "Operator [x] fast but dangerous" << ENDL 
                    << "-- no border controll -- out of index is allowed" << ENDL 
                    << "data[0]: " << data[0] << ENDL;
                logger.debug()
                    << "Method .at(x) safe and throw exception if out of range" << ENDL
                    << "Regular index access: .at(1): " << data.at(1) << ENDL;
                try {
                    logger.debug() << ".at(100)";
                    int value = data.at(100);
                    logger.debug() << "success or exception?";
                }
                catch (const std::out_of_range& range_exception) {
                    logger.error() 
                        << "Exception caught cause of: " 
                        << range_exception.what() << ENDL;
                }
                
                logger.debug() 
                    << "Front: " << data.front()  << " | "
                    << "Back: "  << data.back()  << ENDL;
            }

            void VectorPlayground::modification_and_memory() {
                logger.info() << "[Vector - Modification && Memory]" << ENDL;
                std::vector<float> numbers;
                logger.debug()
                    << "Memory reservation primary by: " << ENDL 
                    << "-- method reserve(x)";
                numbers.reserve(10);
                numbers.push_back(15.26);    numbers.emplace_back(20.15);
                numbers.push_back(563.76);   numbers.emplace_back(58.211);
                log_vector_state("After reserve(10)", numbers);

                logger.debug()
                    << "Put in the middle of (costly)" << ENDL
                    << "-- method insert(nr_place, value)";
                
                numbers.insert(numbers.begin() + 2, 995);
                log_vector_state("After insert", numbers);
                
                logger.debug()
                    << "Removal last one" << ENDL << "-- method pop_back()";
                numbers.pop_back();
                log_vector_state("After pop", numbers);

                logger.debug()
                    << "Remove given index" << ENDL << "-- method erase()";
                numbers.erase(numbers.begin() + 2);
                log_vector_state("After erase", numbers);

                // czyszczenie bez zmiany capacity
                logger.debug() << "Clear" << ENDL;
                numbers.clear();
                log_vector_state("After clear", numbers);

                numbers.resize(5);
                log_vector_state("Resized", numbers);

                std::vector<int> values = {0,1,2,3,4,5,6,7,8,9,10,11,12};
                log_vector_state("Main values vector", values);
                std::vector<int> sub_vector(values.begin(), values.begin() + 11); 
                log_vector_state("Sub vector", sub_vector);
                
            }

            void VectorPlayground::iteration() {
                logger.info() << "[Vector - ITERATION]" << ENDL;
                std::vector<double> doubles = {12.667, 512.51267, -133.5787};

                logger.debug()
                    << "Standard iteration formula: \t"
                    << "for (type index = 0; index < .size(); index++)" << ENDL;
                for (std::size_t index = 0; index < doubles.size(); ++index) {
                    logger.debug()
                        << "Index: "   << index          << " | "
                        << "Element: " << doubles[index] << ENDL; 
                }
                logger.debug()
                    << "FOR RANGE, Read only loop: \t"
                    << "for (type element: vector)" << ENDL;
                for (double dub: doubles) {
                    logger.debug() 
                        << "Element: " << dub << ENDL;
                }
                logger.debug()
                    << "FOR RANGE loop with modification by reference : \t"
                    << "for (type& element: vector)" << ENDL;
                for (double& dub: doubles) {
                    logger.debug() 
                        << "Before: " << dub << " | "; 
                    dub *= 3;
                    logger.debug() 
                        << "After: "  << dub << ENDL;
                }
                /*  Iterator
                    coś w rodzaju wskaźnika
                    pokazuje na który element kontenera akutalnie patrzymy
                Możemy zacząć od początku begin | końca end
                    Przejść dalej po kontenerze (kolejny adres) ++it
                    Zobaczyć zawartość *it ->it
                */
                logger.debug() << "By iterator " << ENDL;
                for (auto it = doubles.begin(); it != doubles.end(); it++) {
                    logger.info() << "Iter: " << *it << ENDL;
                }
            }
            
            void VectorPlayground::sort_and_algorithms() {
                logger.info() << "[Vector - soft and algorithms]" << ENDL;
                std::vector<unsigned int> positive{5,6,12,73,8};
                logger.debug() << "Sort ascending - up" << ENDL;
                std::sort(
                    positive.begin(),
                    positive.end()
                );
    
                log_vector_state("After ascending sort", positive);
                logger.debug() << "Sort descending - down" << ENDL;
                std::sort(
                    positive.begin(), positive.end(),
                    std::greater<>()
                );
                log_vector_state("After descending sort", positive);

                std::stable_sort(positive.begin(), positive.end());
                log_vector_state("After stable sort", positive);
                logger.debug() << "Maping values" << ENDL;
                std::transform(
                    positive.begin(), positive.end(), positive.begin(),
                    [](unsigned int x) {
                        return x * 10;
                    }
                );
                log_vector_state("After value mapping", positive);
                int sum = std::accumulate(positive.begin(), positive.end(), 0);
                // szukanie
                auto it = std::find(positive.begin(), positive.end(), 4);

                logger.debug()
                    << "Sorting objects by checking lambda function" << ENDL;

                std::vector<Player> players = {
                    {"Ala", 10}, {"Ola", 25}, {"Ela", 15}
                };
                log_vector_state("Players before sorting", players);
                std::sort(players.begin(), players.end(),
                    [](const Player& first, const Player& second) {
                        return first.score > second.score;
                    }
                );
                log_vector_state("Players after sorting", players);
            }

        #pragma region VECTOR_PLAYGROUND_CLASS
        /*---------------------------------------------------------------------------------------*/
        #pragma region MAP_PLAYGROUND_CLASS
        
            void MapPlayground::creation() {
                logger.info() << "[MAP - CREATION WAYS]" << ENDL;

                std::map<int, std::string> empty_map;
                log_map_state(
                    "EMPTY MAP",
                    empty_map
                );

                std::map<int, std::string> filled_by_initalized_list = {
                    {1, "south"},
                    {4, "north"},
                    {2, "west" },
                    {3, "east" }
                };

                log_map_state(
                    "FILLED BY INITALIZED LIST",
                    filled_by_initalized_list
                );

                std::map<int, std::string> map_copy = filled_by_initalized_list;
                log_map_state("MAP COPY", map_copy);
                
                std::map<int, std::string> moved = std::move(filled_by_initalized_list);
                log_map_state("MOVED WITHOUT COPY", moved);

                std::vector<std::pair<int, std::string>> vector_pairs = {
                    {0, "some"},
                    {100, "other"}
                };
                std::map<int, std::string> from_iterator(
                    vector_pairs.begin(),
                    vector_pairs.end()
                );
                log_map_state("From iterator range", from_iterator);
            }

            void MapPlayground::access_and_safety() {
                logger.info() << "[MAP - ACCESS AND SAFETY]" << ENDL;

                std::map<std::string, int> scores = {
                    {"Alice", 100},
                    {"Tom", 50}
                };
                log_map_state("Initial scores", scores);
                logger.debug()
                    << "Check by [key] if not set it will create with 0: "
                    << scores["Mariusz"] << ENDL;
                
                log_map_state("After [key] check", scores);
                try{
                    logger.debug() << "Safe access by .at(key) " << ENDL;
                    int personScore = scores.at("David");
                    logger.debug() 
                        << "Person score: (not gonna happen)" 
                        << personScore << ENDL;
                }
                catch(const std::out_of_range& exception) {
                    logger.error() 
                        << "Exception caught: " 
                        << exception.what() << " (Key not found)" << ENDL;
                }
                
                logger.debug() << "Check if key exists: " << ENDL;
                #if __cplusplus >= 202002L
                    if (scores.contains("Alice")) logger.info() << "Found" << ENDL;
                    else logger.error() << "Not found" << ENDL;
                #endif

                logger.debug()
                    << ".find() searches for element with key, "
                    << "if found - returns iterator to element"
                    << "if not - return map.end()" << ENDL;

                auto it = scores.find("Alice");
                if (it != scores.end()) {
                    logger.debug()
                        << "Found Alice with value: "
                        << it->second << ENDL;
                }
                
            }

            void MapPlayground::modification_and_merging() {
                logger.info() << "[MAP- MODIFICATION AND MERGIN]" << ENDL;
                std::map<int, int> dict;

                logger.debug()
                    << ".insert(), returns pare {iterator, bool success}" << ENDL
                    << "Not overwriting if key exists" << ENDL;
                dict.insert({1, 12});
                auto [iterator, success] = dict.insert({1, 51});
                log_map_state("Map after inserting", dict);
            
                logger.debug()
                    << ".insert_or_assaign()" << ENDL
                    << "Inserting or overwiting key value " << ENDL;

                dict.insert_or_assign(2, 41);
                dict.insert_or_assign(2, 61);
                log_map_state("After insert_or_asign()", dict);
                
                logger.debug() << ".emplace() creates in place" << ENDL;
                dict.emplace(6, 65);
                log_map_state("After emplace()", dict);

                logger.debug() << ".try_emplace() creates if not exists" << ENDL;
                dict.try_emplace(2, 200);
                log_map_state("After try_emplace()", dict);

                logger.debug() << ".merge() nodes from one to another map" << ENDL;
                std::map<int, int> other_dict = {
                    {7, 63},
                    {8, 1}
                };
                dict.merge(other_dict);
                log_map_state("After merge()", dict);

                logger.debug() << ".erase(): Removing key from map" << ENDL;
                dict.erase(1);
                log_map_state("After erase()", dict);

            }

            void MapPlayground::iteration() {
                logger.info() << "[MAP ITERATION]" << ENDL;
                std::map<int, int> squares = {
                    {1, 1}, {2, 4}, {3, 9}
                };
                logger.debug() << "Iteration by [key, value]: " << ENDL; 
                for (const auto& [number, sq]: squares) {
                    logger.debug()
                        << "Number: " << number << "^2 = " << sq << ENDL;
                }
                logger.debug() << "Classical it.first it.second iteration" << ENDL;
                for (auto &pair : squares) {
                    logger.debug() 
                        << "Pair: " << pair.first << " => " << pair.second << ENDL;
                }
            }
            
            void MapPlayground::custom_sorting_behavior() {
                logger.info() << "[MAP - CUSTOM SORTING]" << ENDL;
                logger.debug()
                    << "Mapy sortują się same. Ale co jeśli chcemy odwrotnie (malejąco)?" << ENDL
                    << "Trzeci parametr szablonu to komparator." << ENDL;
                
                std::map<int, std::string, std::greater<int>> descending_map = {
                    {1, "First"}, {3, "Third"}, {2, "Second"}
                };
                std::ostringstream oss;
                oss << "Descending Map: { "; 
                for(const auto& [key, value] : descending_map) 
                    oss << key << " ";
                oss << "}";
                logger.debug() << oss.str() << ENDL;
            }

            void MapPlayground::pair_usage_scenarios() {
                logger.info() << "[ PAIR usage scenario]" << ENDL;

                logger.debug() << "pair creation" << ENDL;
                std::pair<int, std::string> classic_way = {10, "classic way"};
                auto self_detected = std::make_pair(20, "detected pair by make_pair");
                std::pair modern_way(
                    30, "modern way CTAD, class template argument decution"
                );
                logger.debug()
                    << "Createdd pairs: "
                    << "{" << classic_way.first << "}" << ENDL            
                    << "{" << self_detected.first << "}" << ENDL            
                    << "{" << modern_way.first << "}" << ENDL;   
                
                logger.debug() << "Acces by structered binding" << ENDL;
                auto [id, name] = classic_way;
                logger.debug() 
                    << "Unpacked pair: ID=" << id  << ", "
                    << "Name=" << name << ENDL;

                std::pair<int, int> p_small = {1, 999};
                std::pair<int, int> p_big   = {2, 0};
                logger.debug() << "Comparing pairs attributes" << ENDL;
                bool is_smaller = p_small < p_big;
                logger.debug() 
                    << "{1, 999} < {2, 0} is: " << std::boolalpha << is_smaller << ENDL;

                classic_way.first = 99;
                logger.debug() << "Modification in loose pair key" << classic_way.first << ENDL;

                logger.debug() << "Simulation of map pair:" << ENDL;
                std::pair<const int, std::string> map_node = {1, "MapData"};
                // map_node.first = 2; // compilation error
                map_node.second = "NewData";

                logger.debug() << "Pairs Vector " << ENDL;
                std::vector<std::pair<std::string, int>> ranking = {
                    {"Burek", 10}, {"Azor", 50}, {"Reksio", 30}
                };
                
                // Sortowanie po wyniku (second)
                std::sort(ranking.begin(), ranking.end(), 
                    [](const auto& a, const auto& b) {
                        return a.second > b.second; // Malejąco po punktach
                    }
                );
                std::ostringstream oss;
                oss << "Vector of pairs sorted by value: ";
                for(const auto& [dog, score] : ranking) {
                    oss << dog << "(" << score << ") ";
                }
                logger.debug() << oss.str() << ENDL;
            }
        
        #pragma endregion MAP_PLAYGROUND_CLASS
    }
    #pragma endregion COLLECTIONS_KNOWLEDGE_NAMESPACE
    /*---------------------------------------------------------------------------------------*/
    #pragma region FUNCTIONS_KNOWLEDGE_NAMESPACE
    namespace Functions {

        #pragma region LAMBDA_PLAGROUND_CLASS

            void LambdaPlayground::syntax_and_basics() {
                logger.info() << "[LABMDA - syntax & basics]" << ENDL;
                logger.debug()
                    << "IIFGE - immediately invoked function expression" << ENDL
                    << "Od razu wykonana lambda - bo na koncu {}()";

                []() -> void {
                    logger.debug() << "Executed instantly" << ENDL;
                }();
                logger.debug()
                    << "Nazwana lambda, przypisana do mziennej" << ENDL;
                auto hook_to_squares = [](int baseNumb) -> int {
                    return std::pow(baseNumb, 2);
                };

                logger.debug()
                    << "hoocked lambda with arg execution " << ENDL
                    << ".(2): " << hook_to_squares(5) << ENDL;
                
                auto divide_hook = [](int sep, int div) -> double {
                    if (div == 0)
                        return 0.0;
                    return static_cast<double>(sep) / div;
                };
                logger.debug() 
                    << "Sprecyzowany typ i mutli arg: "
                    << divide_hook(10, 3) << ENDL;
                
            }
            
            void LambdaPlayground::capture_mechanisms() {
                logger.info() << "[LAMBDA - CAPTURE & MUTABLE]" << ENDL;
                
                int multiplier = 10;
                logger.debug()
                    << "Domyslnie lambda jest const, kopiuje wartosc." << ENDL
                    << "nie można zmienić skopiowanej wartość" << ENDL
                    << "CAPTURE BY VALUE [=] - wszystko  | [zmienna]" << ENDL;

                auto by_value = [multiplier](int value) -> bool {
                    // multiplier++; error read-only variable
                    return value * multiplier;
                };
                int local_state = 0;
                logger.debug()
                    << "MUTABLE, poszwrala edytować skopiowaną wartosc" << ENDL
                    << "Ale jest zmieniana tylko wewnątrz lambdy" << ENDL;

                auto stateful_lambda = [local_state]() mutable {
                    local_state += 15;
                    logger.debug() << "Inside mutable lambda: " << local_state << "\n";
                };
                stateful_lambda();
                stateful_lambda();
                logger.debug() 
                    << "Outside variable (unchanged): " 
                    << local_state << ENDL;

                int counter = 1;
                logger.debug()
                    << "CAPTURE BY REFERENCE" << ENDL
                    << "pracujemy na oryginale, wiec możemy zmieniać" << ENDL
                    << "Before: " << counter << ENDL;

                auto increment_by_ref = [&counter]() -> void {
                    counter++;
                };

                increment_by_ref();
                logger.debug() 
                    << "Counter after increment" << counter <<  ENDL;
            }

            void LambdaPlayground::run_times(
                size_t iter_amount,
                const std::function<void(int)>& action
            ) {
                for (int index = 0; index < iter_amount; index++) {
                    logger.debug() 
                        << "Runnig action " << index << " time." << ENDL;
                    action(index);
                }
            }

            void LambdaPlayground::std_function_wrapper() {
                logger.info() << "[LAMBDA STD::FUNCTION]" << ENDL;
                logger.debug()
                    << "std::function to 'pudełko' na cokolwiek co da się wywołać " << ENDL
                    << "(lambda, funkcja, funktor). Ma narzut wydajnościowy, " << ENDL
                    << "ale pozwala przekazywać funkcje jako parametry. " << ENDL;
                
                std::function<void(int)> printer = [](int index) {
                    logger.debug() 
                        << "callback value: " << index << ENDL;
                };

                run_times(3, printer);
            }

            void LambdaPlayground::modern_lambdas() {
                logger.info() << "[LAMBDA] MODERN C++14/20" << ENDL;
                /* 1. Generic Lambda (C++14) - parametr auto
                Działa jak szablon. Jedna lambda obsłuży int, string, double.
                */
                auto print_anything = [](const auto& value) {
                    logger.debug()
                        << "Generic print: " << value << ENDL;
                };
                print_anything(123);
                print_anything("John Słaby");
                print_anything(15.5f);
                /* 2. Capture Initialization (C++14)
                    Można stworzyć nową zmienną tylko dla lambdy.
                */
                auto moved_lambda = [ptr = std::make_unique<int>(10)]() {
                    logger.debug() 
                        << "I own a unique_ptr inside lambda: " 
                        << *ptr << ENDL;
                };
                moved_lambda();

            }

        #pragma endregion LAMBDA_PLAGROUND_CLASS
        /*---------------------------------------------------------------------------------------*/
        #pragma region UTILITY_PLAGROUND_CLASS

            void UtilityPlayground::char_operations() {    
                logger.info() << "[UTILS] CHAR CHECKS " << ENDL;
                /*
                    isdigit(int char)
                        z <cctype>
                    sprawdza czy dany znak reprezentuje cyfre
                        '0' - '9'
                */
                char c = '5';
                char l = 'A';
                logger.debug()
                    << "Char '" << c << "':\n"
                    << "  isdigit: " << (std::isdigit(c) ? "Yes" : "No") << "\n" // Cyfra
                    << "  isalpha: " << (std::isalpha(c) ? "Yes" : "No") << "\n" // Litera
                    << "  isalnum: " << (std::isalnum(c) ? "Yes" : "No") << "\n"; // Litera lub Cyfra

                char lower = std::tolower(l);
                logger.debug() 
                    << "Toupper/Lower: " << l 
                    << " -> " << lower << "\n";
            }

            void UtilityPlayground::numeric_operations() {
                logger.info() << "[UTILS] NUMERIC HELPER" << ENDL;
                /* std::clamp (C++17) - ogranicza wartość do zakresu [min, max]
                    Dobre do gier (HP, pozycja) czy UI.
                */
                int value = 150;
                int clamped = std::clamp(value, 0, 100); // utnie do 100
                logger.debug() << "Clamp(150, 0, 100) = " << clamped << "\n";

                /* std::swap - szybka zamiana wartości */
                int a = 1, b = 2;
                std::swap(a, b);
                logger.debug() << "Swapped a: " << a << ", b: " << b << "\n";
            }

        #pragma endregion UTILITY_PLAGROUND_CLASS
    }
    #pragma endregion FUNCTIONS_KNOWLEDGE_NAMESPACE
};
#pragma endregion KNOWLEDGE