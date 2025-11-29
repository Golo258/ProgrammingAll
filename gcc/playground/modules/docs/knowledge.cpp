// ------------------------
#include <docs/knowledge.hpp>
/*
    Creating Exceptions
*/

namespace Knowledge {
    
/*#--------------StreamsManagement NAMESPACE---------------------------------#*/
    namespace StreamsManagement {
        /*-------------StandardStream methods----------------*/
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

        /*-------------FileStream methods----------------*/
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

        /*-------------MemoryStream methods----------------*/
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

        /*-------------FileSystemManagment methods----------------*/
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

/*#--------------AliasesAndTypes NAMESPACE---------------------------------#*/
    namespace AliasesAndTypes {

    /*-------------AliasesPlayground methods----------------*/
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
    /*-------------CastingPlayground methods----------------*/
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

    /*-------------Pointers methods----------------*/
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
    /*#--------------Enums NAMESPACE---------------------------------#*/
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
            void show_tamples(){
                add_int(1,1);
                add_double(1.5, 1.5);

                // z użyciem templata
                int add_int = add(1,2);
                double add_double = add(1.5, 15.7);
                std::string add_string = add(
                    std::string("Hi "), std::string("there")
                );
                auto bigger = max_of(5, 9);        // int
                auto longer = max_of<std::string>("his", "yo"); // string
                auto different = add_different(
                    12, 515.5125
                );
                // dowolny typ pudełka
                Box<int> health(100);
                Box<double> accuracy(99.5);
                Box<std::string> nickname("Golo");

                logger.debug() << "HP: " << health.get() << "\n";
                logger.debug() << "ACC: " << accuracy.get() << "\n";
                logger.debug() << "Nick: " << nickname.get() << "\n";
                
                Pair<std::string, int> player_score("Grzesiuniunia", 999);
                logger.debug() << player_score.get_key() << ": " 
                          << player_score.get_value() << "\n";
                
                Container<int> numbers(3);
                numbers.add(10);
                numbers.add(1256);
                numbers.print_all_items();
                Container<int> numbers_inicialized{10, 1256};
                numbers_inicialized.print_all_items();
                Container<int> filled_zeros(3, 0);
                filled_zeros.print_all_items();
            }
        }
    }
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
            private:
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
    namespace ClassKnow {

        namespace Specificators {
            //--------------------
            void PrivateSpec::start(){
                velocity = 50; // this.velocity
            }
            void PrivateSpec::compare(const PrivateSpec& diff){
                logger.debug() << "Comparing: [" << velocity - diff.velocity << "]\n";  
                velocity = diff.velocity;
            }
            //--------------------
            void PublicSpec::set_and_show(){
                scores = 51.2;
                logger.info() << "Scores: " << scores << std::endl;
            }
            //--------------------
            void ProtectedSpec::show_shield() const {
                logger.debug() << "Shield value: " << shield << std::endl;
            }
            void ProtectedChild::damage() {
                shield -= 10; // has access
                show_shield(); // has access
            }
        }
        namespace LifeCycle {
            // -----------------------
            Constructor::Constructor(){
                _name = "none";
                logger.info() << "Default object created\n";
            }
            Constructor::Constructor(std::string name){
                _name = name;
                logger.info() << "Object with " << name << " name created\n";
            }
            Constructor::Constructor(std::string name, int threshold)
                : _name(name), _threshold(threshold){
                logger.info() << "Object inicialized with list (" << name << ", " << threshold <<  " params created\n";
            }
            // -----------------------
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
        }
        namespace Utility {
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
            // 

