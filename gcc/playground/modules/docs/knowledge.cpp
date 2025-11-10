// ------------------------
#include <docs/knowledge.hpp>
/*
    Creating Exceptions
*/

namespace Knowledge {
    
    namespace StreamsManagement {
        void StandardStream::input_stream_example(){
            // input - czyli dane wchodzą gdzieś

        }

        void print_list(std::ostream& os, const std::vector<int>& items){
            int index = 1;
            for (const auto& item: items){
                os << index++ << ") value: " << item << "\n";
            }
        }
        std::vector<std::string> read_lines(std::istream& is){
            std::vector<std::string> lines;
            std::string line;
            while(std::getline(is, line)){
                lines.push_back(line);
            }
            return lines;
        }
        void StandardStream::output_stream_example(){
            /*
                output - czyli dane wychodzą gdzieś
                - funkcja nie zna celu wyjśca wtedy mamy ostream jako parametr
            */
            std::vector<int> numbs{1, 15, 61, 211};
            std::ofstream out("numbers_list.txt");
            std::ostringstream mem;
            print_list(out, numbs);
            print_list(mem, numbs);
            logger.info() << "Memory buffor " << mem.str() << "\n";
            
            // istream
            std::ifstream in("numbers_list.txt");
            std::istringstream stream_mem("a\nb\nc\n");
            auto lines = read_lines(in);
            auto mem_lines=  read_lines(stream_mem);
        }
        void StandardStream::standard_stream() {
            std::cout << "Enter some number" << std::endl; //  pisanie do stdout - terminala 
            int number;
            // czyta z stdin - z klawiatury
            /* 
                Czyta z klawiatury 
                Czeka aż user wpisze, i przekonwertuje na dany typ
                Zła konwersaja to bląd i cin ustawia flage błędu na failbit
            */ 
            std::cin >> number; 
            if (!std::cin) {
                std::cin.clear(); // czyści buffor
                std::cin.ignore(); // wyrzucenie śmieci z buffora
                //  cerr - od razu wypisze bez buforowania
                std::cerr << " Provided number is not a integer" << std::endl;
                return;
            }
            else {
                // clog jest pod informacje diagnostyczne
                std::cout << "Provided number: [" << number << "]. \n" << std::endl; 
                std::clog << "[LOG-INFO] User provide number: " << number << std::endl;
            }
        }
        void show_streams(){
            StandardStream stream;
            stream.input_stream_example();
            stream.output_stream_example();
            // stream.standard_stream()
        }
        void FileStream::writing_overriting(){
            // tworzy nowy albo czyści
            // domyślne tryby std::ios::out | std::ios::trunc
            std::ofstream out("notes.txt");
            if(!out){
                std::cout << "Cannot open for override";
                return;
            }
            out << "[INFO] File stream in here!\n [NEXT] end\n<->";
            // out.close(); // after went out of func
        }

        void FileStream::appending(){
            // dopisuje std::ios::app - append
            std::ofstream append_out("notes.txt", std::ios::app);
            if(!append_out){
                std::cout << "Cannot open to append";
                return;
            }
            append_out << "\n[NEW] one and last";
        }
        void FileStream::reading_by_lines(){
            std::ifstream in("notes.txt");
            if (!in){
                std::cerr << "Cannot open notes.txt";
                return;
            }
            std::string line;
            int index = 0;
            /*
                pojedyncze pobranie to 
                std::string first_line;
                std::getline(in, first_line);
                // bierze z buffora pierwszą linie i wstawia w zmienną 
            */
            while (std::getline(in, line)){
                std::cout << "Line " << index++ << " content: " << line << ".\n"; 
            }
        }

        void MemoryStream::reading_from_string(){
            std::string text = "12 34 5 61\n";
            /*
                Tekst trafia do buffora
                    bo chcesz na nim potem robić jakieś rzeczy
                    jakbyś czytał plik 
            */
            std::istringstream in(text);
            int a,b ,c, d;
            in >> a >> b >> c >> d;

            std::cout << "a=" << a << ", b=" << b << ", c=" << c << ", d=" << d << '\n';
        }

