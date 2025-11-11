
// docs/knowledge.hpp
// ------------------------

#pragma once
#include <iostream>
#include <string>
#include <fstream> // strumienie plikowe
#include <sstream> // strumienie w pamieci 
#include <ctime> // zarządzanie czasem
#include <vector>
#include <map>
#include <array>
#include <algorithm>
#include <numeric> // accumulate 
#include <cctype> // to lower | upper
#include <utils/variables.hpp>
#include <variant> // union variant
#include <regex>
#include <exception> // exception
#include <chrono> // czas systemowy
#include <iomanip> // formatowanie czasu
#include <filesystem> // zarządzanie plikami
#include <memory> // smart pointers
#include <optional>

// ------------------------
/*
    TODO co do przerobienia:
        - json, parsowanie, tworzenie, tak samo yaml i inne typy 
        - testowanie kodu, tworzenie testów
        - może modyfikacja loggera żeby zapisywał do pliku i żeby terminal nie spamił
        - includowanie zewnętrznych bibliotek, ale to pewnie przy jsonie
        - przeciążanie operatorów, mniej wiecej jak to działa
        - wątki i programowanie wielowątkowe 
        - tworzenie baz danych
            łączenie sie, tworzenie query, itp
        - tworzenie requestów do api, i parsowanie tego
            - tworzenie własnego API, ale to nie wiem czy nie lepiej w pythonie


*/
namespace Knowledge {

    namespace StreamsManagement {
        /*
        Strumień
            - kanał przepłwu danych , obiekt zarządzający tym przepływem
            - dane przepływają wchodzą i wychodzą do miejsc takich jak
            - tekst, pliki, sieć, pamięć -- wszystko leci przez strumienie
            - dane mogą płynąć na zewnątrz (out) programu
                - std::ostream 
            - dane mogą płynąć do programu (in)
                - std::istream
            Kierunki:
                wejście - in, istream   cin, ifstream, istringstream
                wyjście - out, ostream, cout, ofstream, ostringstream
                oba - wejscie i wyjscie
                    iostream, input output stream
                        fstream, stringstream
            Hierarchia: 
                    std::ios -- wspólna baza trzymająca stan
                        │
                ┌───────┴────────┐
            std::istream     std::ostream
                │                 │
            std::ifstream       std::ofstream
            std::istringstream  std::ostringstream
                └────────────┬────────────┘
                        std::iostream
                            │
                        std::fstream
                        std::stringstream
        */

        /*
           Strumienie standardowe
            cin  - wejscie  - czyta z klawiatury
            cout - wyjscie  - pisze na standardowe wyjscie - terminal
            cerr - wyjscie  - pisze błędy bez buforowania
            clog - wyjscie  - pisze logi z buforowaniem
            #Każdy z nich jest obiektem klasy 
                - std::istream - wejscie
                - std::ostream - wyjscie
                - iostreram łaczy oba - plikowy może być jednym i drugim
            
            Każdy ze strumieni ma operator bool()
                w momencie gdy do strumienia wpadła zła wartość
                i wykryto błąd to coś możemy zrobić 
                if (!std::cin)
            
            W linuxie:
                ./program > output.txt 2> errors.txt
                > output.txt - wyłapie cout i clog
                2> - wyłaie cerr
        */
        class StandardStream {
            public:
                void input_stream_example();
                void output_stream_example();
                void standard_stream();
        };
        /*
            Strumienie plikowe <fstream>
                ifstream  - wejscie - czytanie z pliku
                ofstream  - wyjscie - pisanie do pliku
                fstream   -  oba    - czytanie i pisanie

            Tryby otwierania:
                std::ios::
                    in - czytanie 
                    out - pisanie
                    app - dodawanie append - na koniec
                    trunc - czyszczenie pliku przy otwarciu
                    ate - at end - utwainie na koncu
                    binary - tryb binarny 
                Można miksować poprzez | 
                    np std::ios::out | std::out::trunc
        */
        class FileStream {
            public:
                void writing_overriting();
                void appending();
                void reading_by_lines();
        };

