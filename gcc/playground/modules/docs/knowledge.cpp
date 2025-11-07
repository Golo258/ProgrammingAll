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

        void PrivateSpecificator::start(){
            velocity = 50; // this.velocity
        }
        
        void PrivateSpec::compare(const PrivateSpec& diff){
            std::cout << "Comparing: [" << velocity - diff.velocity << "]\n";  
            velocity = diff.velocity;
        }
        
        void PublicSpec::set_and_show(){
            scores = 51.2;
            log.info() << "Scores: " << scores << std::endl;
        }
        void demonstrate_classes(){
            PrivateSpec first, second;
            first.start();
            /*
                Błąd kompilacji, nie można dostać się do prywatnego atrybutu
                second.velocity = 12;  
            */
            first.compare(second);
            first.compare(second); // after change 
            PublicSpec 
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
        }

        void StringOperation::modification(std::string text){

        }
        void show_all_string_operation() {
            std::string one = "one";
            std::string two = one; // kopia, nowe dane w pamieci

            std::string_view msg;
            std::cout << "[INFO] " << msg << "\n";
            //  explanation class
            std::string text = " some funny tricky text";
            StringOperation str_operation(text);
            str_operation.access();
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
            if (scores.contains(1)){
                std::cout << "1 exists\n";
            }
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




