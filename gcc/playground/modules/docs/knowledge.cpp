// ------------------------
#include <docs/knowledge.hpp>
/*
    Creating Exceptions
*/

namespace Knowledge {
    
/*--------------StreamsManagement namespace---------------------------------*/
    namespace StreamsManagement {
/*----------StreamsManagement::StandardStream class methods------------*/
        void StandardStream::print_list(std::ostream& os, const std::vector<int>& items){
            int index = 1;
            for (const auto& item: items){
                os << index++ << ") value: " << item << "\n";
            }
        }
        std::vector<std::string> StandardStream::read_lines(std::istream& is){
            std::vector<std::string> lines;
            std::string line;
            while(std::getline(is, line)){
                lines.push_back(line);
            }
            return lines;
        }
        void StandardStream::standard_output(){
            /* output - czyli dane wychodzą gdzieś
                - funkcja nie zna celu wyjśca wtedy mamy ostream jako parametr
            */
            std::vector<int> numbs{1, 15, 61, 211};
            std::ofstream out("numbers_list.txt");
            std::ostringstream mem;
            print_list(out, numbs);
            print_list(mem, numbs);
            logger.info() << "Memory buffor: \n" << mem.str();
            std::ifstream in("numbers_list.txt");
            std::istringstream stream_mem("a\nb\nc\n");
            auto lines = read_lines(in);
            auto mem_lines = read_lines(stream_mem);
            std::filesystem::remove("numbers_list.txt");
        }
        void StandardStream::standard_input() {
            logger.debug() << "Enter some number" << std::endl; //  pisanie do stdout - terminala 
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
                logger.debug() << "Provided number: [" << number << "].\n"; 
                std::clog // clog do informacji diagnostycznych
                    << "[LOG-INFO] User provide number: " 
                    << number << std::endl;
            }
        }
/*----------StreamsManagement::FileStream class methods------------*/
        void FileStream::write_data_out(){
            /* tworzy nowy plik albo czyści , domyślne tryby
                std::ios::out | std::ios::trunc */
            std::ofstream out("notes.txt");
            if(!out){
                logger.debug() << "Cannot open for override";
                return;
            }
            out << "[INFO] File stream in here!\n [NEXT] end\n<->";
            std::filesystem::remove("notes.txt");
        }  // out.close(); // after went out of func

        void FileStream::write_data_out_by_append(){
            std::ofstream append_out("notes.txt", std::ios::app); // dopisuje std::ios::app - append
            if(!append_out){
                logger.debug() << "Cannot open to append";
                return;
            }
            append_out << "\n[NEW] one and last";
        }

        void FileStream::read_from_in(){
            std::ifstream in("notes.txt");
            if (!in){
                std::cerr << "Cannot open notes.txt\n";
                return;
            }
            std::string line;
            int index = 0;
            /* getline() - pojedyncze pobranie to 
                std::string first_line;
                std::getline(in, first_line);
                bierze z buffora pierwszą linie i wstawia w zmienną 
            */
            while (std::getline(in, line)){
                logger.debug() << "Line " << index++ << " content: " << line << ".\n"; 
            }
            std::filesystem::remove("notes.txt");
        }

/*----------StreamsManagement::MemoryStream class methods------------*/
        void MemoryStream::load_string_into_buffor(){
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
                      << ", d=" << d << '\n';
        }

        void MemoryStream::load_data_into_buffor(){
            std::ostringstream out;
            out << "Result: " << 27 << std::endl;
            std::string text = out.str(); // pobiera z buffora
            logger.debug() << "Content after loading from buffor " << text << std::endl;
        } 

        void MemoryStream::read_and_write_data_to_buffor(){
            std::stringstream sstream;
            sstream << "123 451";
            int first, second;
            sstream >> first >> second;
            logger.debug() << (first + second) << '\n';
        }

/*----------StreamsManagement::FileSystemManagment class methods------------*/
        fs::path FileSystemManagment::create_paths(){
            /*  tworzenie ścieżek
                operator / - składa ścieżki */
            fs::path user_path = "/home/user";
            fs::path scores_path = user_path / "home" / "scores.txt";
            return scores_path;
        }

        void FileSystemManagment::paths_management(fs::path path)
        {
            logger.info() << "Getting basic elements of paths: (slices)\n";
            logger.debug() << "[PATHS PARTS]\n"
                << "Filename: "   << path.filename()    << std::endl
                << "Identifier: " << path.stem()        << std::endl
                << "Extension: "  << path.extension()   << std::endl
                << "Parent : "    << path.parent_path() << std::endl;
            
            /*  absolute - nie sprawdza czy istnieje 
                cannonical - rzuca wyjatek
                weakly_cannonical - nie rzuca  */
            fs::path absolute = fs::absolute(path);
            fs::path cannonical = fs::weakly_canonical(path);
            logger.debug()
                << "[FULL PATHS]\n"
                << "  Absolute path : " << absolute    << '\n'
                << "  Canonical     : " << cannonical  << "\n\n";
            /* aktualne środowisko pracy */
            // bierzące katalogi, gdzie jesteśmy
            logger.debug()
                << "  Current path  : " << fs::current_path()       << '\n'
                << "  Temp dir      : " << fs::temp_directory_path() << "\n";
        }

        void FileSystemManagment::file_states(fs::path path){
            logger.info() << "[FILE STATES]\n";
            /*Czy istnieje i jakim jest plikiem*/
            bool exists   = fs::exists(path);
            bool is_file  = fs::is_regular_file(path);
            bool is_dir   = fs::is_directory(path);
            bool is_empty = fs::is_empty(path);
            logger.debug()
                << "  Exists        : " << std::boolalpha << exists << '\n'
                << "  Is file       : " << is_file << '\n'
                << "  Is directory  : " << is_dir << "\n"
                << "  Is empty      : " << is_empty << "\n";

            std::uintmax_t file_size = fs::file_size(path);
            if (exists) {
                /* czas ostatniej akutalizacji:
                    auto path_time = fs::last_write_time(path);
                czy wskazują na ten sam obiekt
                    fs::equivalent(path, fs::path("other.txt")); */
            }
        }
        
