

#Projekt 1:
    Board:
        tablica wyników

Co do zrobienia:
    1. Parser linii 
        pary (nazwa_gry/imie_osoby, wynik)
        Pliki:
        include/utils/parse.hpp
        moduiles/utils/parse.cpp

# założenia zadania
Api do parsowania: parse.hpp / parse.cpp
    /*
        Wejscie: bufor tekstu z wieloma liniami
        Format linii: "<name> = <score>"
            Spacje dookoła nazwy sa git, trzeba ztrimować
            Linie puste i zaczynające sie od # ignorujemy // komentarz
            <score> przyjmujemy to liczba całkowita -int
            Jesli linia ma zły format to rzucamy ParseError 
                z opisem i numerem linii

        Zasady parsowania:
            separatorem jest dokładnie jeden znak = 
                wiecej to błąd
            <name> nie moze byc pusty po trimie
            <score> musi byc intem
        Przykładowy:
            # sample
            Alice = 10
            Bob=7
        Oczekiwany wynik:
            {
                {"Alice",10},{"Bob",7}
            }
    */

Klasa LeaderBoard:
    Przechowuj wyniki w:
        std::unorder_map<std::string, int>

    Do top(n) wez dane z mapy, zrob kopie do std::vector
    posortuj po DESC ASC 

    print() -- spiecie z loggerem

3) Aplikacja demonstracyjna
    Plik:
        apps/playground/main.cpp

    Zachowanie:
            Jeśli uruchomisz bez argumentów: użyj wbudowanego tekstu (z sekcji parsera).
            Jeśli z 1 argumentem: potraktuj go jako ścieżkę do pliku i wczytaj cały plik.
            Skorzystaj z utils::parse_name_score_lines(...), wczytane pary wrzuć do Leaderboard przez set_score.

        Pokaż:
            top(3) wypisane przez print(std::cout, 3) (albo Twój Logger).
            Dodaj add_or_update("Alice", +5), potem ponownie top(3).
            average() i median() wypisz jako liczby (lub “n/a” jeśli brak).
            remove_below(0) i pokaż ile usunięto, a potem top(10).

4) Testy minimalne (asercje)

    Plik:
        tests/test_core_results.cpp

    Wymagania (użyj zwykłych assert, bez frameworka):

        Parser:
            Poprawny przykład zwraca 3 pary, dokładnie z oczekiwanymi wartościami.
            Dla linii “X = not_a_number” ma polecieć utils::ParseError.
        Leaderboard:

            add_or_update sumuje.
            top(n) ma poprawną kolejność przy remisach (alfabetycznie).
            median() poprawna dla parzystej i nieparzystej liczby elementów.
            remove_below zdejmuje to, co ma zdjąć, i zwraca dobrą liczb


Kryteria zaliczenia (checklista)
    parse_name_score_lines poprawnie zwraca dane i rzuca ParseError z numerem linii przy błędzie.

    Leaderboard kompiluje się jako osobna biblioteka, posiada metody z wymagań, nie używa globali.

    top(n) jest stabilne wg reguły: wynik malejąco, nazwa rosnąco przy remisach.

    median() działa dla 0/1/2/… elementów (dla 0 → std::nullopt).

    print() wypisuje numerowane pozycje 1), 2), 3) …

    apps/playground pokazuje pełny flow (load → top → update → stats → prune → top).

    Testy w tests/ przechodzą (uruchom ctest lub ./core_tests).
    

Rozszerzenia (opcjonalne, jak będziesz miał flow)

    Wczytywanie z pliku: dodaj utils::read_file(std::filesystem::path) i użyj w main.
    Eksport: metoda to_vector_sorted() zwracająca cały ranking posortowany regułą TOP.
    Wyjątki własne: zrób struct LeaderboardError : std::runtime_error.
    Szablony (mini-smaczek Stage 5): zrób generyczne top<TExtractor> i pozwól sortować po extract(score) (np. absolutna wartość).
    Operator<<: przeciąż operator<< (std::ostream&, const Leaderboard&), aby drukować cały ranking.
    Jak uruchomić (przykład)