            void AccessGates::
            set_amount(int new_amount){
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
        }
        namespace Structures {
            void Employee::print() const {
                logger.debug() << name 
                    << " (" << age << " lat) - " 
                    << salary << " PLN\n";
            }
            Employee::Employee(std::string name, int age, double salary)
                : name(std::move(name)), age(age), salary(salary)
            {
                logger.debug() << "Employee " << name << "created successfully\n";
            }
            void Stats::show_stats() const {
                logger.debug() << "HP: " << hp
                      << " | ATK: " << attack
                      << " | DEF: " << defense << '\n';
            }
            void Player::introduce() const {
                logger.debug() << "Player: " << name << " (lvl " << level << ")\n";
                stats.show_stats();
            }
            void show_player(const Player& player){
                logger.debug() << "=== PLAYER ===" << std::endl;
                player.introduce();
                // player.level++;  object == const - not allowed
            }
            void creation_and_access(){
                // poprzez pojedyncze wstawianie wartości
                Employee man;
                man.name = "Man";
                man.age = 31;
                man.salary = 512612.55;
                logger.info() << "Employee " << man.name << " earns " << man.salary << " PLN\n";
                // poprzez liste inicjalizacyjną
                Employee second{
                    "Mark", 53, 4666.66
                };
                second.print();
                // braced initialization
                Employee basia = {"Basia", 22, 7200.0};
                basia.print();
                // z konstruktorem
                Employee john("John", 21, 215.22);
                john.print();
                // zagnieżdżone struktury
                Stats base_stats{100, 25, 10};
                Player mage{"Lord", 7, base_stats};
                // inicjalizacja pojedyncza 
                Player warior{
                    "Odyn", // name
                    7,                // level
                    {120, 40, 15}     // stats: hp, attack, defense
                };
                mage.introduce();
                warior.introduce();
                // zmiana statystyk
                mage.stats.hp = 50;
                mage.stats.show_stats();
            }
            void all(){
                creation_and_access();
            }
        }
        namespace Inheritance {
            Animal::Animal(int legs)
                : _legs(legs){
                logger.debug() << "Animal created\n";
            }
            Dog::Dog()
                : Animal(4) // default value for base construct
            {
                _name = "Burek";
                logger.debug() << "Default dog created\n";
            }
            Dog::Dog(std::string name)
                : Animal(4), _name(std::move(name))  // default value for base construct
            {
                logger.debug() << "Regular dog created\n";
            }
            Dog::Dog(int legs, std::string name)
                : Animal(legs), _name(std::move(name))
            {
                logger.debug() << "Dog with amount of legs\n";
            }
            int Animal::count_legs() {
                return _legs;
            }
            void Dog::introduce(){
                logger.debug() << "Dog " << _name 
                    << ", legs: " << count_legs() << "\n"; 
            }

        }
        namespace Polymorphism {
            void broadcast(
                const std::vector<
                    std::unique_ptr<Notification>
                >& notifications,
                const std::string& message  
            ){
                for (const auto& notif: notifications){
                    notif->send(message);
                }
            }

            void show_broadcast(){
                std::vector<
                    std::unique_ptr<Notification>
                > notifications;
                notifications.push_back(
                    std::make_unique<EmailNotification>("golo338@gmail.com")
                );
                notifications.push_back(
                    std::make_unique<SmsNotification>("golo338@gmail.com")
                );
                broadcast(notifications, "Senor, como esta uested?");
            }
            
            void pipeline(
                const std::vector<std::unique_ptr<IProcessor>>& steps,
                const std::string& input_text
            ){
                for (const auto& step: steps){
                    step->process(input_text);
                }
            }
            