        void MemoryStream::writng_building_string(){
            std::ostringstream out;
            out << "Result: " << 27 << std::endl;
            std::string text = out.str(); // pobiera z buffora
            std::cout << "Content after loading from buffor " << text << std::endl;
        } 

        void MemoryStream::both_string_operation(){
            std::stringstream sstream;
            sstream << "123 451";
            int first, second;
            sstream >> first >> second;
            std::cout << (first + second) << '\n';
        }
        
        void simple_tasks(){
            // otwórz app.log w trybie append 
            //  dopisz linie z aktualnym czasem i started\n;
            std::ofstream out_data("app.txt");
            if(!out_data){
                std::cout << "Cannot open app.log";
                return;
            }
            else{
                std::cout << "Writing to it";
                time_t current_date = time(0);
                char* datetime = ctime(&current_date);
                out_data << "[" << datetime << "]: Started \n";
            }
        }

        void show_file_stream(){
            StandardStream sstream_obj;
            // sstream_obj.standard_stream();
            FileStream fstream_obj;
            fstream_obj.writing_overriting();
            fstream_obj.appending();
            fstream_obj.reading_by_lines();
            MemoryStream mstream;
            mstream.reading_from_string();
            mstream.writng_building_string();
            mstream.both_string_operation();
            logger.info() << "\n-----------------------------\n";
            simple_tasks();
        }

        fs::path FileSystemManagment::create_paths(){
            // tworzenie ścieżek
            fs::path user_path = "/home/user";
            // operator / - składa ścieżki
            fs::path scores_path = user_path / "home" / "scores.txt";
            return scores_path;
        }
        void FileSystemManagment::get_slices(fs::path score_path){
            /* wyciaganie kawałków ze ścieżki*/
            logger.debug() 
                << "Filename: "   << score_path.filename()    << std::endl
                << "Identifier: " << score_path.stem()        << std::endl
                << "Extension: "  << score_path.extension()   << std::endl
                << "Parent : "    << score_path.parent_path() << std::endl;
            // normalizacja i konwersje
            // abosultna ścieżka, bez sprawdzania czy istnieje
            fs::path absolute = fs::absolute(score_path);
            fs::path with_symlinc = fs::canonical(score_path);
            absolute.string();           // std::string (na UI/logi)
            // bierzące katalogi, gdzie jesteśmy
            // fs::current_path();
            // fs::temp_directory_path(); // /tmp dir
        }

        void FileSystemManagment::file_states(fs::path file_path){
            bool path_exists = fs::exists(file_path); // czy istnieje 
            bool is_regular = fs::is_regular_file(file_path); // zwykły plik
            // fs::is_directory(file_path);
            // fs::file_size(file_path);
            auto path_time = fs::last_write_time(file_path);
            // czy wskazują na ten sam obiekt
            // fs::equivalent(file_path, fs::path("other.txt")); 
        }
        
        void FileSystemManagment::modification(fs::path file_path){
            // tworzenie katalogów
            fs::create_directory(file_path);
            fs::create_directories(file_path);
            // usuwanie pliku / pustego katalogu
            fs::remove(file_path);
            fs::remove_all(file_path); // rm -rf rekurencyjne
            // zmian nazwy
            fs::rename(file_path, fs::path("other.txt"));
            // kopiowanie
            fs::copy( // src, dst, option 
                file_path, fs::path("other/files"),
                fs::copy_options::overwrite_existing 
            ); // sa też inne opcje 
            // iteracja
            for (const auto& file: fs::directory_iterator(file_path)){
                const fs::path& path = file.path();
            }
            // rekurencyjnie
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
        void show_file_system_managment(){
            FileSystemManagment managment;
            // managment.get_file_from_resources();
            fs::path score_path = managment.create_paths();
            managment.get_slices(score_path);
            managment.file_states(score_path);
        }
    }
    namespace AliasesAndTypes {
        // std::variant
        void resolve_variant_types(){
            std::variant<std::string, int> possibilites;
            if (std::holds_alternative<int>(possibilites)){
                logger.info() 
                    << "Variant holds int type" 
                    << std::get<int>(possibilites) << std::endl;
            }
            else {
                logger.info() 
                    << "Variant holds string type" 
                    << std::get<std::string>(possibilites) << std::endl;
            }
        }
        void casting_example(){
            VariableCasting casting;
            casting.static_casting();
            int x = 10;
            const int* some_var = &x;
            casting.const_casting(some_var);
            std::cout << "After casting" << x << "\n";
            casting.reinterpret_casting();
            casting.dynamic_casting();
        }
        // Pointers
        void Pointers::simple_poiners(){
            /*
                numb = wartosc 
                ptr - adres pamieci
                *ptr - dereferencja- idz pod adres i wex wartosc
            */
            int numb = 412;
            int* numb_ptr = &numb; // &adres
            std::cout << "Numb " << numb << std::endl;
            std::cout << "Numb address " << numb_ptr << std::endl;
            *numb_ptr = 100;
            std::cout << "Dreference after chage: " << *numb_ptr << std::endl;
        }

