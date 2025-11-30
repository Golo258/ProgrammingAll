
// include/docs/knowledge.hpp
// ------------------------

#pragma once
#include <iostream>
#include <string>
#include <fstream>  // strumienie plikowe
#include <sstream>  // strumienie w pamieci 
#include <ctime>    // zarządzanie czasem
#include <vector>
#include <map>
#include <array>
#include <algorithm>
#include <numeric>  // accumulate 
#include <cctype>   // to lower | upper
#include <utils/variables.hpp>
#include <variant>  // union variant
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
        - może modyfikacja loggera żeby zapisywał do pliku i żeby terminal nie spamił
        - includowanie zewnętrznych bibliotek, ale to pewnie przy jsonie
        - przeciążanie operatorów, mniej wiecej jak to działa
        - wątki i programowanie wielowątkowe 
        - tworzenie baz danych
            łączenie sie, tworzenie query, itp
        - tworzenie requestów do api, i parsowanie tego
            - tworzenie własnego API, ale to nie wiem czy nie lepiej w pythonie
*/
/*--------------Knowledge NAMESPACE---------------------------------*/
namespace Knowledge {
/*--------------StreamsManagement NAMESPACE---------------------------------*/
    namespace StreamsManagement {
        /* Strumień
            - kanał przepływu danych , obiekt zarządzający tym przepływem
            - dane przepływają:
                wchodzą i wychodzą do miejsc takich jak
                -> tekst, plik, sieć, pamięć -- wszystko leci przez strumienie
            - dane mogą płynąć na zewnątrz (out) programu
                - std::ostream 
            - dane mogą płynąć do programu (in)
                - std::istream
            --------------------------------
            INPUT - program czyta / pobiera dane z zewnątrz
                pobiera dane z pliku/terminala/bufora i czyta je na konsole 
                buffor >> zmienna; czytamy z buffora
            OUTPUT - program wysyła / wyrzuca dane na zewnątrz
                bierze dane jakieś i wysyła je do pliku
                buffor << "dane"; - wysylamy do buffora
            --------------------------------
            Kierunki:
                wejście - in  | istream |  cin | ifstream | istringstream | 
                wyjście - out | ostream | cout | ofstream | ostringstream | 
                wejscie & wyjscie - iostream --> input output stream
                              | fstream | stringstream |
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
/*----------StreamsManagement::StandardStream class definition------------*/
        class StandardStream {
        /* Strumienie standardowe
            cin  - wejscie  - czyta z klawiatury
            cout - wyjscie  - pisze na standardowe wyjscie - terminal
            cerr - wyjscie  - pisze błędy bez buforowania
            clog - wyjscie  - pisze logi z buforowaniem
            -> Każdy z nich jest obiektem klasy 
                - std::istream - wejscie
                - std::ostream - wyjscie
                - iostream łaczy oba - plikowy może być jednym i drugim
            
            Każdy ze strumieni ma operator bool()
                w momencie gdy do strumienia wpadła zła wartość
                i wykryto błąd to coś możemy zrobić 
                if (!std::cin)

            W linuxie:
                ./program > output.txt 2> errors.txt
                    > output.txt - wyłapie cout i clog
                    2> - wyłapie cerr
        */
            public:
                std::vector<std::string> read_lines(std::istream& is);
                void print_list(std::ostream& os, const std::vector<int>& items);
                void standard_output();
                void standard_input();
        };
/*----------StreamsManagement::FileStream class definition------------*/
        class FileStream {
        /* Strumienie plikowe <fstream>
                ifstream - wejscie - czytanie z pliku
                ofstream - wyjscie - pisanie do pliku
                fstream  -  oba    - czytanie i pisanie

            Tryby otwierania:
                std::ios::
                    - in  - czytanie 
                    - out - pisanie
                    - app - dodawanie append - na koniec
                    - trunc - czyszczenie pliku przy otwarciu
                    - ate - at end - ustawiane na końcu
                    - binary - tryb binarny 
                Można miksować poprzez | 
                    np std::ios::out | std::out::trunc
        */
            public:
                void write_data_out();
                void write_data_out_by_append();
                void read_from_in();
        };
/*----------StreamsManagement::MemoryStream class definition------------*/
        class MemoryStream {
        /* Strumienie w pamięci <sstream>, 
            - służą do pracy z tekstem w pamieci,
                mamy bufor tekstu z wieloma liniami 
                | istringstream | ostringstream |
            Buffor - po co jak i gdzie i co to jest 
                Bufor to tymczasowa pamieć (RAM)
                    w której gromadzimy dane zanim 
                    zostaną odczytane albo zapisane
                To magazyn pośredni miedzy 
                    kodem a źródłem docelowym - plikiem, klawiaturą
            Tymczasowe miejsce, gdzie trzymamy dane
                zanim coś z nimi zrobisz
            std::cin - bufor wejsciowy 
                system trzyma znaki które wpisuje zanim pogram je pobierze
            logger.debug() - bufor wyjściowy
                tekst trafia do buffora, a dopiero potem do terminala
        */
            public:
                void load_string_into_buffor();
                void load_data_into_buffor();
                void read_and_write_data_to_buffor();
        };
/*----------StreamsManagement::FileSystemManagment class definition------------*/
        namespace fs = std::filesystem;
        class FileSystemManagment {
            /* filesystem:
                    standardowe funkcje do pracy
                        z plikami / scieżkami / katalogami
                    najcześciej sie używa aliasu do namespaca
                    namespace fs = std::filesystem
    
                Ścieżki:
                    fs::path
            */
            public:
                fs::path create_paths();
                void paths_management(fs::path score_path);
                void file_states(fs::path file_path);
                void modification(fs::path file_path);
                void get_file_from_resources();
        };
    }
    
/*--------------AliasesAndTypes NAMESPACE---------------------------------*/
    namespace AliasesAndTypes {
        // stosuejmy pascal case - czyli duża litera i potem małe
        