        /*
            Strumienie w pamięci <sstream>
                służa do pcy z tekstem w pamieci
                    bufor tekstu z wieloma liniami
                    istringstream
                    ostringstream
        
            Buffor - po co jak i gdzie i co to jest 
                Bufor to tymczasowa pamieć (RAM)
                    w której gromadzimy dane zanim 
                    zostaną odczytane albo zapisane
                To magazyn pośredni miedzy 
                    kodem a źródłem docelowym- plikiem, klawiaturyą
            Tymczasowe miejsce, gdzie trzymamy dane
                zanim coś z nimi zrobisz
            std::cin - bufor wejsciowy 
                system trzyma znaki które wpisuje zanim pogram je pobierze
            std::cout - bufor wyjściowy
                tekst trafia do buffora, a dopiero potem do terminala

        */
        class MemoryStream {
            public:
                void reading_from_string();
                void writng_building_string();
                void both_string_operation();
        };
        
        /*
            filesystem:
                standardowe funkcje do pracy
                    z plikami / scieżkami / katalogami
                najcześciej sie używa aliasu do namespaca
                namespace fs = std::filesystem

            Ścieżki:
                fs::path
        */
        namespace fs = std::filesystem;
        class FileSystemManagment {
            public:
                fs::path create_paths();
                void get_slices(fs::path score_path);
                void file_states(fs::path file_path);
                void modification(fs::path file_path);
                void get_file_from_resources();
        };
        
        // utils functions
        void print_list();
        std::vector<std::string> read_lines(std::istream& is);
        // -------------------
        void show_streams();
        void simple_tasks();
        void show_file_stream();
        void show_file_system_managment();
        // | Temat                                                       | Po co                                                 
        // | ----------------------------------------------------------- | ------------------------------------------------------
        // | `std::cin.ignore()` i `clear()`                             | obsługa błędów i czyszczenie bufora                   
        // | `std::getline()`                                            | czyta całą linię, łącznie ze spacjami                 
        // | `std::ios::binary`                                          | praca z plikami binarnymi (np. structy)               
        // | manipulatory (`std::setw`, `std::setprecision`, `std::hex`) | ładne formatowanie liczb                              
        // | `std::tie(std::cin, nullptr)`                               | odłącza `cout` od `cin`, żeby przyspieszyć I/O        
        // | `rdbuf()`                                                   | przekierowywanie strumieni (np. `clog` → `cout`)      
        // | wyjątki na streamach (`exceptions()`)                       | wykrywanie błędów przez `throw`, nie przez `if (!cin)`

    }
    namespace AliasesAndTypes {
        // stosuejmy pascal case - czyli duża litera i potem małe

            /* aliasy podstawowe*/
        // stary sposób (C- style)
        typedef unsigned int Uint32;
        
        // nowoczesny sposób (c++1++)
        using ULL = unsigned long long;

        // aliasowanie funkcji
        using Callback = void(*)(int); // wskaźnik do funkcji 
            //  to podpytać -- narazie nie 

            /*aliasy szablonowe*/
        
        // skrót dla vectora dowolnego typu
        template<typename T>
        using TypeVec = std::vector<T>;

        //  skrót lda mapy string : dowolny typ
        template<typename T>
        using StringMap = std::map<std::string, T>;

            /*Silne typy */
        // unikalny typ
        using UserIdAlias = int; 
        
        // nowy typ, niezmienialny
        struct UserId {
            int value;
            explicit UserId(int value) : value(value){}
        };

        /*
            variant, pozwala dać możliwośc wyboru typu
                 ten typ albo ten typ
                 
            std::variant<std::string, intQ possibilities;
        */
        void resolve_variant_types();
        /*
           klasyczny union
            pudełko na kilka typów
            union Nazwa { int a, double b...};
        */
        union PossibleTypes {
            int i;
            double d;
            char c;
        };
        struct TaggedValue {
            PossibleTypes value;
        };

        /*
            Castowanie - rzutowanie
                świadoma zamiana jakiegos typu 
            Kompilator albo automatycznie rzutuje zmienną   
                albo chce żebyśmy świadomie rzutowali
            4 typy castów
                static_cast
                const_cast
                reinterpret_cast
                dynamic_cast
                (typ) -> stary styl z C 
        */
       //Implicit conversion - automatyczne rzutowanie
        class VariableCasting {
        public:
            double pi_double = 3.14562;
            