            void show_pipeline_steps(){
                std::vector<std::unique_ptr<IProcessor>> steps;
                steps.push_back(std::make_unique<Compressor>());
                steps.push_back(std::make_unique<Encryptor>());
                steps.push_back(std::make_unique<Logger>());

                pipeline(steps, "Confidential data");
            }

        }
        void demonstrate_classes(){
            // --------------------------------
            Specificators::PrivateSpec first, second;
            first.start();
            /*
                Błąd kompilacji, nie można dostać się do prywatnego atrybutu
                second.velocity = 12;  
            */
            first.compare(second);
            first.compare(second); // after change 
            Specificators::PublicSpec allowed;
            // --------------------------------
            allowed.set_and_show();
            allowed.scores = 12.5;
            logger.debug() << "Allowed scores " << allowed.scores << std::endl;
            Specificators::ProtectedSpec family;
            family.show_shield();
            Specificators::ProtectedChild child;
            child.damage();
            // child.shield -= 10;  jak z private, błąd komplacji
            // --------------------------------
            LifeCycle::Constructor default_one;
            LifeCycle::Constructor with_parameter("Pretty");
            LifeCycle::Constructor inicialized_list("Not bad", 15);
            // --------------------------------
            LifeCycle::Destructor destructor;
            LifeCycle::Destructor destructor_witH_param("other.json");
            // --------------------------------
            Utility::AccessGates gates(5, 12);
            logger.info() << "Amount: " << gates.get_amount() << std::endl;
            logger.info() << "Size of gates: " << gates.get_gates().size() << std::endl;
            gates.set_amount(15);
            std::vector<int> new_gates{15, 62, 73, 21};
            gates.set_gates(new_gates);
            logger.info() << "Gates item: " << gates.get_gates().at(1) << std::endl;
            // --------------------------------
            // Inheritance
            Inheritance::Dog burek;
            burek.introduce();    
            Inheritance::Dog drago("Drago");
            drago.introduce();       
            Inheritance::Dog diff(3, "Damaged");
            diff.introduce();
            //Polymorphism 
            Polymorphism::show_broadcast();
            Polymorphism::show_pipeline_steps();
        }
        
    }
    namespace ExceptionsKnow {
        ExceptionHandling::ExceptionHandling(int arg)
            : _arg(arg) {
                throwing_one();
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
        void show_all_exceptions() {
            // --------------------------------------
            try{
                ExceptionHandling handling(-2);
            }
            catch(const std::invalid_argument& arg_err){
                logger.error() << "Argument error: " << arg_err.what() << "\n";
            }
            catch(const std::exception& reg_err){
                logger.error() << "Other error: " << reg_err.what() << "\n";
            }
            catch(...){
                logger.error() << "Unknown error\n";
            }
            // --------------------------------------
            // custom exception handling
            try{
                ExceptionHandling handling_custom(5);
            }
            catch(const CustomException::exception& custom_err){
                logger.error() << "Custom error: " << custom_err.what() << "\n";
            }
            // --------------------------------------
            // custom with fields
            try{
                ExceptionHandling handling_custom(12);
            }
            catch(const CustomWithFields& custom_adv_err){
                logger.error() << "Custom error: " << custom_adv_err.what() << "\n";
            }
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
            //  no i tworzymy wiadomośc błędu
            std::ostringstream exception_message; // bufor do wiadomosci
            // auto now = std::chrono::system_clock::now();
            // auto tt = std::chrono::system_clock::to_time_t(now);
            // std::tm tt{};
            // localtime_r(&tt, &tm);
            exception_message 
                // << "[" << std::put_time(&tm, "%F %T") << "] "
                << "[Code: " << _code << " ]\n"
                << "[Message (" << _message << ")" 
                << " called in function " << _function
                << "() in file" << _file << " at line " << _line << std::endl;
                
            _what = exception_message.str();
        }
    }
    namespace StringKnow {
        StringOperation::StringOperation(std::string base)
            : base_text(base) {}
        
        void StringOperation::access(){
            // rozmiar
            logger.info() << "size: "  << base_text.size() << std::endl;
            logger.info() << "empty: " << base_text.empty() << std::endl;
            //  dostęp
            logger.info() << "0: "     << base_text[0] << std::endl;
            logger.info() << "front: " << base_text.front() << std::endl;
            logger.info() << "back: "  << base_text.back() << std::endl;
            logger.info() << "data: "  << base_text.data() << std::endl;
            logger.info() << "c_str: " << base_text.c_str() << std::endl;
            // formatowanie +20
            // include <format>
            // std::string message = std::format("{} {}", "data", "data")
        }

