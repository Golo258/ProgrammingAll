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
        //  czytanie 


        void show_file_stream(){
            StandardStream sstream_obj;
            // sstream_obj.standard_stream();
            FileStream fstream_obj;
            fstream_obj.writing_overriting();
            fstream_obj.appending();
        }
    }
};