            inline void implicit_conversion(){
                int converted_pi = pi_double;
                std::cout<< "Converted "<<  converted_pi << "\n";
            }
             /*
                static_cast 
                    normalne, bezpieczne castowanie typów pokrewnych
                        int na double
                        char na int itp.
                        wskaźnika na typ bazowy w klasach
                    Syntax:
                        static_cast<na_jaki_typ>(jaką zmienną)
            */
            inline void static_casting(){
                double var = 3.1561261;
                int static_var = static_cast<int>(var); 
                std::cout<< "Converted "<<  static_var << "\n";
            }
             /*
            const_cast
                usuwanie lub dodawanie const
                używane tylko do manipulowania const
                np: gdy masz funckje const ale potrzebuje tam cos zmienic
            */
            inline void const_casting(const int* value){
                int* pointer = const_cast<int*>(value);
                *pointer = 99; // nie polecane, ale możliwe
                std::cout << *pointer << "\n";
            }
             /*
                reinterpret_cast 
                    nie zmienia danych, tylko zmienia
                    sposób ich ich interpetacji w pamieci
                    Używany do niskopoziomowgo kodu
                    sieciowych, bibliotek systemowych
                Mało używany
            */
            inline void reinterpret_casting(){
                int value = 65;
                char* ptr = reinterpret_cast<char*>(&value);
                std::cout << *ptr << "\n";
            }
            /*
                dynamic_cast
                    rzutowanie obiektów miedzy klasami w OOP
                    Przy dziedziczeniu i polimorfizmie
            */
            struct Base {
                virtual ~Base() = default;
            };
            struct Derived : Base {
                inline void say(){
                    std::cout << "Something\n";
                }
            };
            // TODO: powrót po nauce dziedziczenia itp
            inline void dynamic_casting(){
                Base* base = new Derived;
                Derived* derived = dynamic_cast<Derived*>(base);
                if (derived) {
                    derived->say();
                }
            }
        };
        void casting_example();
        struct Person {
            int _age;
            Person(int age) : _age(age) {}
            ~Person() { std::cout << "End of story\n"; }
            void introduce(){
                std::cout << "age: " << _age << std::endl;
            }
        };
        
        struct Connection {
            std::string name;
            int accounts;     
            Connection() { std::cout << "Openning connection \n"; }
            ~Connection() { std::cout << "Closing connection \n"; }
        };

        class Pointers {
            /*
                wskąźnik, czyli
                    zmienna która przechowuje adres obiektu /zmiennej
            */
            public:
                void simple_poiners();
                void pointers_to_structures();
                /*
                    Dynamiczne tworzenie obiektów
                        należy samemu zarządzać pamiecią 
                        i ją potem zwalniać poprzez delete
                */
                void dynamic_memory();
                /*
                    Smart pointers - bezpieczne wskaźniki
                        z klasy memory
                        automatycznie zarządzają pamiecią
                */
                void unique_pointer();
                void shared_pointer();
                void weak_pointer();

        };
        void pointer_example();
        void check_optional();
        namespace Enums {
            /*
                Enum - typ wyliczeniowy
                    nadaje nazwane stałe wartościom liczbowym
                    Zamiast pisać dane liczby 
                        to mają one określony sens
                Każdy element to domyslnie int 
                    zaczynający się od 0
                
                Można przypisać konkretne wartości do typów
                    enum Nazwa {
                        typ = wartosc;
                    }
            */
            enum Status {
                OK,       // 0
                WARNING,  // 1 
                ERROR,    // 2
                CRITICAL  // 3
            };
            enum HttpCode {
                OK_FOUND  = 200,
                NOT_FOUND = 404,
                INTERNAL  = 500
            };
            /*
                nowoczesny enum class - silnie typowany
                    nie miesza sie z int
                    nie wchodzi w globalny namespace
                    wymaga jawnego rzutowania 
                Aby dostać sie do wartość 
                    wymagane jest rzutowanie na inta
                można obrać jaki jest typ bazowy 
                    rozmiar / zarkes 
            */
            enum class RequestMethod {
                GET,
                POST,
                DELETE
            };
            //  można przypisać hexa
            enum class Color : uint8_t {
                RED   = 0xFF,
                GREEN = 0x80,
                BLUE  = 0x40,
                BLACK = 0x00
            };
            std::string method_to_string(Enums::RequestMethod method);
            std::optional<Enums::RequestMethod> string_to_method(const std::string& method_str);
            
        }
        void enums_example();
    }
    namespace NameSpacesKnow {
        /*
        Namespacy wytłumaczenie
            Sposób na grupowanie nazw
                (funkcji, klas, zmienych) w logiczne bloki,
                aby uniknąć konfliktu nazw w projetach
                Dostęp poprzez using nazwa_namespacu
                print() -> funkcja z danego namespacu
        
            Aby dostać sie potem do funkcji z tego namespacu używamy:
                nazwa_namespacu::funkcja()
            Można stworzyć alias do przestrzeni nazw
                namespace IO = App::IO; IO::read();
            Można tworzyć anonimowe przestrzenie nazw
                namespace { funckja() { deklaracja }}
            taka przestrzeń jest static i widoczna tylko w danym .cpp
        */
        namespace Begin {
            void print();
        }
        namespace End {
            void print();
        }
        /*
            Można tworzyć zagnieżdzone namespacy
                od C++17 można wewnętrzne deklarować jako
                namespace Out::In {}
        */
        namespace Out {
            namespace Inner {
                void read();
                void write();
            }
        }
        namespace App::IO { // C++17
            void read();
            void write();
        }
        
