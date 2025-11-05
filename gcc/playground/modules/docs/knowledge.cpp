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
    namespace StringOperations {
        void string_example() {
            std::string one = "one";
            std::string two = one; // kopia, nowe dane w pamieci

            std::string_view msg;
            std::cout << "[INFO] " << msg << "\n";
        }
    }
};