        /*
            Podstawowe aliasy: syntaxy
                typedef typ NazwaAliasu;
                using NazwaAliasu = typ
                using NazwaAliasuFUnckji = typ(*)(typ argumentu)

            Aliasy szablonowe:
                template<typename NazwaTypu>
                using NazwaAliasu = std::vector<NazwaTypu>
            
            Silne typy:
                unikalny typ - using UserIdAlias = int; 
                - struct UserId {};
                - class classUser{};

            Alias dla przestrzeni nazw:
                -namespace NazwaAliasu = NazwaNamespacu;
                do funkcji w przestrzeni nazw
                  -using NazwaAliasuFunckji = NazwaNamespacu::funkcja;
            variant, pozwala dać możliwośc wyboru typu
                ten typ albo ten typ
                - std::variant<std::string, intQ possibilities;
            
            klasyczny union
                pudełko na kilka typów
                union Nazwa { int a, double b...};
        */
        // ----------BASIC ALIASES------------ 
        inline void basic_aliases_definition(){
            typedef unsigned int Uint32;
            using ULL = unsigned long long;
            using Callback = void(*)(int);// zamiast  void f(int)
        }
        // ----------TEMPLATE ALIASES------------
        template<typename T>
        using TypeVec = std::vector<T>;

        template<typename T>
        using StringMap = std::map<std::string, T>;
            

        // ----------STRONG ALIASES------------
        using UserIdAlias = int; 
        struct UserId {
            int value;
            explicit UserId(int value) : value(value){}
        };