        /*
            -> to to samo co (*pointer).metoda()
        */
        void Pointers::pointers_to_structures(){
            Person woman(21);
            Person* struct_ptr = &woman; //adres obiektu
            struct_ptr->introduce();

        }
        
        void Pointers::dynamic_memory(){
            int* ptr = new int(10); // tworzy int w pamieci
            std::cout << *ptr << std::endl;
            delete ptr;
        }

        /*
            std::unique_ptr
                wyłączna własność obiektu
                tylko on może przechowywać adres obiektu

            syntax:
                std::unique_ptr<typ> nazwa =
                    std::make_unique<Typ>(obiekt)
            {
                
            } Po wyjściu ze scopa automatycznie jest wywoływany destruktor
            
            Nie można kopiować do danego obiektu miedzy pointerami
            Zdefiniowany obiekt należy już tylko do tego pointera
            Ale można przekazać wartość poprzez
                std::move(pointer);
        */
        void Pointers::unique_pointer(){
            std::unique_ptr<Person> marek = 
                std::make_unique<Person>(51);
            std:: cout << "Person " << marek->_age << " is doing something\n";
            // auto f2 = marek; compilation fail
            auto f2 = std::move(marek);
        }
        
        /*
            shared_ptr<>  make_shared<>(obiekt);
                wiele pointerów może korzystać z obiektu
        */
        void Pointers::shared_pointer(){
            std::shared_ptr<Connection> sql_db, mongo_db;
            sql_db = std::make_shared<Connection>();
            sql_db->name = "SQL db";
            sql_db->accounts = 1;
            
            mongo_db = sql_db; // współdzielenie jednego obiektu
            mongo_db->accounts = 2;
            std::cout << "Mongo db: " << mongo_db->name << "\n";
            std::cout << "SQL amount: " << sql_db->accounts << "\n";
            std::cout << "Using the connection\n";
        }
        /*
            weak_ptr
                służy do współpracy z shared_ptr
                obserwator który nie zwieksza licznika
            TODO: later
        */
        void Pointers::weak_pointer(){} 

        void pointer_example(){
            Pointers points;
            points.simple_poiners();
            points.pointers_to_structures();
            points.dynamic_memory();
            points.unique_pointer();
            points.shared_pointer();
            // points.weak_pointer();
        }
        void check_optional(){
            // optional
            // albo wartosc typu albo nullopt 
            std::optional<int> maybe = 42;
            std::optional<int> other = std::nullopt; 
            if (maybe.has_value()){
                std::cout << "Value " << maybe.value() << std::endl;
                std::cout << "Value v2" << *maybe << std::endl;
            }
            int number = maybe.value_or(-1);
            std::cout << "Number : " << number;

        }

        // Enumy
        // mapowanie enuma
        std::string Enums::method_to_string(Enums::RequestMethod method) {
            switch (method) {
                case Enums::RequestMethod::GET:      return "GET";
                case Enums::RequestMethod::POST:     return "POST";
                case Enums::RequestMethod::DELETE:   return "DELETE";
                default:                             return "UNKNOWN";
            }
        }

