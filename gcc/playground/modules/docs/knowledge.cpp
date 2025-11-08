// ------------------------
#include <docs/knowledge.hpp>
/*
    Creating Exceptions
*/
Logger log{std::clog, LogLevel::Debug, true};

namespace Knowledge {
    
    namespace StreamsManagement {
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
            log.info() << "\n-----------------------------\n";
            simple_tasks();
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
                log.info() << "Scores: " << scores << std::endl;
            }
            //--------------------
            void ProtectedSpec::show_shield() const {
                log.debug() << "Shield value: " << shield << std::endl;
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
                log.info() << "Default object created\n";
            }
            Constructor::Constructor(std::string name){
                _name = name;
                log.info() << "Object with " << name << " name created\n";
            }
            Constructor::Constructor(std::string name, int threshold)
                : _name(name), _threshold(threshold){
                log.info() << "Object inicialized with list (" << name << ", " << threshold <<  " params created\n";
            }
            // -----------------------
            Destructor::Destructor(){
                _notes_file_hook.open("notes.txt");
                if (!_notes_file_hook){
                    std::cerr << "Cannot open notes.txt file\n";
                    return;
                }
                else{
                    log.info() << "Hook to file notes.txt applicated\n";
                }
            }
            Destructor::Destructor(std::string path){
                _notes_file_hook.open(path);
                if (!_notes_file_hook){
                    std::cerr << "Cannot open " << path << "path\n";
                    return;
                }
                else{
                    log.info() << "Hook to file " << path << "applicated\n";
                }
            }
            Destructor::~Destructor(){
                if(_notes_file_hook.is_open()){
                    _notes_file_hook.close();
                    log.info() << "Hook closed properly\n";
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
                        log.error() << "Exception " << range_exception.what() << std::endl;
                    }
                }
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
            log.debug() << "Allowed scores " << allowed.scores << std::endl;
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
            log.info() << "Amount: " << gates.get_amount() << std::endl;
            log.info() << "Size of gates: " << gates.get_gates().size() << std::endl;
            gates.set_amount(15);
            std::vector<int> new_gates{15, 62, 73, 21};
            gates.set_gates(new_gates);
            log.info() << "Gates item: " << gates.get_gates().at(1) << std::endl;

        }
    }
    namespace StringKnow {
        StringOperation::StringOperation(std::string base)
            : base_text(base) {}
        
        void StringOperation::access(){
            // rozmiar
            log.info() << "size: "  << base_text.size() << std::endl;
            log.info() << "empty: " << base_text.empty() << std::endl;
            //  dostęp
            log.info() << "0: "     << base_text[0] << std::endl;
            log.info() << "front: " << base_text.front() << std::endl;
            log.info() << "back: "  << base_text.back() << std::endl;
            log.info() << "data: "  << base_text.data() << std::endl;
            log.info() << "c_str: " << base_text.c_str() << std::endl;
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
            log.info() << "After replacement: " << base_text << std::endl;
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
                log.info() << "Key: " << key << std::endl;
                log.info() << "Value: " << value << std::endl;
            }
            else {
                log.error() << "= not found in base \n";
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
            log.info() << "Whitespace from left found in position: " << left_position << std::endl;
            log.info() << "Whitespace from right found in position: " << right_position << std::endl;
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
            log.info() << "Left trimmed: " << left_trimmed_string << std::endl;
            log.info() << "Right trimmed: " << right_trimmed_string << std::endl;
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
            str_operation.triming_white_spaces();
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
            log.info() << "Without checking index:" 
                << numbers[0] << std::endl;
            log.info() << "With checking index:" 
                << numbers.at(0) << std::endl; // sprawdza czy jest zakres inaczej out_of_range
            log.info() << "First one" 
                << numbers.front() << std::endl;
            log.info() << "Last one" 
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
                log.debug() << "Index: " << index << " element " << doubles[index] << std::endl;
            }

            // range-for - read only 
            for (double dub: doubles) {
                log.error() << "Read only numbers: " << dub << std::endl;
            }
            // range for - z modyfikacją(poprzez referencje)
            for (double& dub: doubles) {
                dub *= 3;
                log.warn() << "Changed numbers: " << dub << std::endl;
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
                log.info() << "Iter: " << *it << std::endl;
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
            //  para
            std::pair<std::string, int> single_score = {"Bob", 561};
            std::cout << single_score.first << std::endl;
            std::cout << single_score.second << std::endl;

            return copy;
        }
        void MapExamples::access_to_elements(std::map<int, int> scores){
            scores[0] = 12; // utworzy jak nie ma
            scores[1] = 51; // nadpisze 

            log.info() << "By operator []:" 
                << scores[1] << std::endl;
            log.info() << "With checking index:" 
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
};