        // ----------NAMESPACE ALIASES------------
        inline void namespace_aliases_definition(){
            namespace KMD = Knowledge::StreamsManagement;
            using StreamReader = Knowledge::StreamsManagement::StandardStream;
        }
        // ----------MULTIPLE TYPES ALIASES------------
        inline void multiple_types_aliases_definition(){
            union PossibleTypes {
                int i;
                double d;
                char c;
            };
            struct TaggedValue {
                PossibleTypes value;
            };
        }
/*----------AliasesAndTypes::AliasesPlayground class definition------------*/
        class AliasesPlayground {
            public:
                static void basic_aliases();
                static void template_aliases();
                static void strong_types();
                static void play_with_variant_save_union();
                static void play_with_optional();
        };
/*----------AliasesAndTypes::CastingPlayground class definition------------*/
        class CastingPlayground {
            /*  Castowanie - rzutowanie - zamiana jakiegos typu 
            Kompilator albo automatycznie rzutuje zmienną   
                albo chce żebyśmy świadomie rzutowali
            Typy castów:
                - implicit conversion - automatyczne rzutowanie
                - (typ) -> stary styl z C 
                - static_cast:
                    normalne, bezpieczne castowanie typów pokrewnych
                        int na double
                        char na int itp.
                        wskaźnika na typ bazowy w klasach
                    Syntax:
                        static_cast<na_jaki_typ>(jaką zmienną)
                - const_cast
                    usuwanie lub dodawanie const
                    używane tylko do manipulowania const
                    np: gdy masz funckje const ale potrzebuje tam cos zmienic

                - reinterpret_cast
                    nie zmienia danych, tylko zmienia
                    sposób ich ich interpetacji w pamieci
                    Używany do niskopoziomowgo kodu
                    sieciowych, bibliotek systemowych
                    Mało używany
                - dynamic_cast
                    rzutowanie obiektów miedzy klasami w OOP
                    Przy dziedziczeniu i polimorfizmie
            */
        public:
            void implicit_conversion();
            void convert_static_cast();
            void convert_const_cast(const int* value);
            void convert_reinterpret_cast();
            struct Base {
                virtual ~Base() = default;
            };
            struct Derived : Base {
                inline void say(){
                    logger.debug() << "Something\n";
                }
            };
            void convert_dynamic_cast();
        };

/*----------AliasesAndTypes::PointersPlayground class definition------------*/
        class PointersPlayground {
            /*  wskąźnik, czyli
                    zmienna która przechowuje adres obiektu /zmiennej
            Dynamiczne tworzenie obiektów
                należy samemu zarządzać pamiecią 
                i ją potem zwalniać poprzez delete
            Smart pointers - bezpieczne wskaźniki
                z klasy memory
                automatycznie zarządzają pamiecią
            
            Typy:
                std::unique_ptr
                    wyłączna własność obiektu
                        tylko on może przechowywać adres obiektu
                    syntax:
                        std::unique_ptr<typ> nazwa = std::make_unique<Typ>(obiekt)
                    Po wyjściu ze scopa automatycznie jest wywoływany destruktor
                    Nie można kopiować obiektu pomiedzy innymi pointerami
                    Zdefiniowany obiekt należy już tylko do tego danego pointera
                    Ale można przekazać wartość poprzez
                        std::move(pointer);

                shared_ptr<>  make_shared<>(obiekt);
                    wiele pointerów może korzystać z obiektu
            */
           public:
                struct Person {
                    int _age;
                    Person(int age) : _age(age) {}
                    ~Person() { logger.debug() << "End of story\n"; }
                    void introduce(){
                        logger.debug() << "age: " << _age << std::endl;
                    }
                };

                struct Connection {
                    std::string name;
                    int accounts;     
                    Connection() { logger.debug() << "Openning connection \n"; }
                    ~Connection() { logger.debug() << "Closing connection \n"; }
                };
                void basic_pointer();
                void pointer_to_structure();
                void allocate_memory_dynamic();
                void unique_pointer();
                void shared_pointer();
        };
/*--------------AliasesAndTypes::Enums namespace---------------------------------*/
        namespace Enums {
            /*  Enum - typ wyliczeniowy
                    nadaje nazwane stałe wartościom liczbowym
                    Zamiast pisać dane liczby 
                        to mają one określony sens
                Każdy element to domyslnie int 
                    zaczynający się od 0
                Można przypisać konkretne wartości do typów
                Stary styl definiowania:
                    enum Nazwa { typ = wartosc; }
                
                Nowoczesny styl i typ definiowania:
                    enum class - jest on silnie typowany
                        nie miesza sie z int
                        nie wchodzi w globalny namespace
                        wymaga jawnego rzutowania 
                Aby dostać sie do wartość 
                    wymagane jest rzutowanie na inta
                można obrać jaki jest typ bazowy 
                    rozmiar / zarkes 
                
                jak jest sam enum Something {}
                    to wszystkie wartości które są zdefinowane
                    są wrzucone prosto do globalnej przestrzeni nazw
                        jaky na luzie, a mogą byc potem konflikty
                    i wtedy można sie odwołać czysto do WARNING
                    a nie trzeba do Status::WARNING
                        co jest niebezpieczne imo
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

            enum class RequestMethod {
                GET,
                POST,
                DELETE
            };

            enum class Color : uint8_t {
                RED   = 0xFF,//  można przypisać hexa
                GREEN = 0x80,
                BLUE  = 0x40,
                BLACK = 0x00
            };
/*----------AliasesAndTypes::Enums::EnumPlayground class methods------------*/
            class EnumPlayground {
                public:
                    std::string request_method_to_string(RequestMethod method);
                    std::optional<RequestMethod> string_to_request_method(const std::string& method_str);
                    void basic_enum_attribute_check();
                    void enum_class_value_retrieval();
                    void enum_class_hex_attribute_value();
                    void enum_as_vector_type_iteration();
                    void mapping_enum_to_string();    
            };
        }
/*--------------AliasesAndTypes::Templates NAMESPACE---------------------------------*/
        namespace Templates {
            /* Co to jest template:
                to sposób na pisanie uniwersalnego kod
                    dla wielu typów, bez duplikowania funkcji 
            Wewnątrz:
                kompilator nie wie jaki jest typ od razu
                Generuje kod wtedy gdy wywołujemy funkcje z 
                konkretynymi argumentami o danych typach
                    podstawia wtedy dany typ i generuje kod
            Każdy typ to osobna wersja funkcji
                instancja szabonu

            !!WAZNE!!
            Typy muszą wspierać operacje użyte w funkcji
            np:  Jeśli robimy operacje a + b
            to kompilator wymaga żeby typ miał operator +
                można samemu postawić typ
                    add<int>(3, 5);
                    ale kompilator sam sie domyślna
                
            Konwencje nazywania typu w templacie:
                T (Type) | TReturn  
                TValue   | TKey
                TElement | TData
            
            Szablony funkcji:
                template<typename T>
                T nazwa_funkcji(const T& a, const T& b);
            
            Jeśli potrzebujemy mieć typy mieszane 
                to do definicji dajemy kilka typów
                template<typename Type_a, typename Type_b>
                
            KLASY SZABLONOWE
                kompilator widzi że dana klasa to template
                towrzy kopie kodu wtedy gdy użyjemy innego typu
                każdy typ ma osobną implementacje
                    tak jak funkcje szablonowe

            Uniwersalny przepis na dany obiekt
                T to miejsce na typ który wstawiamy później
            Kiedy używamy z danym typem
                kopmilator tworzy wersje klasy i wszedzie wrzuca swój typ
            */ 
            //  Zamiast pisać dwie różne funkcje
            inline int add_int(int a, int b ) { return a + b; }
            inline double add_double(double a, double b) {return a + b; }
            