        /*
            Można tworzyć inline namespace
                umożliwia wersjonowanie np API
            API::append_list() # domyślnie V1
            API::v2::append_list() # jawnie v2
            inline daje coś takiego że jest widoczne
                jakby v1 było bezpośednio w API
                wtedy traktujemy na przykłąd tą wersje v1
                    jakby była domyslna/aktualna wersja
                a inne już musimy wymusić
            Nie może być przez to dwóch inner inline namespaców
            Można w namespacach trzymać takzę klasy i struktury
                Gdy przekazujemy w danym namespacie do funkcji
                    inną strukture danych to ona przy definicji automatycznie
                wie że to jest ten własnie tych i nie trzeba tego precyzować
        */
        namespace API {
            inline namespace v1 {
                struct Vector_v1;
                void append_list(Vector_v1 vector);
            }
            namespace v2 {
                class Vector_v2;
                void append_list(Vector_v2 vector);
            }
        }

    }    
    namespace Preprocesor {
        /*
            Preproces 
                to etap który działa zanim kod C++ trafi do kompilatora
                czyta plik źródłowy i dokonuje zamian tekstowych
            Zanim skompiluje kod, preprocesor:
                rozwija #include 
                podstawia #define 
                #usuwa fragmenty zależne od #ifdef #ifndef
                przetwarz #pragma itd
                g++ -E main.cpp -- jak to działa
        */
        // makra symboliczne 
        #define PI 3.141624
        double circle_area(double radius);
        void all();
        /*
            Makra funkcyjne
                czyli funkcje bez typów i kompilacji
        */
        #define SQUARE(x) ( (x) * (x))
        // w nowoczesnym pisze sie 
        template <typename MathType>
        constexpr MathType square(MathType var){
            return var * var;
        }

        /* 
            Makra warunkowe
                pozwalają kompilować rózne kawałki kodu
                w zależności od warunków
            #ifdef x // jesli x jest zdefinowane
            #ifndef x // jesli x nie jest zdefinowane
            #endif  -konie cwarunku
            #undef x - usuń definicje

            include guard
                #pragma once - zabezpieczenie przez wielokrotnym includowanie
                zamiast 
                    #ifndef LOGGER_HPP
                        #define LOGGER_HPP
                        
                    ... kod
                    #endif
        */
        #define DEBUG_MODE 
        #ifdef DEBUG_MODE // jesli jest zdefinowane
            #define LOG(x) std::cout << "[DEBUG]" << x << "\n"
        #else
            #define LOG(x)
        #endif
        
        /*
            Parametry przekazywane z kompilatora:
                kompilacja z parametrem
                -D
                np: g++ -Dversion=3 main.cpp 
            to tak jakby kompilator dodał na początku pliku
                #define version 3
            w kodzie potem można używać
                #idef VERSION
                    #if VERSION == 3
                        std::cout << "Wersja 3!\n";
                    #elif VERSION == 2
                        std::cout << "Wersja 2!\n";
                    #else
                        std::cout << "Nieznana wersja\n";
                    #endif
                #endif
            Inne:
                #error	ręczne przerwanie kompilacji
                #warning	ostrzeżenie podczas kompilacji
        */

    }
    namespace ClassKnow {
        /*
            Klasy:
                - domyslnie mają wszystkie pola prywatne
                - w struct publiczne
        */
        namespace Specificators {
        /*
            Specyfikatory dostępu:
                - mówią, kto  może dotykać rzeczy w środku klasy
                    --> jej zmiennych i metod
            Jak drzwi do domu:
                - otwarte dla wszystkich - public
                - tylko dla domowników   - protected
                - zamkniete na klucz     - private
        */
            /*---------- PRIVATE - tajemnica klasy --------
                    dostep mają tylko metody tej klasy
                    z zewnątrz nikt nie może tego dotknąć
                    - metody mogą czytać/zapisywaćpola innych
                        obiektów tej samej klasy
            */
            class PrivateSpec {
                private:
                    int velocity = 0; // with default 
                public:
                    void start();
                    void compare(const PrivateSpec& diff);
            };

