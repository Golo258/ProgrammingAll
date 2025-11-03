// =============================
// collections.cpp
// =============================
#include "collections.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "utility"   // std::pair
#include <algorithm> // remove_if
using namespace std;
/*-------------- DEFINITIONS ----------------------*/

/*
    vector<int> numbers;
        dynamiczna tablica
        dodając element - push_back
        sam rezerwuje pamiec, zwieksza capacity
        - capacity - to ile ma pamieci
        - size ile ma realnie elementów w środku
*/

void show_vector(vector<int> numbers)
{
    cout << "Numbers: ";
    for (int index = 0; index < numbers.size(); index++)
    {
        cout << numbers[index] << " ";
    }
    cout << "\tSize: " << numbers.size();
    cout << " Capacity " << numbers.capacity();
    cout << endl;
}
void playing_with_vector()
{

    vector<int> numbers;   // pusty
    numbers.push_back(10); // dodawanie elementów
    numbers.push_back(20);
    numbers.push_back(30);
    int size = numbers.size();
    int capacity = numbers.capacity();
    int first = numbers[0];
    int second = numbers.at(1);
    show_vector(numbers);
    // rezerwowanie pamieci
    vector<int> numbs;
    numbs.reserve(10);
    int flaoting_size = numbs.size();
    numbs.push_back(7);
    numbs.push_back(12);
    numbs.push_back(61);
    int after_adding = numbs.size();
    numbs.resize(10); // uzuepłnie puste elementy 0
    show_vector(numbs);
    // wstawianie /usuwanie
    numbs.insert(numbs.begin() + 2, 51); // wstawia 12 na pozycji 2
    show_vector(numbs);
    numbs.erase(numbs.begin() + 1); // index 3
    show_vector(numbs);
    numbs.clear();
    show_vector(numbs);

    vector<int> nums = {1, 31, 5, 6, 21, 762};
    for (int &nr : nums)
    {
        nr = nr * 13; // zmiana elementu przez referencje
    }
    show_vector(nums);
    /*
        usuń nieparzyste
        remove_if nie w usuwa elementów
        tylko przesuwa pasujące na poczatkek

        erase - przecina wektor na nową długość
    */
    nums.erase(
        remove_if(
            nums.begin(), nums.end(),
            [](int nr)
            {
                return nr % 2 != 0;
            }),
        nums.end());
    cout << "NUms: ";
    show_vector(nums);
}

void show_map(map<string, int> scores)
{
    for (const auto &[name, score] : scores)
    {
        cout << name << " => " << score << endl;
    }
}
void playing_with_map()
{
    map<string, int> scores;
    scores["Ann"] = 12;
    scores["John"] = 51;
    scores["Mike"] = 65;

    // dostep
    int anas = scores["Ann"];
    cout << "Anas: " << anas << endl;

    // czy istnieje
    if (scores.find("John") != scores.end())
    {
        cout << "John exists. Score: " << scores["John"] << endl;
    }

    // iteracja
    // first - key | second - value
    for (auto &kv : scores)
    {
        cout << kv.first << " => " << kv.second << endl;
    }
    scores.erase("Ann");
    cout << "After erasing Ann\n";
    show_map(scores);

    /*
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
    pair<string, int> single_score = {"Bob", 561};
    cout << single_score.first << endl;
    cout << single_score.second << endl;
}

void show_set(set<int> s)
{
    cout << "\nSets: \t";
    for (int x : s)
        cout << x << " ";
}

void playing_with_set()
{
    set<int> s1;                       // empty
    set<int> s2 = {5, 2, 6, 7, 7, 12}; // usunie duplikat
    show_set(s2);
    if (s2.count(6))
    {
        cout << "\n6 is in set\n";
    }
}