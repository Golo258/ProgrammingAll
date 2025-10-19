Etap 1 — Fundamenty języka i własne typy

    Cel:
        ogarnąć podstawy pisania kodu i prostych typów w C++, czyli to, co musisz znać, żeby cokolwiek ruszyło.

    Tematy:
        Struktura pliku .hpp i .cpp
        Tworzenie własnych typów (struct, class, enum)
        Hermetyzacja (private, public, protected)
        Gettery, settery, metody
        const i noexcept
        Statyczne pola i metody (static)
        this i fluent API (return *this;)

Ćwiczenia:
    Stworzyć klasę Dog, Car lub User z metodami, polami, walidacją danych.
    Napisać metody bark(), birthday(), rename() itp.

Etap 2:
    Cel:
        zrozumieć, jak działa dziedziczenie, wirtualne metody i nadpisywanie zachowań.

    Tematy:
        public/protected/private dziedziczenie
        Polimorfizm – co to znaczy i gdzie się go używa
        virtual, override, final
        Destruktory wirtualne
        Przykłady: Animal -> Dog/Cat, Shape -> Circle/Rectangle
        Wzorzec projektowy: interfejs (klasa abstrakcyjna)

    Ćwiczenia:
        Napisać klasę bazową Animal i kilka pochodnych (Dog, Cat)
        Dodać metodę speak() i zrozumieć, czemu virtual jest potrzebne.

Etap 3 — Enums, stałe i zasięgi

    Cel:
        opanować enumy i stałe w praktycznym użyciu.

    Tematy:
        enum vs enum class
        Używanie w switchu
        Mapowanie enum ↔ string
        const, constexpr, static const
        Globalne stałe i dlaczego lepiej ich nie nadużywać
        namespace jako kontener na stałe i funkcje


    Ćwiczenia:
        Enum LogLevel, Color, Direction
        Funkcja, która wypisuje nazwę enuma
        Stworzyć “konfig” z constexpr stałymi.

Etap 3.5:
    Własne typy (aliasy i “silne” typy):
        Alias typów: using Meters = int; (czytelność bez bezpieczeństwa)
        Alias templates: template<class T> using Vec = std::vector<T>;
        Silne typy (nowe wrappery):

Etap 4 — Operatory i przeciążenia

    Cel:
        nauczyć się przeciążać operatory logiczne i porównawcze jak człowiek.

    Tematy:
        Operatory: ==, !=, <, >, +=, << itd.
        Słowo friend i czemu czasem się przydaje
        Porównania obiektów
        Zasada: operator powinien zachowywać się intuicyjnie

    Ćwiczenia:
        Napisać klasę Vector2D z operatorami +, -, ==
        Napisać operator<< dla ostream, żeby ładnie wypisywać obiekt.

Etap 5 — Szablony (templates) i generyczność

    Cel:
        zrozumieć podstawy generyczności w C++ bez fikołków akademickich.

    Tematy:

        template<typename T> – jak działa
        Szablony funkcji
        Szablony klas (Vector<T>, Box<T>)
        auto, decltype
        typename vs class
        Krótkie wprowadzenie do concepts (C++20)

    Ćwiczenia:
        Napisać szablon funkcji max(), swap(), print_list()
        Napisać prostą klasę Box<T> trzymającą jeden element dowolnego typu.

Etap 6 — Kolekcje STL i praca z nimi
    Cel: 
        poznać najczęściej używane kolekcje z STL i ogarnąć ich zastosowania.

    Tematy:
        std::vector, std::map, std::unordered_map
        Iteratory, for(auto& x : container)
        find, erase, insert
        Różnice map vs unordered_map
        std::pair, std::tuple, std::optional (dla bonusu)
        std::string vs char* – czym się różnią i jak działa C-string

    Ćwiczenia:
        Napisać funkcję, która liczy wystąpienia słów w tekście (map<string,int>)
        Mały “notatnik” trzymający dane użytkowników (vector + map)

Etap 7 — Wskaźniki, referencje i rzutowanie

    Cel:
        oswoić się ze wskaźnikami i referencjami bez paniki.

    Tematy:
        Wskaźnik T* i dereferencja *p
        Referencja T&
        nullptr, new, delete
        unique_ptr, shared_ptr
        static_cast, dynamic_cast, reinterpret_cast (praktyczne różnice)
        size_t — co to za typ i dlaczego go używamy

    Ćwiczenia:
        Napisać prosty przykład z unique_ptr<Dog>
        Polimorfizm z shared_ptr<Base>
        Własna funkcja safe_cast() używająca dynamic_cast

Etap 8 — Wyjątki i błędy

    Cel: 
        nauczyć się obsługi błędów po ludzku, nie przez ify.

    Tematy:
        try, catch, throw
        Własne klasy wyjątków (dziedziczenie po std::exception)
        what() i diagnostyka błędów
        noexcept i kiedy warto
        Bezpieczne konstruowanie obiektów (RAII)

    Ćwiczenia:
        Stworzyć klasę FileReader, która rzuca wyjątek przy błędzie otwarcia pliku
        Napisać własny wyjątek InvalidAgeException.

Etap 9 — Strumienie i pliki

    Cel: 
        poznać typy strumieni i umieć zapisywać/odczytywać dane.

    Tematy:
        std::istream, std::ostream, ifstream, ofstream, stringstream
        Otwieranie, zapisywanie, odczyt
        Formatowanie danych (setw, setprecision)
        Bufory i getline

    Ćwiczenia:
        Odczytać dane CSV do vectora struktur

Etap 10 — Testy, asercje i dobre praktyki

    Cel:
        nauczyć się testować i pisać kod bezpieczny dla użytkownika.

    Tematy:
        assert() i statyczne asercje (static_assert)
        Proste testy jednostkowe bez frameworka
        Dobre praktyki: RAII, wyjątki, const-correctness
        Debugowanie i logowanie
        Refaktoryzacja i czytelność kodu

    Ćwiczenia:
        Napisać funkcję divide(a,b) z testami i obsługą błędów
        Napisać prostą klasę z testami walidującymi zachowanie.

Etap 11 — Mini projekt

    Cel:
        połączyć wszystko w praktyce.

    Pomysł:
        Zrobić mini projekt np.
        “Pet Manager” – zarządzanie listą zwierząt, plikami, logowaniem i wyjątkami
        albo “Task Tracker” – zapis zadań do pliku, edycja, wyszukiwanie