            template<typename Type> // Piszemy jedną wersje
            Type generic_add(Type a, Type b){ return a + b; }

            template<typename Type>
            Type max_of(const Type& prev, const Type& next){
                return (prev > next) ? prev : next;
            }
            
            template<typename Type_a, typename Type_b>
            auto add_different(Type_a first, Type_b second){
                return first + second;
            }

            template<typename TData>
            class GenericBox {
                private: 
                    TData _value;
                public:
                    GenericBox(TData value) : _value(value){}
                    TData get() const { return _value; }
                    void set(TData new_value){ _value = new_value; }
            };

            template <typename TKey, typename TValue>
            class GenericPair {
                private:
                    TKey _key;
                    TValue _value;
                public:
                    GenericPair(TKey key, TValue value)
                        : _key(key), _value(value) {}
                    TKey get_key() const { return _key; }
                    TValue get_value() const { return _value; }
            };

            // Klasa GenericItemsContainer
            template <typename TItem>
            class GenericItemsContainer {
                private:
                    std::vector<TItem> _items;
                    inline static int containers_amount = 0; //statyczne pole musi być zaincjalowane przed
                    
                public:
                    GenericItemsContainer() { containers_amount++; } 
                    ~GenericItemsContainer(){ containers_amount--; }
                    GenericItemsContainer(size_t size){
                        _items.reserve(size);
                        containers_amount++;
                    }
                    // wypełnia n kopiami 'value'
                    GenericItemsContainer(std::size_t n, const TItem& value) {
                        _items.assign(n, value);    
                        containers_amount++;
                    }

                    GenericItemsContainer(std::initializer_list<TItem> items) 
                        : _items(items) {
                        containers_amount++;
                    }

                    void add(const TItem& item){ _items.emplace_back(item); }
                    void print_all_items() const {
                        for (const TItem& item: _items){
                            logger.debug() 
                                << "Item [" << item << "]\n"; 
                        }
                    }
                    static int get_active_containers(){ return containers_amount; }
            };
            class TemplatePlayground {
                public:
                    void basic_redundancy_difference();
                    void template_functions();
                    void template_classes();
                    void template_as_vector_type();
            };
        }
    }

/*----------------NameSpacesKnow NAMESPACE---------------------------*/
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

/*----------------CompileTime NAMESPACE---------------------------*/
    namespace CompileTime {
        /* W C++ są dwa czasy:
        Compile Time - czyli rzeczy które dzieją sie podczas kompilacji
            - kompilator możę liczyć pewne rzeczy od razu
            - dzieki czemu program działa szybciej
            - albo pozwala na rzeczy, które wymagają stałych wartości
            np:  constexpr int x = 5 + 5; policzone zanim program sie uruchomi

        Run Time - czyli wszystko co sie dzieje kiedy program sie wykonuje
            int a = user_input()
            int b = a +_5; // liczy podczas działania programu
        
        constexpr - mówi do kompilatora
            zrób wszystko co sie da już podczas kompilacji
            syntax: constexpr typ nazwa_zmiennej = wartość;
                wartosc musi być znana w czasie kompilacji
            wartosci z constexpr mogą działać też w runtime

        constexpr functions:
            prefix przed funckją mówi nam że:
            funkcja może zostać policzona podczas kompilacji
            ale tylko jesli warunki na to pozwalają
                czyli jesli wartosci zmiennych są znane w compile-time
            jesli nie to C++ automatycznie wybierze runtime

        consteval - natychmiastowa funkcjia
            mówi do kompilatora że musi być ona policzona w compile-time
            nie wolno wywoływać jej w runtime
            wymurza wyliczenie wartość w compile_time
        
        constinit - zmienna musi być zainicjalizowana w compile-time
            potem może być zmieniana, musi być statyczna
            nie musi być constexpr
            Przydatne w inicjalizacji stałych globalnych zmiennych
        
        constexpr w klasach:
            w konstrutrze
            w metodach
            w operatorach
            w obiektach klasy/ struktur / templatów
        */