        void FileSystemManagment::modification(fs::path file_path){
            /* modyfikacja plików i katalogów
                create_directory - mkdir nazwa, zwraca boolean jesli istnieje
                create_directories - mkdir -p

                remove - usuwa plik lub pusty katalog
                remove_all - rekurencyjne rm -rf 

                rename - linux mv - zmienia nazwe i przenosi gdzie chemy  
                copy(source, destination, option)
                    fs::copy_options::none
                    fs::copy_options::overwrite_existing
                    fs::copy_options::skip_existing
                    fs::copy_options::recursive (dla katalogów)

                iteracja: 
                    directory_iterator - płaska, tylko bezposredni katalog
                    recursive_directory_iterator - rekurencyjna, wchodzi w podkatalogi
                permissions - nadawnie uprawnienia:
                    auto statsu =- 
                    perms - jakie uprawnienia ustawiasz
                        owner | group | other --- all | write | read | exite
                    fs::perm_options::add
                        add remove replace
            */
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
            for (const auto& file: fs::directory_iterator(file_path)){
                const fs::path& path = file.path();
            }

            for(const auto& file_rec: fs::recursive_directory_iterator(file_path)){\
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

        void FileSystemManagment::get_file_from_resources(){
            try{
                auto path = resource_path("scores.txt");
                logger.info() << "Config path: " << path << std::endl; 
                std::string loaded_text = load_text("scores.txt");
                logger.info() << "Config path text: " << loaded_text<< std::endl; 
            }
            catch (const std::exception& ex){
                logger.error() << "Error while reading resources: " << ex.what() << std::endl; 
            }
        }
    }

/*--------------AliasesAndTypes NAMESPACE---------------------------------*/
    namespace AliasesAndTypes {
/*----------AliasesAndTypes::AliasesPlayground class methods------------*/
        void AliasesPlayground::basic_aliases(){
            logger.info() << "BASIC ALIASES\n";
            typedef unsigned long int UL_int;
            using Ldouble = long double;
            using Callback = void(*)(int);
            UL_int bts_id = 125612512516324673;
            Ldouble meta_numb = 512.512095102518260166;
            Callback cb = [](int x) {
                logger.debug() << "Callback called with x = " << x << "\n";
            };

            logger.debug() 
                << "UL_int bts_id = " << bts_id << "\n"
                << "Ldouble meta_numb = " << meta_numb << "\n";

            cb(12);
        }
        void AliasesPlayground::template_aliases(){
            logger.info() << "TEMPLATE ALIASES\n";
            TypeVec<int> numbers{1,5,612,26};
            StringMap<double> factors{
                {"pi", 3.51251},
                {"e", 2.61241}
            };
            logger.debug() << "TypeVec<int> numbers:" << std::endl;
            for (int numb : numbers) {
                logger.debug() << "  " << numb << std::endl;
            }

            logger.debug() << "StringMap<double> factors:" << std::endl;
            for (const auto& [key, value]: factors){
                logger.debug() << " " << key << "-" << value << '\n';
            }
        }
        
        void AliasesPlayground::strong_types(){
            logger.info() << "STRONG TYPES" << std::endl;
            UserIdAlias id1 = 10;
            UserIdAlias id2 = 20;

            UserId strong1{10};
            UserId strong2{20};

            logger.debug()
                << "UserIdAlias u1 = " << id1 << std::endl
                << "UserIdAlias u2 = " << id2 << std::endl
                << "UserId strong1.value = " << strong1.value << std::endl
                << "UserId strong2.value = " << strong2.value << std::endl;
        }

        /* std::variant - Bezpieczna unia
            - czyli zmiennado przechwycenie jednego z wielu typów
                przetrzymuje jedną wartość z listy typów
               syntax std::variant<typ1, typ2, typx> zmienna;
            Sprawdzenie jaki typ trzymany jest aktualnie
                std::holds_alternative<typ_sprawdzany>(zmienna_wariantowa) {}
            Index przechowywane typu (liczony jako kolejność z definicji)
            pobieranie zawartości
                std::get<typ>(zmienna)
                std::get_if<typ>(zmienna) bezpieczniejsza wersja
                std::visit(lambda) - użyteczne do 
                    narzedzie które odpala odpowiednia lambde w zalęzności od typu
                    jak siedzi w środku
        */
        void AliasesPlayground::play_with_variant_save_union(){
            logger.info() << "VARIANT PLAYGROUND\n"; 
            std::variant<std::string, int, double> values;
            bool holds_integer = std::holds_alternative<int>(values);
            int variant_index = values.index();
            values = 1;
            logger.debug() << 
                "Does hold it integer " << std::boolalpha << holds_integer << std::endl;
            if (holds_integer){
                logger.debug() 
                    << "Variant holds int type, which is index nr" << variant_index << '\n'
                    << "Value of integer is" <<  std::get<int>(values) << '\n';
                if (auto val = std::get_if<std::string>(&values)) {
                    logger.debug() << *val;
                }
            }
            std::visit(
                [](auto&& value){
                    logger.info() << "Received from variant: " << value << "\n"; 
                },
                values
            );
        }

        void AliasesPlayground::play_with_optional(){
            /*  optional 
                    może przechowywać wartość albo wartosc albo nullopt 
                    zamiast zwracać -1 0 lub nullptr tylko
                        albo<T> albo nic
                tworzenie
                    std::optional<typ> zmienna = wartosc;
                    auto d = std::make_optional(wartosc);
                wyciaganie wartosci
                    zmienna.value() ale rzuci wyjatek jesli brak wartosci
                    *zmienna - poprzez dereferencje
                    zmienna.value_or(wartosc_jesli_null_opt)
                modyfikacja:
                    zmienna.reset() - czyści wartosc
                    zmienna.emplace() - wstawia nowa
            */
            std::optional<int> numb = 42;
            std::optional<int> other = std::nullopt;
            bool has_numb_value = numb.has_value();
            if (has_numb_value){
                logger.info()
                    << "Value via .value(): " << numb.value() << std::endl
                    << "Value via *numb   : " << *numb << std::endl;
            }
            int number = numb.value_or(-1);
            logger.info() << "Number (value_or): " << number << std::endl;
            numb.reset();
            numb.emplace(51);
        }

/*----------AliasesAndTypes::CastingPlayground class methods------------*/
        void CastingPlayground::implicit_conversion(){
            double pi_double = 3.14562;
            int converted_pi = pi_double;
            logger.debug()
                << "Implicit convert: "<<  converted_pi << "\n";
        }

        void CastingPlayground::convert_static_cast(){
            double var = 3.1561261;
            int static_var = static_cast<int>(var); 
            logger.debug()
                << "Static convert: "<<  static_var << "\n";
        }

        void CastingPlayground::convert_const_cast(const int* value){
            int* pointer = const_cast<int*>(value);
            *pointer = 99; // nie polecane, ale możliwe
            logger.debug()
                << *pointer << "\n";
        }

        void CastingPlayground::convert_reinterpret_cast(){
            int value = 65;
            char* ptr = reinterpret_cast<char*>(&value);
            logger.debug()
                << *ptr << "\n";
        }

        void CastingPlayground::convert_dynamic_cast(){
            Base* base = new Derived;
            Derived* derived = dynamic_cast<Derived*>(base);
            if (derived) {
                derived->say();
            }
        }

/*----------AliasesAndTypes::PointersPlayground class methods------------*/
        void PointersPlayground::basic_pointer(){
            /*  numb = wartosc 
                ptr - adres pamieci
                *ptr - dereferencja - idz pod adres i wex wartosc
                -> to to samo co (*pointer).metoda()
            */
            int numb = 412;
            int* numb_ptr = &numb; // &adres
            logger.debug() << "Numb " << numb << std::endl;
            logger.debug() << "Numb address " << numb_ptr << std::endl;
            *numb_ptr = 100;
            logger.debug() << "Dereference after chage: " << *numb_ptr << std::endl;
        }

        void PointersPlayground::pointer_to_structure(){
            Person woman(21);
            Person* struct_ptr = &woman;
            struct_ptr->introduce();
        }

        void PointersPlayground::allocate_memory_dynamic(){
            int* ptr = new int(10); // tworzy int w pamieci
            logger.debug() << *ptr << std::endl;
            delete ptr;
        }
        void PointersPlayground::unique_pointer(){
            std::unique_ptr<Person> marek = 
                std::make_unique<Person>(51);
            logger.debug()
                << "Person " << marek->_age << " is doing something\n";
            // auto f2 = marek; compilation fail
            auto f2 = std::move(marek);
        }
    
        void PointersPlayground::shared_pointer(){
            std::shared_ptr<Connection> sql_db, mongo_db;
            sql_db = std::make_shared<Connection>();
            sql_db->name = "SQL db";
            sql_db->accounts = 1;
            mongo_db = sql_db; // współdzielenie jednego obiektu
            mongo_db->accounts = 2;
            logger.debug()
                << "Mongo db: " << mongo_db->name << "\n"
                << "SQL amount: " << sql_db->accounts << "\n"
                << "Using the connection\n";
        }

/*----------------AliasesAndTypes::Enums NAMESPACE---------------------------*/
        namespace Enums {
            
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
                logger.info() << "[Basic enum attribute check]" << std::endl;
                Status well = WARNING;
                Status status_by_number = (Status)100;
                if (well == ERROR || status_by_number == ERROR)
                    logger.debug()
                        << "There occurs an error\n";
                else
                    logger.debug()
                        << "Value: " << well 
                        << " and its ok\n";
                // są konflikty z innymi
            }
            
            void EnumPlayground::enum_class_value_retrieval() {
                logger.info() << "[Enum class value retrieval]" << std::endl;
                RequestMethod method = RequestMethod::GET;
                int method_code = static_cast<int>(method);
                logger.debug() 
                    << "Request method code: " 
                        << method_code << std::endl;
            }
            
            void EnumPlayground::enum_class_hex_attribute_value() {
                logger.info() << "[Class hex value]" << std::endl;
                Color color = Color::GREEN;
                logger.debug() 
                    << "Hex color: "
                    << std::hex << static_cast<uint8_t>(color) 
                    << std::endl;
            }

            void EnumPlayground::enum_as_vector_type_iteration(){
                logger.info() << "[Vector<Enum type> iteration]" << std::endl;
                constexpr std::array<RequestMethod, 3> all_requests = {
                    RequestMethod::GET,
                    RequestMethod::DELETE,
                    RequestMethod::POST
                };
                for (auto request: all_requests){
                    logger.debug() 
                        << "Request: (int) " << static_cast<int>(request)
                        << ", As (string) " << request_method_to_string(request)
                        << std::endl;
                }
            }

            void EnumPlayground::mapping_enum_to_string(){
                logger.info() << "[Mapping enum]" << std::endl;
                RequestMethod method = RequestMethod::GET;
                std::string method_str = request_method_to_string(method);
                logger.info()
                    << "Converted method to string: " << method_str
                    << std::endl;
                RequestMethod get_method = RequestMethod::GET;
                auto mapped_from_string = string_to_request_method(method_str);
                if (mapped_from_string != std::nullopt){
                    RequestMethod mapped_value = mapped_from_string.value();
                    logger.debug() << "Method: " << static_cast<int>(mapped_value) << std::endl;
                }
            }
        }
        
        namespace Templates {
            void TemplatePlayground::basic_redundancy_difference() {
                logger.debug() << "[Templates] basic_redundancy_difference()\n";
                //  zduplikowane podejście - dwie osobne funkcje do dodawanie
                int sum_int = add_int(1,1);
                double sum_double = add_double(1.5, 1.5);
                logger.debug()
                    << "add_int(1, 1) = " << sum_int << "\n"
                    << "add_double(1.5, 1.5) = " << sum_double << "\n";

                // z użyciem templata
                int generic_int = generic_add(1,2);
                double generic_double = generic_add(1.5, 15.7);
                std::string generic_string = generic_add(
                    std::string("Hi "), std::string("there")
                );
                logger.debug()
                    << "generic_add<int>(1, 2) = " << generic_int << "\n"
                    << "generic_add<double>(1.5, 15.7) = " << generic_double << "\n"
                    << "generic_add<std::string>(\"Hi \", \"there\") = "
                    << generic_string << "\n";
            }

            void TemplatePlayground::template_functions() {
                logger.info() << "[Templates] template_functions\n"; 
                /*  automatyczna dedukacja typu - int
                    jawne typowanie <typ>*/
                auto bigger = max_of(5, 9); 
                auto longer = max_of<std::string>("his", "yo");
                logger.debug()
                    << "max_of(5, 9) = " << bigger << "\n"
                    << "max_of<string>(\"his\", \"yo\") = " << longer << "\n";
                
                auto different_types = add_different(12.51, 125);
                logger.debug()
                    << "add_different(12, 515.5125) = " << different_types << "\n";
            }
            void TemplatePlayground::template_classes() {
                logger.info() << "[Templates] classes: \n";
                GenericBox<int> health(100);
                GenericBox<double> accuracy(51.5);
                GenericBox<std::string> nickname("Johny");
                logger.debug() 
                    << "HP: ["   << health.get()   << "] | "
                    << "ACC: ["  << accuracy.get() << "] | " 
                    << "Nick: [" << nickname.get() << "] \n";
                // Para typów generycznych
                GenericPair<std::string, int> player_score("Golo", 125);
                logger.debug() 
                    << "Key: "   << player_score.get_key() << ": " 
                    << "Value: " << player_score.get_value() << "\n";
            }

            void TemplatePlayground::template_as_vector_type(){
                logger.debug() << "[Templates] template_as_vector_type \n";
                GenericItemsContainer<int> numbers(5);
                numbers.add(10);
                numbers.add(1256);
                logger.debug() << "All numbers reserved:\n";
                numbers.print_all_items();
                GenericItemsContainer<int> numbers_inicialized{10, 1256};
                logger.debug() << "Numbers initialized:\n";
                numbers_inicialized.print_all_items();
                logger.debug() << "Numbers filled with zeros:\n";
                GenericItemsContainer<int> filled_zeros(3, 0);
                filled_zeros.print_all_items();

                logger.debug()
                    << "Active containers: "
                    << GenericItemsContainer<int>::get_active_containers() << "\n";
            }
        }
    }

/*----------------NameSpacesKnow NAMESPACE---------------------------*/
    namespace NameSpacesKnow {
        namespace Begin{
            void print(){
                logger.debug() << "Namespace Begin \n";
            }
        }
        namespace End{
            void print(){
                logger.debug() << "Namespace End \n";
            }
        }

