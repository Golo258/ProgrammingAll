
Komedny co robić i jak podłączać to:
message()
    log - do debugowania w cmake
    syntax:
        message(MODE "message_text")
        MODE:
            FATAL_ERROR
            SEND_ERROR
            WARNING
            AUTHOR_WARNING
            DEPRECATION
            STATUS
            
#--------------------------------------------
set()
    tworzenie zmiennej
    nie piszemy int x = 5 tylko set()
    syntax:
        set(NAZWA_ZMIENNEJ "wartosc")
    dostęp do zmiennych zdefiniowanych:
        ${ZMIENNA}

    do czego służy:
        - skracanie ścieżek 
            set(INCLUDES_DIR "dev/tracker/include")
        - ustawianie kompilatora:
            set(CMAKE_CXX_STANDARD 20)
        - ustawianie listy plików
            set(SOURCES_LIST  main.cpp tracker.cpp logger.cpp)
            
    - ten target to taki haczyk do którego można dowiązać inne rzeczy
        nagłówki, biblioteki, definicje itp

#--------------------------------------------
add_executable()
    - mówi Cmake, żeby stworzył gotowy do odpalania program - binarke
        - bierze dany plik/pliki źródłowe,
            przemiela je i skleja w jeden plik - binarke do uruchomienia
        skleja - zlinkuje je w jeden plik wykonywalny 
    
    syntax:
        add_executable(NAZWA_TARGETU plik_źródłwy1.cpp plik2cpp ..)
            NAZWA_TARGETU - nazwa programu wewnątrz Cmake
                poprzez tą nazwe odnosisz sie do aplikacje 
                przy skompilowaniu tak sie bedzie nazywał plik w build
                

#--------------------------------------------
add_library()
    biblioteka - pudełko z gotowymi narzedziami
        zbiór funkcji, klas, struktur, które same z siebie nic nie robią
        nie mają main() - są to tylko pliki .o - skompilowany kod 
        zapakowane w jeden plik math_lib.o

    główna aplikacja mówi tylko danym bibliotekom co mająrobić


#--------------------------------------------
target_include_directories()
    - gdzie jest mój plik nagłowkowy.hpp
    - gdy piszemy #include "plik.hpp"
        kompilator usi wiedzieć w którym folderze szukać, domyślne patrzy tylkotam gdzie jest .cpp - i uruchamiamy program
    - lista folderów które dajemy kompilatorowi do sprawdzenia
    Sytuacja:
        nagłówki trzymamy w inc
        robimy w main.cpp #include "header.hpp" - on patrzy tylko na roota, i nie ma tam nagłówka, wiec nie wie gdzie on jest
    syntax:
        target_include_directories(żródło  PRIVATE  folder_z_nagłówkiem)
        w komendarz target_ musimy określić zasięg:
            PRIVATE 
                - tylko ten dany target (aplikacji) widzi ten nagłowek,
                - jesli ktos inny podłączy aplikacje, to nie zobaczy naglówka
            INTERFACE:
                - target nie używa nagłówka u siebie, ale kazy kto sie do niego podepnie musi je dodać
            PUBLIC:
                - wszyscy widzą wszystko
                - target używa tych nagłówków
                - każdy kt osie podepnie to tez go widzi

        w kontekscie bibliotek:
            gdy podpinamy nagłówki do bibliotek
        to gdy chcemy podłączyć biblioteke, to główna aplikacja nie potrzebuje dołączać specjalnie
            headersów bibliotek, biblioteka mu o tym powie jak jest scope PUBLIC

#--------------------------------------------
target_link_librarties()
    - to jest klej, komenda mówi:
        bierzemy ten projekt (target) i dołączamy do niego tamtą biblioteke

    - przekazuje paczke / moduł - math_lib, z headersami podpietymi do niej (PUBLIC)
        aplikacja używa biblioteki - podpina sie do niej  target_link_libraries
        Cmake widzi że biblioteka ma publiczne nagłółwki do automatycznie wstrzykuje je 


#--------------------------------------------
Używanie external libraries:
    nie piszemy wszystkiego sami, tylko używamy gotowców
    z zewnątrz
    bibliotek które są zainstalowane na systemie
        np w /usr/lib  /usr/include itd
    Żeby cmake je znalazł potrzebujemy mu je wskazać
    - find_pakackge()
        - znajdz na PC daną biblioteke w wersji xxx
        - jak nie znajdziesz to wyrzuć błąd i nie zaczynaj budowani
        - szuka w standardowych folderach systemowowych plikó konfiguracyjnych biblioteki
        - jeśli znajdzie to tworzy targety które można używać w target_link_libraries
    
#Przykład biblioteka CURL
    sudo apt update
    sudo apt install libcurl4-openssl-dev
    cd /usr/include/wersja_linuxa(x86_64-linux-gnu)/curl/curl.h

    # do CMakeList.txt
    find_package(CURL REQUIRED)
    target_link_libraries(target_app PRIVATE CURL::libcurl)

        W doku znajdziesz target: https://cmake.org/cmake/help/latest/module/FindCURL.html
            Imported Targets
                This module provides the following Imported Targets:

                CURL::libcurl
                Added in version 3.12.

                Target encapsulating the curl usage requirements, available if curl is found.

#--------------------------------------------
function():
    to po prostu funkcja, nazwany blolk kodu, który można wykonywać wielokrotnie
    syntax:
        function(nazwa_funkcji parametr1 parametr2)
            //.. ciało
        endfunction()

    file(GLOB)
        global - polecenie które mówi cmakowi
        przeszukaj ten dany folder i stwórz liste plików które pasują do danego wzroca
        np:
            file(GLOB MY_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
            
#--------------------------------------------
Komendy Linuxowe Cmake:
    Czysty folder build/ - wchodzimy do niego 
    cmake ..
        1.  Sprawdza środowisko
        - szuka kompilatora 
        - Sprawdza czy kopmilator działa, 
        - Sprawdza istnienie bibliotek (find_pacakges)
        2. Wykonuje instrukcje w CmakeLists.txt
            - czyta od góry do dołu
            - to jest generator, nie kompilator
            - generuje on plik MakeFile
            - generuje pliki które są instrukcją obsługi dla komputera
                jak ma pokolei wykonać komendy kompilator g++, żeby złożyć program
            - ustawia zmienne CACHE->plik CmakeCashe.txt
                set( CACHE) - wtedy zmienna jest w pamieci aż nie wyczyścimy build/

    cmake --build .
        - kompilator g++ dostaje polecenie z Cmaka, które stworzył na podstawie treści
            np: g++ main.cpp -o inc
        - dostajemy potem plik wykonywalny 
            ./cmake_learn_app

#--------------------------------------------
function() - jak tego używać 

find_package() - DONE
add_library() - DONE 
target_include_directories() - DONE  
target_link_libraries() - DONE
target_compile_definitions() # todo
add_executable() - DONE 
attach_resources() - co to jest 