        std::optional<Enums::RequestMethod> Enums::string_to_method(const std::string& method_str) {
            if (method_str == "GET")    return  Enums::RequestMethod::GET;
            if (method_str == "POST")   return  Enums::RequestMethod::POST; 
            if (method_str == "DELETE") return  Enums::RequestMethod::DELETE;
            return std::nullopt;
        }
        void enums_example(){
            /*
                jak jest sam enum
                    to wszystkie wartości które są zdefinowane
                    są wrzucone prosto do globalnej przestrzeni nazw
                        jaky na luzie, a mogą byc potem konflikty
                    i wtedy można sie odwołać czysto do WARNING
                    a nie trzeba do Status::WARNING
                        co jest niebezpieczne imo
            */
            Enums::Status well = Enums::WARNING;
            if (well == Enums::ERROR){
                std::cout << "There occurs an error\n";
            }
            else{
                std::cout << "Value: " << well << " and its ok\n";
            }
            // Enums::Status err = (Enums::Status)100;  są konflikty z innymi
            Enums::RequestMethod method = Enums::RequestMethod::GET;
            // Wymagane jest rzutowanie na inta
            int code = static_cast<int>(method);
            std::cout << "Request method code: " << code << std::endl;
            Enums::Color color = Enums::Color::GREEN;
            std::cout << "Hex color: "
                << std::hex << static_cast<uint8_t>(color) 
                << std::endl;

            // iterowanie po enumie ( hack na fora)
            constexpr std::array<Enums::RequestMethod, 3> all_requests = {
                Enums::RequestMethod::GET,
                Enums::RequestMethod::DELETE,
                Enums::RequestMethod::POST
            };
            for (auto request: all_requests){
                std::cout << "Request: " << static_cast<int>(request) << std::endl;
            }
            // mapowanie 
            std::string method_str = Enums::method_to_string(method);
            std::cout << "Converted method: " << method_str << "\n";
            // alais do skrótów
            using REQUEST_METHOD = Enums::RequestMethod;
            REQUEST_METHOD get_method = REQUEST_METHOD::GET;
            auto mapped_from_string = Enums::string_to_method(method_str);
            if (mapped_from_string != std::nullopt){
                REQUEST_METHOD mapped_value = mapped_from_string.value();
                std::cout << "Method: " << static_cast<int>(mapped_value) << std::endl;
            }
            
        }   
    }
    namespace NameSpacesKnow {
        namespace Begin{
            void print(){
                std::cout << "Namespace Begin \n";
            }
        }
        namespace End{
            void print(){
                std::cout << "Namespace End \n";
            }
        }
        void Out::Inner::read(){
            std::cout << "Reading in Inner\n";
        }
        void Out::Inner::write(){
            std::cout << "Writing in Inner\n";
        }
        struct API::Vector_v1{
            float x;
            float y;
        };
        void API::append_list(Vector_v1 vector){
            std::cout << "Appending to list from inline\n";
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
            std::cout << "Appending to list from api v2\n";
        }
    }
    namespace Preprocesor {
        double circle_area(double radius){
            return PI * radius * radius; 
        }