        void Out::Inner::read(){
            logger.debug() << "Reading in Inner\n";
        }

        void Out::Inner::write(){
            logger.debug() << "Writing in Inner\n";
        }

        struct API::Vector_v1{
            float x;
            float y;
        };

        void API::append_list(Vector_v1 vector){
            logger.debug() << "Appending to list from inline\n";
        }

        class API::v2::Vector_v2 {
            float x;
            float y;
            public:
                float get_x(){
                    return x;
                }
                float get_y(){
                    return y;
                }
        };

        void API::v2::append_list(Vector_v2 vector) {
            logger.debug() << "Appending to list from api v2\n";
        }
    }

/*----------------CompileTime NAMESPACE---------------------------*/
    namespace CompileTime {
        
        void CompilePlayground::compile_time_basic_definition(){
            logger.info() << "[COMPILE BASICS]\n";
            //  constexpr vs c const 
            const int const_value = 512;
            logger.debug()
                << "const int value: " << const_value << "\n";
                // << wartosc nie zmienna, ale nie w comple time

            constexpr int board_number = 125;
            constexpr std::array<int, 4> numbers {
                151, 625, 5125, board_number 
            }; 
            logger.debug() 
                << "constexpr int board_number" << board_number ; 

            for (auto& numb: numbers){
                logger.debug()
                    << "Value from compile numbers: " << numb << "\n";
            }
            // mogą działać w runtime
            int x = 561226;
            int runtime_sum = board_number + x;
            logger.debug()
                << "runtime_sum = board_number + x = " << runtime_sum << "\n";
        }
        void CompilePlayground::compile_time_functions() {
            logger.info() << "[COMPILE TIME FUNCTIONS ]\n";
            constexpr int fac_result_ct = factorial(12);
            logger.debug() 
                << "constexpr func factorial(5): "
                << fac_result_ct << "\n";
            int run_time_value = 51;
            int fac_result_rt = factorial(run_time_value);
            logger.debug()
                << "constexpr func factorial(rt_value): "
                << fac_result_rt << "\n";
        }
        void CompilePlayground::only_compile_time_functions() {
            logger.info() << "[CONSTEVAL FUNCTIONS]\n";
            constexpr int id = make_id(51);
            int x = 5;
            // int id_rt = make_id(x); // nie, bo wymaga ct value 
            logger.debug()
                << "constexpr make_id(7): "
                << id << "\n";
        }
        void CompilePlayground::only_compile_time_inicialization() {
            logger.info() << "[CONSTINIT EXPLANATION]\n";
            logger.debug() <<
                "Var counter already inicialized in ct: "
                << global_counter << "\n";
            // moze byc zmienialna
            global_counter++;
            logger.debug()
                << "Po zmianie: "
                << global_counter << "\n";
        }
        void CompilePlayground::compile_time_in_classes() {
            logger.info() << "[CONSTEXPR IN CLASSES]\n";
            constexpr Point p1(3, 4);            // compile-time obiekt
            constexpr int len = p1.length_squared(); // compile-time obliczenie
            logger.debug()
                << "compile time point length: "
                << len << "\n";

            // --- runtime obiekt ---
            int a = 5;
            Point p2(a, 10);     // runtime konstrukcja
            int len2 = p2.length_squared(); // runtime wywołanie
            logger.debug()
                << "run time point length: "
                <<  len2 << "\n";

        }
    }

/*----------------Preprocesor NAMESPACE---------------------------*/
    namespace Preprocesor {
        double circle_area(double radius){
            return PI * radius * radius; 
        }

