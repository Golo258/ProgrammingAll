
// docs/knowledge.hpp
// ------------------------

#pragma once
#include <iostream>
#include <utils/logger.hpp>
#include <string>
#include <fstream> // strumienie plikowe


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
        

        Strumienie w pamięci <sstream>
            służa do pcy z tekstem w pamieci
                bufor tekstu z wieloma liniami
                istringstream
                ostringstream

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
        */
        class FileStream {
            public:
                void writing_overriting();
                void appending();
        };
        void show_file_stream();
    }
    int sum();

}