        void all(){
            double area = circle_area(5);
            std::cout << "Area: " << area << std::endl;
            // usage of SQUARE macro
            std::cout << SQUARE(4) << std::endl;
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
                std::cout << "Comparing: [" << velocity - diff.velocity << "]\n";  
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
                std::cout << "Hook deleted\n";
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
                std::cout << name 
                    << " (" << age << " lat) - " 
                    << salary << " PLN\n";
            }
            Employee::Employee(std::string name, int age, double salary)
                : name(std::move(name)), age(age), salary(salary)
            {
                std::cout << "Employee " << name << "created successfully\n";
            }
            void Stats::show_stats() const {
                std::cout << "HP: " << hp
                      << " | ATK: " << attack
                      << " | DEF: " << defense << '\n';
            }
            void Player::introduce() const {
                std::cout << "Player: " << name << " (lvl " << level << ")\n";
                stats.show_stats();
            }
            void show_player(const Player& player){
                std::cout << "=== PLAYER ===" << std::endl;
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
                std::cout << "Animal created\n";
            }
            Dog::Dog()
                : Animal(4) // default value for base construct
            {
                _name = "Burek";
                std::cout << "Default dog created\n";
            }
            Dog::Dog(std::string name)
                : Animal(4), _name(std::move(name))  // default value for base construct
            {
                std::cout << "Regular dog created\n";
            }
            Dog::Dog(int legs, std::string name)
                : Animal(legs), _name(std::move(name))
            {
                std::cout << "Dog with amount of legs\n";
            }
            int Animal::count_legs() {
                return _legs;
            }
            void Dog::introduce(){
                std::cout << "Dog " << _name 
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
                std::cout << "Other found in text\n";
            }

            // sprawdzanie całego stringa
            std::regex specific_pattern("^some [=]{2}.*");
            if (std::regex_match(text, specific_pattern)){
                std::cout << "Specific found\n";
            }
            // wyciąganie dopasowań
            // match[x] → grupy z nawiasów ()
            std::string data = "user: admin, id: 42";
            std::regex matching_pattern(R"(user:\s*(\w+),\s*id:\s*(\d+))");
            std::smatch match;
            if (std::regex_search(data, match, matching_pattern)) {
                std::cout << "Whole: " << match[0] << std::endl;
                std::cout << "User: " << match[1] << std::endl;
                std::cout << "Id: " << match[2] << std::endl;
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
                 std::cout << "Name: " << (*it)[1] << ", score: " << (*it)[2] << '\n';
            }
            // zamiana regex_replace
            std::regex r_numbs("Ala");
            std::string changed = std::regex_replace(other, r_numbs, "Ola");
            std::cout << "Changed " << changed << std::endl;

            //  z  grupami
            std::string variables = "x=10; y=20;";
            std::regex group_replace(R"((\w)=(\d+))");
            std::string changed_vars = std::regex_replace(
                variables, group_replace, "$1 -> $2"
            );
            std::cout << "Changed vars: " << changed_vars << std::endl;
            // sprawdzenie czy zawiera wiecej niż jedną litere
            std::regex multiple(R"(a{2,})");
            // conajmniej 2 litery a
        }

        void show_all_string_operation() {
            std::string one = "one";
            std::string two = one; // kopia, nowe dane w pamieci

            std::string_view msg;
            std::cout << "[INFO] " << msg << "\n";
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

            std::cout << copy.size() << " " << copy.capacity() << "\n";
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
            std::cout << "Copy size: " << copy.size() << std::endl;
            
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
            std::cout << single_score.first << std::endl;
            std::cout << single_score.second << std::endl;
            
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
                std::cout << "1 not exists\n";
            }
            // 20 contains
            // if (scores.contains(1)){
                // std::cout << "1 exists\n";
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
                std::cout << pair.first << " => " << pair.second << std::endl;
            }

            // (C++17)
            for (auto &[name, score] : scores) {
                std::cout << name << " ma wynik " << score << std::endl;
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
            []() { std::cout << "In the lambda\n"; }(); 
            // z zaczepieniem o zmienną
            auto hook = []() {
                std::cout << "With hook\n";
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
            std::cout << "Square: " << radius * radius << std::endl;
        }

        void LambdaFunction::show_function_examples(){
            repeat(5, print_square);
            repeat(5,
                [](int i) {
                    std::cout << "With lambda\n";
                }
            );
            // jeden parametr
            std::function<void(int)> single_param_call;
            single_param_call = [] (int single) {
                std::cout << "Number: " << single << std::endl;
            };
            // double
            std::function<void(int, std::string)> double_param_call;
            // returned type
            std::function<int(double, int)> with_return_type;
            // without any 
            std::function<void()> no_param;
        }

        void show_all_functions(){
            LambdaFunction lambda;
            lambda.syntax();
            lambda.show_function_examples();
        }
    }

};