        void StringOperation::modification(){
            std::string backup = base_text;
            base_text.push_back('!'); // dopięcie na koncu / char expected
            base_text += "and more"; // concatenate
            base_text.append(" with = specific width", 10); // 10 liczba znaków dodawanego string
            base_text.insert(5, "in the middle"); // wstawienie w dane miejsce
            base_text.erase(0, 4); // usuwa od 0 - 4
            base_text.replace(1, 5, "some"); // podmiana fragmentu
            // base_text.clear();
            logger.info() << "After replacement: " << base_text << std::endl;
            // bierze fragment i zwraca | zaczyna od 0 i bierze 5 znaków
            std::string repl = base_text.substr(0, 5); 
            // od 4 index, 2 znaki 
            std::string small_repl = base_text.substr(4, 2);
            // od 7 index, do końca 
            std::string repl_rest = base_text.substr(7);
            base_text.reserve(256); // rezerwacja pamieci
            // upper | lower
            char a_sign = 'A';
            char lower_case = std::tolower(a_sign);
            char upper_case = std::toupper(lower_case);
        }
        void StringOperation::searching(){
            auto sign_position = base_text.find('=');
            size_t pos = base_text.find('-', 15); // zaczyna od danego
            if (sign_position != std::string::npos){
                std::string key = base_text.substr(0, sign_position);            // [0, pos)
                std::string value = base_text.substr(sign_position + 1);
                logger.info() << "Key: " << key << std::endl;
                logger.info() << "Value: " << value << std::endl;
            }
            else {
                logger.error() << "= not found in base \n";
            }
            base_text.rfind('='); // od konca
            base_text.find_first_of(",;="); // szuka pierwszego z zestawu
            base_text.find_first_not_of("\r \n"); // który nie jest w zestawie 
            // find_last_of | .find_last_not_of  tak samo tylko ostatni
            
            // boolean - true jesli zaczyna sie
            base_text.starts_with("conf"); 
            base_text.ends_with(".yaml");
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

        /* Klasy regexowe:
            regex - wzorzec, kompilowany regex
            smatch - dopasowanie do stringa
            cmatch - dopasowanie do chara
            regex_match  - sprawdza czy cały string pasuje
            regex_search - szuka gdziekolwiek w stringu
            regex_replace - zamienia wzorzec na inny tekst

        */
        void StringOperation::regex_matching(){
            std::string text = "some == other and_different";
            // regex - tworzymy pattern do sprawdzenia tekstu
            std::regex pattern("other");
            //  przeszukujemy gdziekolwiek
            if (std::regex_search(text, pattern)){
                logger.debug() << "Other found in text\n";
            }

            // sprawdzanie całego stringa
            std::regex specific_pattern("^some [=]{2}.*");
            if (std::regex_match(text, specific_pattern)){
                logger.debug() << "Specific found\n";
            }
            // wyciąganie dopasowań
            // match[x] → grupy z nawiasów ()
            std::string data = "user: admin, id: 42";
            std::regex matching_pattern(R"(user:\s*(\w+),\s*id:\s*(\d+))");
            std::smatch match;
            if (std::regex_search(data, match, matching_pattern)) {
                logger.debug() << "Whole: " << match[0] << std::endl;
                logger.debug() << "User: " << match[1] << std::endl;
                logger.debug() << "Id: " << match[2] << std::endl;
            }
            // pisanie wzorców - najlepiej z literą R (raw string literal):
            std::regex r_date(R"(\d{2,4}-\d{2}-\d{2})"); // np. 2025-11-08
            // flagi, jako drugi argument, case insensitive
            std::regex r_case(R"(kot)", std::regex_constants::icase); 
            
            // Iterowanie po dopasowaniach
            std::string other = "Jan:10, Ala:20, Olek:30";
            std::regex r(R"((\w+):(\d+))");
            std::smatch m;
            auto it = std::sregex_iterator(other.begin(), other.end(), r);
            auto end = std::sregex_iterator();
            for (; it != end; it++){
                 logger.debug() << "Name: " << (*it)[1] << ", score: " << (*it)[2] << '\n';
            }
            // zamiana regex_replace
            std::regex r_numbs("Ala");
            std::string changed = std::regex_replace(other, r_numbs, "Ola");
            logger.debug() << "Changed " << changed << std::endl;

            //  z  grupami
            std::string variables = "x=10; y=20;";
            std::regex group_replace(R"((\w)=(\d+))");
            std::string changed_vars = std::regex_replace(
                variables, group_replace, "$1 -> $2"
            );
            logger.debug() << "Changed vars: " << changed_vars << std::endl;
            // sprawdzenie czy zawiera wiecej niż jedną litere
            std::regex multiple(R"(a{2,})");
            // conajmniej 2 litery a
        }

        void show_all_string_operation() {
            std::string one = "one";
            std::string two = one; // kopia, nowe dane w pamieci

            std::string_view msg;
            logger.debug() << "[INFO] " << msg << "\n";
            //  explanation class
            std::string text = " some funny tricky text\n";
            StringOperation str_operation(text);
            str_operation.access();
            str_operation.modification();
            str_operation.searching();
            // str_operation.triming_white_spaces();
            str_operation.regex_matching();
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
