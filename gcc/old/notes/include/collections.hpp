// =============================
// collections.hpp
// =============================
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

/*-------------- DECLARATIONS ----------------------*/
/*
    STL - Standard templates library
        contains -
        trzymają obiekty wartościowo (kopiują przenosza element do środka)

    3 rodziny kontenerów;
        Sekwencyjne:
            vector, string, array, deque, list, forward_list
        Asocjacyjne(posortowane):
            map, multimap, set, multiset
        Unordered(hashe):
            unordered_map, unordered_set itd
        
    Do poruszania sie używamy itertorów:
        algorytmy z <algorithm> 
            sort find_if, transform accumulate
    
*/

/*
    Vector: dynamiczna tablica O(1)
        dostep po indeksie, szybka iteracja 
        Tworzenie
            std::vector<int> v;
            std::vector<int> v(n); // n default-owanych elementów
            std::vector<int> v(n, 5); // n razy 5
            std::vector<int> v = {1,2,3};
        z zakresu: std::vector<int> v(first, last);

    Rozmiar/pamieć:
        v.size() , v.empty()
        v.capacity(), v.reseve(n) - docelowa ilość elementów
        v.resize(n) - zmienia rozmiar
        v.shrink_to_fit() - ściecie nadmiaru capacity
        Dostęp:
            v[i] - bez sprawdzania
            v.at(i) z wyjątkiem jak nie znajdzie
            v.front()  / back() / data() - wskaźnik do bufora

    Modyfikacje:
        v.push-back(x) | emplace-back(args..) element na miejscu
        v.insert(it, x) | erase(it) | clear
        assign, swap(other)

    Iteracja
        for (auto& x: vector){}
        for (auto it = v.begin(); it != v.end(); it++) {}
        std::ranges - aglorightm od C++20

        any_of() -- se obczaj -filtruje i sprawdza warunek
*/
void show_vector(vector<int> numbers);

void playing_with_vector();

/*
    Mapa:
        asocjacyjny kontener - para klucz wartosc
        dict w pythonie, hashmap w javie 
    Cechy:
    - klucze są unikalne  
    - dane sa posortowane po kluczu - rosnąco domyslnie 
    - złożonowść O(log n)
    - stabilne iteraory
                po zmianie nie zwala iteracji
            - zachowuje kolejnosc kluczy 
    Tworzenie:
        map<typ_klucza, typ_wartosci> nazwa;
            nazwa.insert 
            nazwa[klucz] = wartosc
        
        map<typ_klucza, typ_wartosci> nazwa ={
            {klucz, wartosc}
        }

    Metody:
        map.find()
            -szuka elementu o danym kluczu i zwraca iterator
            jeśli znalazł -> iterator do elementu
            jesli nie - to scores.end()
    
        erase("klucz") 
            usuwa klucz i wartość
        dodawanie:
            mapa[klucz] = wartosc
            mapa.insert({"klucz", "wartosc"});
            mapa.insert(make_pair("klucz", "wartosc"));
        

    Iteracja:
        // first - key | second - value
        C++11
            for (auto& kv: scores) {
                cout << kv.first << " => " << kv.second << endl; 
            }
        c++17
            for (const auto& [name, score]: scores){
                cout << name << " => " << score << endl; 
            }
    
    Różnice miedzy map a unordered_map
        unordered:  (bashowana)
            - nie sortuje kluczy 
            - gorsze zużyciepamieci, losowa kolejnosc
        ma dodatkowe metody:
        count - czy klucz istnieje
        insert_or_assign - wstaw lub nadpisz
        emplace - tworzy element do kopiwoania
        clear / swap empty /size
        try_emplace



*/
void show_map(map<string, int> scores);
void playing_with_map();

/*
    set:
        zbiór unikalnych wartości
            set to po prostu mapa bez wartości
        tylko z unikalnymi kluczami
        trzyma posortowane elementy, bez duplikatów
        set() w pythonie i Jaie TreeSet()
    Dodawanie:
        insert(klucz);
        count - sprawdza istnienie
        find - tak jak zawsze
        lower_bound(x),
            znajdź pierwszy >=x,
        
        upper_bound(x)
            znajdź pierwszy >x
        

*/
void show_set(set<int> scores);
void playing_with_set();