        constexpr int factorial(int numb){
            return (numb <= 1) ? 1 : numb * factorial(numb - 1);
        }

        consteval int make_id(int x){
            return x * 10;
        }

        inline constinit int global_counter = 0; 
        struct Point {
            int x;
            int y;
            constexpr Point(int a, int b)
                : x(a), y(b){}
            
            constexpr int length_squared() const {
                return (x * x) + (y * y); 
            }
        };

        class CompilePlayground {
            public:
                void compile_time_basic_definition();
                void compile_time_functions();
                void only_compile_time_functions();
                void only_compile_time_inicialization();
                void compile_time_in_classes();
        };

    }
/*----------------Preprocesor NAMESPACE---------------------------*/
    namespace Preprocesor {
        /*  Preproces 
            to etap który działa zanim kod C++ trafi do kompilatora
            czyta plik źródłowy i dokonuje zamian tekstowych
        Zanim skompiluje kod, preprocesor:
            rozwija #include 
            podstawia #define 
            #usuwa fragmenty zależne od #ifdef #ifndef
            przetwarz #pragma itd
            g++ -E main.cpp -- jak to działa
            
        Makra symboliczne:
            syntax: #define  nazwa_makra wartosc 
        Makra funkcyjne -  czyli funkcje bez typów i kompilacji
            synax: #define  nazwa_funkcji(parametry) (operacje na parametrach)
        Makra warunkowe
            pozwalają kompilować rózne kawałki kodu
            w zależności od warunków
            - #ifdef x // jesli x jest zdefinowane
            - #ifndef x // jesli x nie jest zdefinowane
            - #endif  -konie cwarunku
            - #undef x - usuń definicje
            - include guard
            - #pragma once - zabezpieczenie przez wielokrotnym includowanie
                #ifndef LOGGER_HPP // zamiast tego 
                    #define LOGGER_HPP
                    ... kod
                #endif
        Parametry przekazywane z kompilatora: kompilacja z parametrem
            -D np: g++ -Dversion=3 main.cpp 
            to tak jakby kompilator dodał na początku pliku
                #define version 3
            Inne:
                #error	  ręczne przerwanie kompilacji
                #warning  ostrzeżenie podczas kompilacji
        */
        #define PI 3.141624
        double circle_area(double radius);
        void all();
       
        #define SQUARE(x) ( (x) * (x))
        // w nowoczesnym pisze sie 
        template <typename MathType>
        constexpr MathType square(MathType var){
            return var * var;
        }

        #define DEBUG_MODE 
        #ifdef DEBUG_MODE // jesli jest zdefinowane
            #define LOG(x) logger.debug() << "[DEBUG]" << x << "\n"
        #else
            #define LOG(x)
        #endif

        #ifdef VERSION
            #if VERSION == 3
                logger.debug() << "Wersja 3!\n";
            #elif VERSION == 2
                logger.debug() << "Wersja 2!\n";
            #else
                logger.debug() << "Nieznana wersja\n";
            #endif
        #endif
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
                    logger.debug() << b.pub;  // działa
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
                        logger.debug() << "[EMAIL] To: " << _email << std::endl 
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
                        logger.debug() << "[SMS] To number: " << _phone_number
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
                    logger.debug() << "[COMPRESSOR] Compressing data: " << input << '\n';
                }
            };

            struct Encryptor : IProcessor {
                void process(const std::string& input) override {
                    logger.debug() << "[ENCRYPTOR] Encrypting data: " << input << '\n';
                }
            };

            struct Logger : IProcessor {
                void process(const std::string& input) override {
                    logger.debug() << "[LOGGER] Saving data to logs: " << input << '\n';
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
