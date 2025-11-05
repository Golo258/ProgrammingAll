
// docs/knowledge.hpp
// ------------------------

#pragma once
#include <iostream>
#include <utils/logger.hpp>
#include <string>
#include <fstream> // strumienie plikowe
#include <sstream> // strumienie w pamieci 
#include <ctime> // zarządzanie czasem

// ------------------------
/*
    Co trzeba będdzie sie nauczyć 
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

}