            /*------------ PUBLIC ------------
                Każdy kto ma obiekt może wywołać odczytać 
                Widoczne dla użytkownika rzeczy
            */
            class PublicSpec {
                public:
                    double scores;
                    void set_and_show();
            };
            
            /* ---------- PROTECTED --------------
                Opócz metod, też klasy pochodne (dziedziczące)
                    mają dostęp do pól i metod
                Ale z zewnątrz obiekt nie ma (jak w private)

            */
            class ProtectedSpec {
                protected:
                    int shield = 100;
                public:
                    void show_shield() const;
            };

            class ProtectedChild : public ProtectedSpec {
                public:
                    void damage();
            };
        }
        namespace LifeCycle {
            /* ----- KONSTRUKTOR -----
                Metoda tworząca i inicjalizująca obiket
                    NazwaKlasy obiekt; -- wołany przy tworzeniu obiektu
                Dostęp konstruktora musi być publiczny 
            */
            class Constructor {
                private:
                    std::string _name;
                    int _threshold = 12;
                public:
                    Constructor(); // default
                    Constructor(std::string name); // with parameter
                    Constructor(std::string name, int threshold); // lista inicjalizacyjna
            };

            /* ----- DESTRUKTOR -----
                Metoda czyszcząca obiekt gdy kończy sie scope
                    i obiekt jest usuwany
                { } - wołany jest przy końcu bloku 
            */
            class Destructor {
                private: 
                    std::ofstream _notes_file_hook; // // dopisuje
                public:
                    Destructor();
                    // można dla zabawy dodać param z trybem otwarcia
                    Destructor(std::string path);
                    ~Destructor(); 
            };
        }
        namespace Utility {
            /* ------- GETTERS | SETTERS -----------   
                Kiedy pola są prywatne
                    gdy z zewnątrz nie można ich ruszyć
                    są jak bramki dostępu do wnętrza klasy 
                Umożliwiają one 
                    odczyt wartość - getter
                    nadanie i kontrole wartości - setter
            */
            class AccessGates {
                private:
                    int _amount;
                    std::vector<int> _gates;
                public:
                    AccessGates() = default;
                    AccessGates(int amount, int item);

                    int get_amount() const;
                    std::vector<int> get_gates() const;

                    void set_amount(int new_amount);
                    void set_gates(std::vector<int>& new_gates);
        
            };

        }
        namespace Structures {
            /*
                Struct - własny typ danych
                    grupuje kilka powiązanych wartości
                    dostęp wszystko jest public
                zamiast 
                    std::string name;
                    int age;
                    double salary;
            */
        
            // można zrobić
            struct Employee {
                // pola structury
                std::string name;
                int age;
                double salary;
                // metody struktury
                void print() const;
                // konstruktor - do tworzenia obiektów
                Employee() = default;
                Employee(std::string name, int age, double salary);
            };
            // Zagnieżdżone struktury
            struct Stats {
                int hp;
                int attack;
                int defense;
                void show_stats() const;
            };

            struct Player {
                std::string name;
                int level;
                Stats stats;
                void introduce() const;
            };
            void show_player(const Player& player);
            void creation_and_access();
            void all();
        }
        namespace Inheritance {
            /*
             |-------------------
             |   DZIEDZICZENIE  |
             |-------------------
                Mechanizm dzieki któremu klasa pochodna
                    dziedziczy pola i metody z bazowej
                Konstruktory
                    każda klasa dziedziczy wszystko prócz konstruktorów
                    nie odziedziczy automatycznie
                    klasa dziedziczaca musi zaincjalizowac baze

                Najpierw baza potem konstruktor pochodnej
            */
            // struktur
            struct Animal {
                int _legs;
                public:
                    Animal() = default;
                    Animal(int legs);
                    int count_legs(); 
            };
            struct Dog : Animal { // dziedziczy po Animal
                std::string _name;

