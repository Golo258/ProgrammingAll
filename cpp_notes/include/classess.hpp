// =============================
// classess.hpp
// =============================

/*-------------- IMPORTS ----------------------*/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

/*-------------- DECLARATIONS ----------------------*/

/*
    Klasy:
        domyslnie mają wszystkie pola prywatne private
            w struct - public
        private: - pola widoczne tylko wewnątrz klasy

    Definiowanie klasy:
        class Nazwa{
        };
        pole np int age{0} - domślna wartość atrybutu

    Dog() = default;
        -- domyślny konstruktor
    explicit - zabezpiecza przed niejawnym rzutowaniem
        -- konstruktor x argumentowy
            które zabezpiecza przed niejawną konwersją

    Dog(const Dog& other)=default;
        - konstruktor kopiujący

    Dog& operator=(const Dog&other)
        - operator przypisania

    funkcja const noexcept =
        - funkcja nie zmienia obiektu
        - obiecuje że nie rzuci wyjkątkiem


    static alive:
        - oznacza że należy do klasy, nie do konkretnego obiektu
        - alive(0) -zmiena wspólna dla wszystkich obiektów

    friend - przyjaciel klasy,
        możę dostać sie do pól prywatnych
        operator == - pozwala porównywać obiekty
*/
class Dog {
private:
    std::string _name;
    int _age{0};
    static inline int _alive{0}; // statyczne pole

    bool _validate_age(int age) const; // nie zmienia obiektu

public:
    Dog() = default;                // domyślny
    explicit Dog(std::string name);
    Dog(std::string, int age);
    Dog(const Dog &other) = default;
    Dog &operator=(const Dog &other) = default;
    ~Dog() {
        --_alive;
    }

    // Getters
    const std::string &name() const noexcept {
        return _name;
    }
    int age() const noexcept{
        return _age;
    }
    // Settery
    Dog &set_name(const std::string &new_name);
    Dog &set_age(int new_age);

    // Metody
    void bark() const;
    void birthday();

    // Statyczne
    static int alive_count();

    // przyjaciele
    friend bool operator==(const Dog &a, const Dog &b);
};

/*
    Przykłąd kopmozycji
        jedna klasa zawiera inne obiekty innej klasy

    Kernel add - kopiuje obiekt do wetkora
*/
class Animals {
private:
    std::vector<Dog> _dogs;

public:
    Animals() = default;
    void add(const Dog& new_dog);
    void add(std::string name, int age);

    void list() const;
    bool contains_name(const std::string& name) const;
};

void classes_runner();
/*
    Co to jest this:
    - każda metoda, (funkcja w klasie)
        ma ukryty arumgnet -> wskąźnik do obiektu
        na którym ta metoda działa
    czyli
    class Dog {
        public:
            void bark() {
                std::cout << "woof\n";
            }
    }; kiedy wywołujesz
    Dog rex; rex.bark();
    kopmilator robi:
        Dog::bark(&rex);
        -- wywołuje metode jakby statyczną 
        która należy do klasy
        i przekazuje do niej adres obiektu jako this

    W środku metodY:
        this - ma typ Dog*
        *this ma typ Dog& - czyli sam obiekt

    > wskaźnik na obiekt klasy 
    this->message -- odwołujesz sie do atrybutu obiektu klasy
    this->show - odwołujesz sie do metody klasy 
*/

/*
    Strumienie danych:
        std::ostream
            klasa reprezentujaca dowolny strumień wejściow
                std::cout - konsola
                std::ofstream -plik
                std::ostringstream - bufor stringowy
        Kiedy unfkjca przyjmuje ostream& os 
            że możę pisać dane w dowolne miejsce 
    void greet(std::ostream& os);
        argument, czyli ostream gdzie chcemy wysłać to

    std::ostream& label(std::ostream& os, const char* text);
        przez to że zwracamy sobie ten strumien
            to możemy potem pociągnąc << 

*/
void greet(std::ostream& os);

std::ostream& label(std::ostream& os, const char* text);
/*
    Przez to że mamy zwracany ten 
*/
std::ostream& log_info(std::ostream& os);