        void all(){
            double area = circle_area(5);
            logger.debug() << "Area: " << area << std::endl;
            // usage of SQUARE macro
            logger.debug() << SQUARE(4) << std::endl;
            LOG("Program startuje!");
        }
    }

/*----------------ClassKnow NAMESPACE---------------------------*/
    namespace ClassKnow {

/*----------------ClassKnow::Specificators NAMESPACE---------------------------*/
        namespace Specificators {
            
/*----------Specificators::PrivateSpecificator class methods------------*/
            void PrivateSpecificator::start(){
                velocity = 50; // this.velocity
            }

            void PrivateSpecificator::compare(const PrivateSpecificator& diff){
                logger.debug() << "Comparing: [" << velocity - diff.velocity << "]\n";  
                velocity = diff.velocity;
            }

/*----------Specificators::PrivateSpecificator class methods------------*/
            void PublicSpecificator::set_and_show(){
                scores = 51.2;
                logger.info() << "Scores: " << scores << std::endl;
            }

/*----------Specificators::ProtectedSpecificator class methods------------*/
            void ProtectedSpecificator::show_shield() const {
                logger.debug() << "Shield value: " << shield << std::endl;
            }
            void ProtectedChild::damage() {
                shield -= 10; // has access
                show_shield(); // has access
            }

/*----------Specificators::SpecificatorPlayground class methods------------*/
            void SpecificatorPlayground::private_spec_introduce(){
                logger.info() << "[PRIVATE SPECIFICATOR]\n";
                PrivateSpecificator priv_spec_a, priv_spec_b;
                priv_spec_a.start();
                logger.debug()
                    << "Bład Kompilacji jesli próbujemy"
                    << " dostać sie do atrybutu klasy \n";
                /*
                    Błąd kompilacji, nie można dostać się do prywatnego atrybutu
                    second.velocity = 12;  
                */
                priv_spec_a.compare(priv_spec_b);
            }

            void SpecificatorPlayground::public_spec_introduce(){
                logger.info() << "[PUBLIC SPECIFICATOR]\n";
                PublicSpecificator allowed;
                allowed.set_and_show();
                allowed.scores = 12.5;
                logger.debug() 
                    << "Dostep do wszystkich metod i pól klasy\n";
            }

            void SpecificatorPlayground::protected_spec_introduce(){
                logger.info() << "[PROTECTED SPECIFICATOR]\n";
                ProtectedSpecificator family;
                family.show_shield();
                ProtectedChild child;
                child.damage();
                logger.debug() 
                    << "Dostep do pól przez klasy dziedziczące \n";
                // child.shield -= 10;  jak z private, błąd komplacji
            }
        }

/*----------------ClassKnow::LifeCycle NAMESPACE---------------------------*/
        namespace LifeCycle {

/*----------LifeCycle::Constructor class methods------------*/
            Constructor::Constructor(){
                _name = "none";
                logger.info() << "Default object created\n";
            }

            Constructor::Constructor(std::string name){
                _name = name;
                logger.info() 
                    << "Object with " << name << " name created\n";
            }

            Constructor::Constructor(std::string name, int threshold)
                : _name(name), _threshold(threshold){
                logger.info() 
                    << "Object inicialized with list (" 
                    << name << ", " 
                    << threshold <<  " params created\n";
            }
            void Constructor::introduce(){
                logger.debug()
                    << "Constructor attributes: ["
                    << _name << ", "
                    << _threshold << "]\n";
            }
        
/*----------LifeCycle::Destructor class methods------------*/
            Destructor::Destructor(){
                _notes_file_hook.open("notes.txt");
                if (!_notes_file_hook){
                    std::cerr << "Cannot open notes.txt file\n";
                    return;
                }
                else{
                    logger.info() << "Hook to file notes.txt applicated\n";
                }
            }

            Destructor::Destructor(std::string path){
                _notes_file_hook.open(path);
                if (!_notes_file_hook){
                    std::cerr << "Cannot open " << path << "path\n";
                    return;
                }
                else{
                    logger.info() << "Hook to file " << path << "applicated\n";
                }
            }

            Destructor::~Destructor(){
                if(_notes_file_hook.is_open()){
                    _notes_file_hook.close();
                    logger.info() << "Hook closed properly\n";
                }
                logger.debug() << "Hook deleted\n";
            }

/*----------LifeCycle::LifeCyclePlayground class methods------------*/
            void LifeCyclePlayground::basic_constructor(){
                logger.info() << "[CONSTRUCTOR INTRODUCTION]\n";
                Constructor default_one;
                Constructor with_parameter("Pretty");
                Constructor inicialized_list("Not bad", 15);
                default_one.introduce();
                with_parameter.introduce();
                inicialized_list.introduce();
            }