                public:
                    Dog();
                    Dog(std::string name);
                    Dog(int legs, std::string name);
                    void introduce();
            };
            /*
                Poziomy dziedziczenia:
            */
            class A {
                public:
                    int pub = 1;   // dostępne dla wszystkich
                protected:
                    int prot = 2;  // dostępne tylko dla dziedziczących klas
                private:
                    int priv = 3;  // dostępne tylko w A
            };
            class B : public A {
                /*
                    wszystkie dostępy jak w A są zachowane 
                     B b;
                    std::cout << b.pub;  // działa
                    // b.prot; nie działa (protected)
                    // b.priv; nie działa (private)
                */
            };
            class C : protected A {
                /*
                    pub   -> staje się protected
                    prot  -> zostaje procted
                    priva -> jest niedostepny
                
                    C c;
                    c.pub;  nie działa, bo pub jest protected
                */
            };
            class D : private A {
                // wszystko staje sie private
                // pub | prot | priv 
            };
        }
        namespace Polymorphism {
            /*
            Polimorfizm:
            
            Koncepcja która pozawala 
                    obiektowi zachować sie inaczej
                    w zależności od faktycznego typu obiektu
                Nadpisujemy override wirtualne metody klasy    
            
                Mamy wspólny interfejs
                    i różne klasy pochodne które robią coś innego
                a poprzez to możemy traktować je 
                jako ten sam typ bazowy w petli i kolekcjach
            
                Inaczej:
                    mechanizm języzka który pozwala
                        wołać metody po wskaźniku/refernecji do klasy bazowej
            */
            class Notification {
                public:
                    virtual void send(const std::string& message) const = 0; // czysto writualna
                    virtual ~Notification() = default;
            };

            // pochodna - email
            class EmailNotification : public Notification {
                std::string _email;
                public:
                    EmailNotification(std::string email)
                        : _email(std::move(email)) {}
                    void send(const std::string& msg) const override {
                        std::cout << "[EMAIL] To: " << _email << std::endl 
                            << "Content: " << msg << std::endl; 
                    } 
            };
            // pochodna - sms
            class SmsNotification : public Notification {
                std::string _phone_number;
                public:
                    SmsNotification(std::string phone_number) 
                        : _phone_number(phone_number){}

                    void send(const std::string& msg) const override {
                        std::cout << "[SMS] To number: " << _phone_number
                            << "\nMsg content: " << msg << "\n";
                    }
            };

            void broadcast(
                const std::vector<
                    std::unique_ptr<Notification>
                >& notifications,
                const std::string& message  
            );
            void show_broadcast();
            /*
                Interfejsy, klasy abstrakcyjne
                umowa (kontrakt) pomiedzy klasami
                gdzie każda, która dziedziczaca
                    musi zaimplementować dane metody
                
                Inefejs:
                    nie zawiera żadnej logiki
                    ma tylko deklaracje:
                        jakie metody mają istnieć
                        jakie argumenty i typy zwracają
                        ale nie definicje
                Interfejs:
                    to klasa któa ma przynajmniej jedną metode
                    czysto virtualną
                    virutal typ nazwa() = 0;
                Interface to szablon projektowy 
                    który mówi że każdy kto implemetuje go 
                        to musi mieć dane metody
                Nazewnictwo interfacu:
                    klasa interfacu zaczyna sie od 'I'

                Zazwyczaj nie ma konstruktora, ani pól
                    nie powiniene przechowywać żadnego stanu
            */
            struct IProcessor { 
                virtual void process(
                    const std::string& input
                ) = 0; 
                virtual ~IProcessor() = default;
            };

            struct Compressor : IProcessor {
                void process(const std::string& input) override {
                    std::cout << "[COMPRESSOR] Compressing data: " << input << '\n';
                }
            };

            struct Encryptor : IProcessor {
                void process(const std::string& input) override {
                    std::cout << "[ENCRYPTOR] Encrypting data: " << input << '\n';
                }
            };

            struct Logger : IProcessor {
                void process(const std::string& input) override {
                    std::cout << "[LOGGER] Saving data to logs: " << input << '\n';
                }
            };

            void pipeline(
                const std::vector<std::unique_ptr<IProcessor>>& steps,
                const std::string& input_text
            );

        }
        void demonstrate_classes();
        void show_pipeline_steps();
    }
    namespace ExceptionsKnow {
        /*
            Wyjątek - exception 
                kontrolowany skok przy błędzie
                rzucamy poprzez 
                    throw w miejscu błędu
                łapiemy poprzez
                    catch 
        */
        class CustomException : public std::runtime_error {
            public: 
                using std::runtime_error::runtime_error;
        };
        
