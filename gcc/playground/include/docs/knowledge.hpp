
// docs/knowledge.hpp
// ------------------------

#pragma once
#include <iostream>
#include <utils/logger.hpp>
#include <string>
#include <fstream> // strumienie plikowe
#include <sstream> // strumienie w pamieci 
#include <ctime> // zarządzanie czasem
#include <vector>
#include <map>
#include <algorithm>
#include <numeric> // accumulate 
// ------------------------
/*
    Co trzeba będzie sie nauczyć 
        - 1 przechwytywanie strumienia
            - jakie są typy strumienia itp
        - Jak przechwytywać wyjątki
        - Jak tworzyć wyjątki

*/
namespace Knowledge {
    /*
    Strumienie w c++, związek miedzy wejściem / wyjściem I/O
        tekst, pliki, sieć, pamięć -- wszystko leci przez strumienie
        Strumień - co to jest 
            to jest obiekt który potrafi
                - czytać dane - input stream
                - pisać dane  - output stream
                - lub oba 
        jak rura przez którą przepływa tekst 
        << - pisanie - wyjście   - coś wychodzi 
        >> - czytanie  - wejście - coś wchodzi 
    */
    namespace StreamsManagement {

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
            Tymczasowe miejsce, gdzie czają dane zanim coś 
                z nimi zrobisz
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
        
        
        void simple_tasks();
        void show_file_stream();

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

    namespace Aliases {
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

    }
    namespace NameSpacesKnow {
        // Namespacy wytłumaczenie
        /*
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
    namespace StringOperations{
        
        /*
            std::string 
                przechowuje własny bufor pamieci
                kopiuje dane przy przypisaniu

            std::string_view- lekki, nieposiadający danych
                widok na ciag znakow
                Nie kopiuje tekstu, tylko wskazuje na istniejący fragment pamieci
        */
       void string_example();
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
        };
        void show_all_methods();
    }
}    