            void LifeCyclePlayground::basic_destructor(){
                logger.info() << "[DESTRUCTOR INTRODUCTION]\n";
                Destructor destructor;
                Destructor destructor_with_param("other.json");
                logger.debug()
                    << "Destroy object after reach the score\n";
            }
        }

/*----------------ClassKnow::GettersAndSetters NAMESPACE---------------------------*/
        namespace GettersAndSetters {

/*----------GettersAndSetters::AccessGates class methods------------*/
            AccessGates::AccessGates(int amount, int item){
                if (amount < 0){
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

            void AccessGates::set_amount(int new_amount){
                if (new_amount < 0){
                    std::cerr << "Vector cannot have negative amount of elements\n";
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
                    catch(const std::out_of_range& range_exception){
                        std::cerr << "Element " << new_gates.at(id) << " has index out of range\n";
                        logger.error() << "Exception " << range_exception.what() << std::endl;
                    }
                }
            }
            void demonstrate_gates(){
                logger.debug() << "[Getters & Setters INTRODUCTION]\n";
                AccessGates gates(5, 12);
                logger.debug() 
                    << "Gates amount: " << gates.get_amount() << "\n"
                    << "Size of gates: " << gates.get_gates().size() << "\n";
                gates.set_amount(15);
                std::vector<int> new_gates{15, 62, 73, 21};
                gates.set_gates(new_gates);
                logger.debug() 
                    << "Gates item: " << gates.get_gates().at(1) << "\n";
            }
        }

/*---------------ClassKnow::Structures NAMESPACE---------------------------*/
        namespace Structures {

/*----------Structures::Employee structure methods------------*/
            void Employee::print() const {
                logger.debug() << name 
                    << " (" << age << " lat) - " 
                    << salary << " PLN\n";
            }

            Employee::Employee(
                std::string name,
                int age,
                double salary
            )  : name(std::move(name)), age(age), salary(salary){
                logger.debug() 
                    << "Employee [" 
                    << name   << ", "
                    << age    << ", " 
                    << salary << ", " 
                    << "] - created successfully\n";
            }

            void Stats::show_stats() const {
                logger.debug() 
                    << "Stats: [HP: " << hp
                    << " | ATK: " << attack
                    << " | DEF: " << defense << "]\n";
            }

            void Player::introduce() const {
                logger.debug() 
                    << "Player: " << name 
                    << " (lvl " << level << ")\n";
                stats.show_stats();
            }

            void StructuresPlayground::creation_ways(){
                logger.info() << "[Structure creation]\n";
                Employee default_one;
                // mamy dostep wiec możemy ustawiać wartości
                default_one.name = "default_one";
                default_one.age = 31;
                default_one.salary = 512612.55;
                logger.info() 
                    << "Employee " << default_one.name 
                    << " earns " << default_one.salary << " PLN\n";
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
            
            void StructuresPlayground::nested_structs(){
                logger.info() << "[NEsted Structures]\n";
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
        }

/*---------------ClassKnow::Inheritance NAMESPACE---------------------------*/
        namespace Inheritance {

/*----------Inheritance::Animal class methods------------*/
            Animal::Animal(int legs)
                : _legs(legs){
                logger.debug() << "Animal created\n";
            }

/*----------Inheritance::Dog class methods------------*/
            Dog::Dog() : Animal(4) {
                 // default value for base construct
                _name = "Burek";
                logger.debug() 
                    << "Default dog created\n";
            }

            Dog::Dog(std::string name)
                : Animal(4), _name(std::move(name))  {
                logger.debug() 
                    << "Regular dog created\n";
            }

            Dog::Dog(int legs, std::string name)
                : Animal(legs), _name(std::move(name)){
                logger.debug() 
                    << "Dog with amount of legs\n";
            }

            void Dog::introduce(){
                logger.debug() 
                    << "Dog " << _name 
                    << ", legs: " << count_legs() << '\n'; 
            }
            void inheritance_introduction(){
                logger.info() << "[INHERITANCE INTRODUCTION]\n";
                Inheritance::Dog burek;
                burek.introduce();    
                Inheritance::Dog drago("Drago");
                drago.introduce();       
                Inheritance::Dog diff(3, "Damaged");
                diff.introduce();
            }
        }

/*---------------ClassKnow::Polymorphism NAMESPACE---------------------------*/
        namespace Polymorphism {

/*----------Polymorphism::CastingPlayground class methods------------*/

            void broadcast(const Notifications& notifications, const std::string& message){
                for (const auto& notify: notifications){
                    notify->send(message);
                }
            }

            void pipeline(
                const std::vector<std::unique_ptr<IProcessor>>& steps,
                const std::string& input_text
            ){
                for (const auto& step: steps){
                    step->process(input_text);
                }
            }

            void show_polymorphism(){
                logger.debug() << "[Polymorhpysm INTROCUTION]\n";
                Notifications notifications;
                notifications.push_back(
                    std::make_unique<EmailNotification>("golo338@gmail.com")
                );
                notifications.push_back(
                    std::make_unique<SmsNotification>("golo338@gmail.com")
                );
                logger.debug()
                    << "Brodcast is starting\n";
                broadcast(notifications, "Senor, como esta uested?");
                // --------------
                logger.debug()
                    << "Interface pipeline started:\n";
                std::vector<std::unique_ptr<IProcessor>> steps;
                steps.push_back(std::make_unique<Compressor>());
                steps.push_back(std::make_unique<Encryptor>());
                steps.push_back(std::make_unique<Logger>());

                pipeline(steps, "Confidential data");
            }
        }
    }

/*----------------ExceptionsKnow NAMESPACE---------------------------*/
    namespace ExceptionsKnow {

/*----------ExceptionsKnow::ExceptionHandling class methods------------*/
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
                << "[Code: " << _code << " ]\n"
                << "[Message (" << _message << ")" 
                << " called in function " << _function
                << "() in file" << _file << " at line " << _line << std::endl;
                
            _what = exception_message.str();
        }

        void ExceptionHandling::throwing_one(){
            if (_arg < 0) {
                throw std::invalid_argument("Arg must be >= 0");
            }
            else if (_arg == 5){
                throw CustomException("Should not be 5");
            }
            else {
                THROW_CUSTOM("Other exception type", 1111);
            }
        }
        void ExceptionPlayground::simple_throw() {
            logger.debug() 
                << "Forced Invalid Argument Exception: \n";
            try {
                ExceptionHandling handling(-2);
            }
            catch(const std::invalid_argument& arg_err){
                logger.error() 
                    << "Argument error: " 
                        << arg_err.what() << "\n";
            }
            catch(const std::exception& reg_err){
                logger.error() 
                    << "Other error: " 
                        << reg_err.what() << "\n";
            }
            catch(...){
                logger.error() << "Unknown error\n";
            }
        }

        void ExceptionPlayground::custom_throw() {
            logger.debug() 
                << "Custom Exception Handling: \n";
            try {
                ExceptionHandling handling_custom(5);
            }
            catch(const CustomException::exception& custom_err){
                logger.error() << "Custom error: " << custom_err.what() << "\n";
            }
        }

        void ExceptionPlayground::custom_with_specific_message() {
            try {
                ExceptionHandling handling_custom(12);
            }
            catch(const CustomWithFields& custom_adv_err){
                logger.error() << "Custom error: " << custom_adv_err.what() << "\n";
            }
        }
    }

/*----------------StringKnow NAMESPACE---------------------------*/
    namespace StringKnow {

/*----------StringKnow::StringOperation class methods------------*/
        StringOperation::StringOperation(std::string base)
            : base_text(base) {}
        
        void StringOperation::access_string_attributes(){
            logger.info() << "[Access to strings]\n";
            int word_buffor_size = base_text.size();
            int word_length = base_text.length();
            bool is_word_empty = base_text.empty();
            char first_word_sign = base_text.front();
            const char* inner_buffor_pointer = base_text.data();
            const char* save_ended_with_null = base_text.c_str();
            logger.debug()
                << "Buffor size: "    << word_buffor_size     << '\n'
                << "Word Length: "    << word_length          << '\n'
                << "Is text empty: "  << is_word_empty        << '\n'
                << "String index: "   << base_text[0]         << '\n'
                << "First char/id: "  << first_word_sign      << '\n'
                << "Last char/id: "   << base_text.back()     << '\n'
                << "Inner pointer: "  << inner_buffor_pointer << '\n'
                << "Sav=ly ended:"    << inner_buffor_pointer << '\n';
            
            // formatowanie +20
            #if __has_include(<format>) && __cplusplus >= 202002L
                #include <format>
                std::string message = std::format("{} {}", "data", "data")
            #endif
        }

        void StringOperation::modification_without_return(){
            logger.info() << "[String modification without return]\n";
            std::string backup = base_text;
            log_modification(
                "push_back() dopisanie znaku na koncu",
                backup,
                [](std::string& str){ str.push_back('!'); }
            );
            log_modification(
                "+= dodawanie słów do siebie",
                backup,
                [](std::string& str){ str += "and more | "; }
            );
            log_modification(
                "append(str, 10) dodawanie ze sprecyzowaniem długości dodawanej",
                backup,
                [](std::string& str){ str.append("add at | the end", 10); }
            );
            log_modification(
                "insert(str, 10), wrzucenie w dane miejsce",
                backup,
                [](std::string& str){ str.insert(5, "in the middle | "); }
            );
            log_modification(
                "erase(0, 4), czyszczenie <od, do>",
                backup,
                [](std::string& str){ str.erase(0, 4); }
            );
            log_modification(
                "replace(1, 5, str), podmiana fragmentu na innych",
                backup,
                [](std::string& str){ str.replace(1, 5, "some"); }
            );
        }

        void StringOperation::modification_with_return(){
            logger.info() << "[String modification with return]\n"; 
            // base_text.clear();
            std::string str_fragment = base_text.substr(0, 5); 
            logger.debug() 
                << "substr(from, to) bierze frament, wycina  i zwraca go:  "
                << str_fragment << '\n';
            std::string small_frgament = base_text.substr(4, 2);
            logger.debug() 
                << "substr(4, 2): " << small_frgament << '\n';
            
            std::string from_to_the_rest = base_text.substr(7);
            logger.debug()
                << "substr(6), od do konca: " << from_to_the_rest << '\n';

            base_text.reserve(256); // rezerwacja pamieci - zmienia capacity
            char a_sign = 'A';
            char lower_case = std::tolower(a_sign);
            char upper_case = std::toupper(lower_case);
        }

        void StringOperation::searching(){
            logger.info() << "[Searching inside string]\n";
            logger.debug()
                << "find(char) zwraca pozycje wystapienia znaku\n";
            auto sign_position = base_text.find('=');
            if (sign_position != std::string::npos){
                std::string before_eq = base_text.substr(0, sign_position);            // [0, pos)
                std::string after_eq  = base_text.substr(sign_position + 1);
                logger.debug() 
                    << "Before sign: " << before_eq << '\n'
                    << "After sign: "  << after_eq << '\n';
            }
            logger.debug()
                << "find(char, nr) szuka znaku, ale od konkretnej pozycji\n";
            size_t dash_pos = base_text.find('-', 15);
            if (dash_pos != std::string::npos) {
                logger.debug()
                    << "Found '-' at position: " << dash_pos << '\n'
                    << "Fragment from there: " << base_text.substr(dash_pos) << '\n';
            } 
            logger.debug() << "Find variants:\n";
            size_t pos_from_end = base_text.rfind('='); 
            if (pos_from_end != std::string::npos) {
                logger.debug()
                    << "Last = at position " << pos_from_end << '\n'
                    << "Tail after last '=':" << base_text.substr(pos_from_end + 1) << '\n';
            }
            size_t first_set = base_text.find_first_of(",;=");
            if (first_set != std::string::npos) {
                logger.debug()
                    << "First one of [',', ';', '='] at: " << first_set
                    << " (char: '" << base_text[first_set] << "')\n";
            }

            size_t first_not_ws = base_text.find_first_not_of("\r \n");
            if (first_not_ws != std::string::npos) {
                logger.debug()
                    << "First non whitespace at: " << first_not_ws
                    << " (char: '" << base_text[first_not_ws] << "')\n";
            }
            // find_last_of | .find_last_not_of  tak samo tylko ostatni
            
            // boolean - true jesli zaczyna sie
            bool starts_conf = base_text.starts_with("conf");
            bool ends_yaml   = base_text.ends_with(".yaml");
            logger.debug()
                << "starts_with(conf): " << std::boolalpha << starts_conf << '\n'
                << "ends_with(.yaml): "  << std::boolalpha << ends_yaml   << '\n';
            // base_text.contains("fig") 
        }
        void StringOperation::triming_white_spaces(){
            const std::string_view white_spaces_group = " \t\r\n";
            size_t left_position = base_text.find_first_not_of(white_spaces_group);
            size_t right_position = base_text.find_last_not_of(white_spaces_group);
            logger.info() << "Whitespace from left found in position: " << left_position << std::endl;
            logger.info() << "Whitespace from right found in position: " << right_position << std::endl;
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
            logger.info() << "Left trimmed: " << left_trimmed_string << std::endl;
            logger.info() << "Right trimmed: " << right_trimmed_string << std::endl;
        }
    }

/*----------------RegexKnowleadge NAMESPACE---------------------------*/
    namespace RegexKnowleadge {
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
/*----------RegexKnowleadge::RegexPlayground class methods------------*/
        void RegexPlayground::sign_classes(){
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
            logger.info() << dots << "[Regex sign classes]\n";
            std::string text = "User42 id=77";
            std::regex digits(R"(\d+)");
            if (std::regex_search(text, digits)){
                logger.debug() << "Found digits\n";
            }
            std::regex word_or_char(R"(\W+)");
            if (std::regex_search(text, word_or_char)){
                logger.debug() << "Found word characters\n";
            }
            std::regex white_spaces(R"(\s+)");
            if (std::regex_search(text, white_spaces)){
                logger.debug() << "Found whitespace\n";
            }
            
        }
       
        void RegexPlayground::anchors(){
            /*
            | Wzorzec | Znaczenie        |
            | ------- | ---------------- |
            | `^`     | początek stringa |
            | `$`     | koniec stringa   |
            */
            logger.info() << dots << "[Regex anchors]" << '\n';
            std::string good = "HelloWorld";
            std::string bad  = "123Hello";

            std::regex starts_hello(R"(^Hello)");
            std::regex ends_world(R"(World$)");

            if (std::regex_match(good, starts_hello))
                logger.debug() << "'good' starts with Hello\n";

            if (!std::regex_match(bad, starts_hello))
                logger.debug() << "'bad' does NOT start with Hello\n";

            if (std::regex_match(good, ends_world))
                logger.debug() << "'good' ends with World\n";
        }

        void RegexPlayground::qualifiers(){
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
            logger.info() << dots << "[Regex qualifiers]" << '\n';
            std::regex zero_or_more(R"(go*)"); // g, go, goo, gooo
            std::regex one_or_more(R"(go+)");
            std::regex optional(R"(colou?r)"); // color OR colour

            std::string ex1 = "goooal";
            std::string ex2 = "color";
            std::string ex3 = "colour";

            if (std::regex_search(ex1, one_or_more))
                logger.debug() << "Found 'go+' pattern\n";

            if (std::regex_search(ex2, optional))
                logger.debug() << "'color' matches colour/ color variant\n";

            if (std::regex_search(ex3, optional))
                logger.debug() << "'colour' matches colour/ color variant\n";

            // {n,m}
            std::regex exactly_three(R"(a{3})"); // exactly "aaa"
            if (std::regex_search("caaaab", exactly_three))
                logger.debug() << "Found exactly 'aaa'\n";
        } 

        void RegexPlayground::groups_alternatives(){
            /*
            | Wzorzec     | Znaczenie                                   |                   |
            | ----------- | ------------------------------------------- | ----------------- |
            | `( ... )`   | grupa (możesz ją odwoływać jako `$1`, `$2`) |                   |
            | `a          | b`                                          | albo `a` albo `b` |
            | `(?: ... )` | grupa bez przechwytywania                   |                   |
            */
            logger.info() << dots << "[Regex groups & alternatives]" << '\n';
            std::string people = "Jan:10, Ala:20, Olek:30";
            // ( ... ) – grupy przechwytywujące
            std::regex pair(R"((\w+):(\d+))");
            std::smatch m;
            if (std::regex_search(people, m, pair)) {
                logger.debug()
                    << "Name: " << m[1] << ", score: " << m[2] << '\n';
            }
            // Alternatywa: a|b|c
            std::regex alt(R"(Jan|Ala|Olek)");
            if (std::regex_search(people, alt))
                logger.debug() << "Found name using alternation\n";
            // (?: ... ) – grupa bez przechwytywania
            std::regex noncap(R"((?:Jan|Ala):\d+)");
            if (std::regex_search(people, noncap))
                logger.debug() << "Found using non-capturing group\n";
        }
        
        void RegexPlayground::signs_sets(){
            /*
            | Wzorzec  | Znaczenie               |
            | -------- | ----------------------- |
            | `[abc]`  | a LUB b LUB c           |
            | `[a-z]`  | małe litery a–z         |
            | `[A-Z]`  | wielkie litery          |
            | `[0-9]`  | tylko cyfry             |
            | `[^abc]` | wszystko oprócz a, b, c |
            */
            logger.info() << dots << "[Regex sign sets]" << '\n';
            std::string sample = "FileA.txt";

            // [A-Z] – wielka litera A-Z
            std::regex capital(R"([A-Z])");
            if (std::regex_search(sample, capital))
                logger.debug() << "Found capital letter\n";

            // [^abc] – znak nie będący a, b, c
            std::regex not_abc(R"([^abc])");
            if (std::regex_search("z", not_abc))
                logger.debug() << "'z' is NOT a, b, or c\n";

            // [0-9] – cyfry
            std::regex digits(R"([0-9]+)");
            if (std::regex_search("Room42", digits))
                logger.debug() << "Found digits in string\n";
        }
        
        void RegexPlayground::signs_escape(){
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
            logger.info() << dots << "[Regex escaping]" << '\n';
            std::string file = "config.yaml";

            // \. – literalna kropka
            std::regex ext(R"(\.yaml$)");
            if (std::regex_search(file, ext))
                logger.debug() << "File ends with .yaml\n";

            // \+ – literalny plus
            std::regex plus(R"(\+)");
            if (std::regex_search("a+b", plus))
                logger.debug() << "Found literal plus\n";

            // \? – literalny znak zapytania
            std::regex q(R"(\?)");
            if (std::regex_search("Is this ok?", q))
                logger.debug() << "Found literal question mark\n";
        }

        void RegexPlayground::match(){
            logger.info() << dots << "[Regex FULL match]" << '\n';
            // 1. Email – cały string musi pasować
            std::string email = "admin@example.com";
            std::regex email_pattern(R"(^\w+@\w+\.\w+$)");
            if (std::regex_match(email, email_pattern)) {
                logger.debug() << "Email is valid\n";
            } else {
                logger.debug() << "Invalid email format\n";
            }
            // 2. Data YYYY-MM-DD
            std::string date = "2025-12-02";
            std::regex date_pattern(R"(^\d{4}-\d{2}-\d{2}$)");

            if (std::regex_match(date, date_pattern)) {
                logger.debug() << "Correct date format\n";
            }
            // 3. Tylko litery i cyfry
            std::string name = "User42";
            std::regex alnum(R"(^[A-Za-z0-9]+$)");
            if (std::regex_match(name, alnum))
                logger.debug() << "Name contains only letters and digits\n";
        }
        
        void RegexPlayground::search() {
            logger.info() << dots << "[Regex SEARCH]" << '\n';

            std::string log_line = "User: admin logged at 2025-12-02 with id=42";

            // 1. Szukanie daty wewnątrz tekstu
            std::regex date(R"(\d{4}-\d{2}-\d{2})");
            if (std::regex_search(log_line, date))
                logger.debug() << "Found date in log line\n";

            // 2. Wyciąganie grup (user + id)
            std::regex info(R"(User:\s*(\w+).*id=(\d+))");
            std::smatch m;
            if (std::regex_search(log_line, m, info)) {
                logger.debug() << "User: " << m[1] << '\n';
                logger.debug() << "Id:   " << m[2] << '\n';
            }

            // 3. Iterowanie po wielu dopasowaniach
            std::string scores = "Jan:10, Ala:20, Olek:30";
            std::regex pair(R"((\w+):(\d+))");
            for (std::sregex_iterator it(
                    scores.begin(),
                    scores.end(),
                    pair
                ), end; it != end; ++it){
                logger.debug()
                    << "Name: " << (*it)[1]
                    << ", Score: " << (*it)[2] << '\n';
            }
        }

        void RegexPlayground::replace_match() {
            logger.info() << dots << "[Regex REPLACE]" << '\n';
            // --- 1. Prosta zamiana słowa ---
            std::string text = "Ala ma kota";
            std::regex r_name(R"(Ala)");
            std::string changed = std::regex_replace(text, r_name, "Ola");
            logger.debug() << "Changed: " << changed << '\n'; // Ola ma kota

            // --- 2. Zamiana z użyciem grup ---
            std::string vars = "x=10; y=20; z=30;";
            std::regex group(R"((\w)=(\d+))");

            // $1 – nazwa, $2 – liczba
            std::string formatted = std::regex_replace(vars, group, "$1 -> $2");
            logger.debug() << "Formatted vars: " << formatted << '\n';
            // x -> 10; y -> 20; z -> 30;

            // --- 3. Maskowanie hasła ---
            std::string log = "login ok, password=SuperSecret123";
            std::regex pass(R"(password=\w+)");
            std::string masked = std::regex_replace(log, pass, "password=******");
            logger.debug() << "Masked: " << masked << '\n';
        }
    }

    namespace Collections {
        // --------------------------------//
        //       VECTOR EXAMPLES           //
        // --------------------------------//
        std::vector<int> VectorExamples::creation_ways(){
            std::vector<int> empty_vec; // pusty
            std::vector<int> zeros(5); // inicjalizuje zerami
            std::vector<int> numbers(5, 42); //  5 elementów liczby 42
            std::vector<int> inicialized{1,5,7,12}; // lista inicjalizacyjna

            // kopia i przeniesienie
            std::vector<int> copy = zeros;
            std::vector<int> moved = std::move(numbers);

            logger.debug() << copy.size() << " " << copy.capacity() << "\n";
            return inicialized;
        }
        
        void VectorExamples::access_to_elements(std::vector<int> numbers){
            logger.info() << "Without checking index:" 
                << numbers[0] << std::endl;
            logger.info() << "With checking index:" 
                << numbers.at(0) << std::endl; // sprawdza czy jest zakres inaczej out_of_range
            logger.info() << "First one" 
                << numbers.front() << std::endl;
            logger.info() << "Last one" 
                << numbers.back() << std::endl;
        }
        void VectorExamples::modification() {
            std::vector<float> holds;
            /*
                Dodają oba na koniec vectora
                >push_back
                    - dodaje gotowy obiektu kopiuje lub przenosi
                    - jesli chce go dodać na miejscui to emplace
                >emplace_back
                    - tworzy obiekt bezpośrednio w wektorze
                    - jesli mam obiekt i chce go dodać to push_back
            */
            holds.push_back(10.5); 
            holds.emplace_back(20.15);
            // wstawianie w dane miejsce
            int index = 2;
            holds.insert(holds.begin() + index, 99 );
            // usuniecie z danego indexu
            holds.erase(holds.begin() + index );
            // czyszczenie bez zmiany capacity
            holds.clear();
            // gdy zna sie przybliżoną wartośc to mamy
            holds.reserve(100); // docelowe capacity 100
            holds.resize(5);// ustawia dany rozmiar
        
            // zwrócenie danej ilości elementów / ciecie
            std::vector<int> v = {0,1,2,3,4,5,6,7,8,9,10,11,12};
            // elementy od 0 do 10 
            std::vector<int> sub_vector(v.begin(), v.begin() + 11); 
        }

        void VectorExamples::iteration(){
            std::vector<double> doubles{12.667, 512.51267, -133.5787};
            /*
                size_t - typ liczbowy, rodzaj zmiennej do liczb całkowitych
                    ale tylko dodatnich
                Używany do rozmiarów, indeksów, długości, liczby bitów
                    zamiast unsigned - na różnych systemach różna ilość bitów
                    to jest tutaj size_t  
            */
            // poprzez indeksy
            for (std::size_t index = 0; index < doubles.size(); ++index) {
                logger.debug() << "Index: " << index << " element " << doubles[index] << std::endl;
            }

            // range-for - read only 
            for (double dub: doubles) {
                logger.error() << "Read only numbers: " << dub << std::endl;
            }
            // range for - z modyfikacją(poprzez referencje)
            for (double& dub: doubles) {
                dub *= 3;
                logger.warn() << "Changed numbers: " << dub << std::endl;
            }
            /*
                Iterator
                    coś w rodzaju wskaźnika
                    pokazuje na który element kontenera akutalnie patrzymy
                    Możemy zacząć od początku begin | końca end
                    Przejść dalej po kontenerze (kolejny adres) ++it
                    Zobaczyć zawartość *it ->it
            */
            for (auto it = doubles.begin(); it != doubles.end(); it++){
                logger.info() << "Iter: " << *it << std::endl;
            }
        }
        void VectorExamples::sort_and_algorithms(){
            std::vector<unsigned int> positive{5,6,12,73,8};
            std::sort(
                positive.begin(), positive.end()
            ); // rosnąco 
            std::sort(
                positive.begin(), positive.end(),
                std::greater<>()
            ); // malejąco
            std::stable_sort(positive.begin(), positive.end()); // stabilne
            // mapowanie wartości
            std::transform(
                positive.begin(), positive.end(), positive.begin(),
                [](unsigned int x) {
                    return x * 10;
                }
            );
            // sumowanie
            int sum = std::accumulate(positive.begin(), positive.end(), 0);
            // szukanie
            auto it = std::find(positive.begin(), positive.end(), 4);
            /*
                Sortowanie obiektów, przez funkcje sprawdzającą
            */
            struct Player {
                std::string name;
                int score;
            };
            std::vector<Player> players = {
                {"Ala", 10}, {"Ola", 25}, {"Ela", 15}
            };
            std::sort(players.begin(), players.end(),
                [](const Player& first, const Player& second){
                    return first.score > second.score;
                }
            );


        }
        // --------------------------------//
        //         MAP EXAMPLES            //
        // --------------------------------//

        std::map<int, int> MapExamples::creation_ways(){
            std::map<int, int> empty_scores; // pusta mapa
            std::map<int, int> filled_scores = {
                {1, 15},
                {2, 56},
                {3, 79},
                {4, 37}
            }; // gotowe dane
            // kopia
            std::map<int, int> copy = filled_scores;
            // przeniesienie (oddanie bez kopiowania)
            std::map<int, int> moved = std::move(empty_scores);
            logger.debug() << "Copy size: " << copy.size() << std::endl;
            
            // dodawanie nowych elementów
            filled_scores[12] = 51;
            // check if key exists
            bool is_key_in = filled_scores.contains(1);
            int element = filled_scores[1];
            int element_save = filled_scores.at(2);
            auto searching = filled_scores.find(1);
            if (searching != filled_scores.end()){
                int element = searching->second;
            }
            return copy;
        }

        void MapExamples::pair_know(){
            std::pair<std::string, int> single_score = {"Bob", 561};
            logger.debug() << single_score.first << std::endl;
            logger.debug() << single_score.second << std::endl;
            
            // po inicjalizacji moge 
            std::pair<int, int> result_numbers;
            result_numbers.first = 12;
            result_numbers.second = 51; 
            //albo
            result_numbers = std::make_pair(12, 51);
            // jak chcemy zwrócić pustą pare to 
            // return {};
        }

        void MapExamples::access_to_elements(std::map<int, int> scores){
            scores[0] = 12; // utworzy jak nie ma
            scores[1] = 51; // nadpisze 

            logger.info() << "By operator []:" 
                << scores[1] << std::endl;
            logger.info() << "With checking index:" 
                << scores.at(0) << std::endl; // sprawdza czy jest zakres inaczej out_of_range
        }

        void MapExamples::modification(){
            std::map<int, int> scores;
            // dodanie nowego
            scores[1] = 12;  // jeśli nie ma, doda
            scores[5] = 20;  // jeśli jest, nadpisze
            // alternatywy
            scores.insert({52, 51});          // wstaw (nie nadpisze)
            scores.emplace(6, 65);            // tworzy bezpośrednio w mapie
            scores.insert_or_assign(67, 100); // C17 -doda lub nadpisze
            scores.try_emplace(2, 200);       // doda tylko jeśli nie istnieje
            /*
            map.find()
                -szuka elementu o danym kluczu i zwraca iterator
                jeśli znalazł -> iterator do elementu
                jesli nie - to scores.end()
            */
            if (scores.find(1) != scores.end()){
                logger.debug() << "1 not exists\n";
            }
            // 20 contains
            // if (scores.contains(1)){
                // logger.debug() << "1 exists\n";
            // }
            // usuwanie
            scores.erase(1);
            // łączenie dwóch map
            std::map<int, int> results = {
                {51, 25},
                {66, 2}
            };
            scores.merge(results);
        }
        void MapExamples::iteration(std::map<int, int> scores){
            for (auto &pair : scores) {
                logger.debug() << pair.first << " => " << pair.second << std::endl;
            }

            // (C++17)
            for (auto &[name, score] : scores) {
                logger.debug() << name << " ma wynik " << score << std::endl;
            }
        }
        void MapExamples::sort_and_algorithms(){}

        void show_all_methods() {
            VectorExamples vec_examples;
            std::vector<int> numbers = vec_examples.creation_ways();
            vec_examples.access_to_elements(numbers);
            vec_examples.iteration();
            vec_examples.sort_and_algorithms();
            
            MapExamples map_examples;
            std::map<int, int> scores = map_examples.creation_ways();
            map_examples.access_to_elements(scores);
            map_examples.modification();
            map_examples.iteration(scores);
            // map_examples.sort_and_algorithms();
        }
    }
    namespace Functions {
        void LambdaFunction::syntax(){
            /*
                [parametry_zewnetrznye] 
                    co  funkcja ma widzieć (czyli capture list)
                (argumenty_lambdy) 
                    - argumenty jak w normalnej funkcji
                -> typ - opcjonalny typ zwracany
                {} kod który wykona lambda
                 --- całość
                [parametry_zewętrzny](argumenty_lambdy) -> zwracany_typ {
                    ciało funkcji
                }
            */
           // od razu wykonana (bo () na końcu).
            []() { logger.debug() << "In the lambda\n"; }(); 
            // z zaczepieniem o zmienną
            auto hook = []() {
                logger.debug() << "With hook\n";
            };
            hook(); // wywołanie
            // z argumentami
            auto add = [](int first, int second){
                return first + second;
            };
            logger.debug() << add(1,51) << std::endl;
            // z sprecyzowanym typem
            auto devide = [](int first, int second) -> double {
                return static_cast<double>(first) / second;
            };
            logger.debug() << devide(1,51) << std::endl;
            //  z capture list - zmienne z zewnętrznego zakresu
            int threshold = 10;
            auto exceeds = [threshold](int max) -> bool {
                return max < threshold;
            };
            logger.debug() << "Exceeds "<< std::boolalpha << exceeds(15) << std::endl;
            // łapanie zmiennych przez referencje
            int counter = 1;
            auto increment = [&counter]() -> void {
                counter++;
            };
            logger.debug() << "Counter before " << counter <<  std::endl;
            increment();
            logger.debug() << "Counter aftert" << counter <<  std::endl;
            /*
                [=] -- łapanie wszystkie przez kopie wartości
                [&] -- łapanie przez referencje
                [x, &y] - przez wartość, przez referencje
            */
        }
        /*
        Przyjcie funckji jako callbacku
            funckja przyjmuje parametr int i nie wzraca nic
                syntax
                    std::function<typ_zwrotny(parametry...)>

        */
        void LambdaFunction::repeat(int amount, const std::function<void(int)>& fun){
            for (int i = 0; i< amount; i++){
                fun(i);
            }
        }
        void print_square(int radius){
            logger.debug() << "Square: " << radius * radius << std::endl;
        }

        void LambdaFunction::show_function_examples(){
            repeat(5, print_square);
            repeat(5,
                [](int i) {
                    logger.debug() << "With lambda\n";
                }
            );
            // jeden parametr
            std::function<void(int)> single_param_call;
            single_param_call = [] (int single) {
                logger.debug() << "Number: " << single << std::endl;
            };
            // double
            std::function<void(int, std::string)> double_param_call;
            // returned type
            std::function<int(double, int)> with_return_type;
            // without any 
            std::function<void()> no_param;
        }

        void UsefulFunction::checking_int(){    
            /*
                isdigit(int char)
                    z <cctype>
                sprawdza czy dany znak reprezentuje cyfre
                    '0' - '9'
            */
            logger.debug() << std::isdigit('5') << "\n";  // 1 (true)
            logger.debug() << std::isdigit('a') << "\n";  // 0 (false)
            logger.debug() << std::isdigit(53) << "\n";   // też true, bo 53 to kod ASCII '5'
            // std::isdigit(123); // NIE działa jak myślisz
        }
        
        void show_all_functions(){
            LambdaFunction lambda;
            lambda.syntax();
            lambda.show_function_examples();
            UsefulFunction useful;
            useful.checking_int();
        }
    }

};