        /*
            Exception posiada w sobie pola takie jak:   
                message - surowa treść kod (co poszlo nie tak)
                function - nazwa funckji w której rzucono wyjątek 
                    __func__ jak w pythonie
                file - plik źródłowy __FILE__
                line - linia gdzie wystąpił błąd
                code - kod błędu np 1001
                what - gotowy złożony komnikat zwracany do what()
        */
        
        //TODO definiowanie makr itp, do przerobienia potem
        #define THROW_CUSTOM(msg, code) \
            throw CustomWithFields((msg), (code), __func__, __FILE__, __LINE__)
        
        class CustomWithFields : public std::exception {
            private:
                std::string _message;
                std::string _function;
                std::string _file;
                int _line;
                int _code;
                std::string _what; 
            public:
                CustomWithFields(
                    std::string message,
                    int code,
                    std::string function,
                    std::string file_name,
                    int line
                );
                
                const char* what() const noexcept override {
                    return _what.c_str();
                }
                std::string diagnostic() const{
                    return _what;
                }
                int code() const noexcept { return _code; }
        };
        class ExceptionHandling {
            private:
                int _arg;
            public:
                ExceptionHandling() = default;
                ExceptionHandling(int arg);
                void throwing_one();
        };
        
        
        void show_all_exceptions();
    }
    namespace StringKnow{
        
        /*
            std::string 
                właścieciel danych
                    modyfikowalnyn bufor bajtów /tekst
                przechowuje własny bufor pamieci
                    kopiuje dane przy przypisaniu


            std::string_view- lekki, nieposiadający danych
                widok na ciag znakow
                Nie kopiuje tekstu, tylko wskazuje na istniejący fragment pamieci
        */
        class StringOperation {
            private:
                std::string base_text;

            public:
                StringOperation() = default;
                StringOperation(std::string base);
                void access();
                void modification();
                void searching();
                void triming_white_spaces();
                void regex_matching();
        };
       void show_all_string_operation();
    }
    namespace Collections {
        
        /*
            Vector - co to jest itp
                To dynamiczna tablica, ciągły blok pamieci 
                        zarzadzana automatycznie
                Działa jak tablica, ale sama powiększa bufor przy dodawaniu
                Iteratory /pointer / referencje mogą sie uniewaznić
                    przz realokacji
                - size()     ile elementów jest faktycznie
                - capacity() ile elementów mieści bufor
                - szybko wstawaia na koniec
        */
        class VectorExamples{
            public:
                std::vector<int> creation_ways();
                void access_to_elements(std::vector<int> numbers);
                void modification();
                void iteration();
                void sort_and_algorithms();
        };
        /*
            Map - słownik
                Para klucz i wartość
                    numer telefonu → imię
                    nazwa użytkownika → liczba punktów
                    dzień tygodnia → temperatura
                Klucze są unikalne i posortowane 
                    alfabetycznie, liczbowo itp

            różnica miedzy:
              unordered:  (bashowana)
                - nie sortuje kluczy 
                - gorsze zużyciepamieci, losowa kolejnosc

            pair: para klucz wartosc
                tworzenie:
                    klasyczny konstruktor
                        pair("key", "value")
                    lista inicjalizacyjna
                        pair = {key, value}
                c++17
                    rozbijanie pary na zmienne
                auto[name, score] = para
        */
        class MapExamples {
            public:
                std::map<int, int> creation_ways();
                void access_to_elements(std::map<int, int> scores);
                void modification();
                void iteration(std::map<int, int> scores);
                void sort_and_algorithms();
                void pair_know();
        };
        void show_all_methods();
    }
    namespace Functions {
        /*
            Funkcja anonimowa, pisana namiejscu
                bez potrzeby nazywania i defniowania
            
            Zamiast
                bool compare(const Player& a, const Player& b) {
                    return a.score > b.score;
                }
            mamy
                [](const Player& a, const Player& b) {
                    return a.score > b.score;
                })
        */
        class LambdaFunction {
            public:
                void syntax();
                // callback function
                void repeat(int amount, const std::function<void(int)>& fun);
                void show_function_examples();
            };

        class UsefulFunction{
            public:
                void checking_int();
        };
        void show_all_functions();
    }
}
