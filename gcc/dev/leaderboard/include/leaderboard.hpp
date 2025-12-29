
// leaderboard/include/leadersboard.hpp

#pragma once
#include <iostream>
#include <optional>
#include <unordered_map>
#include <map>
#include <vector>
#include "utility" // std::pair
#include <variables.hpp>
#include <parse.hpp>
#include <numeric> // acumulate

class Leaderboard {

    public:
        /* Dodaje nowego albo aktualizuje istniejącego użytkownika  - sumuje wyniki*/
        void add_or_update(std::string name, int delta);

        /*Ustawia wynik na sztywno  -- nadpisuje aktualny */
        void set_score(std::string name, int score);
        
        /*Zwraca wynik gracza; jeśli nie istnieje -> std::nullopt*/
        std::optional<int> score_of(const std::string& name) const;

        /*Usuwa graczy poniżej danego progu; zwraa ile usunieto */
        std::size_t remove_below(int threshold);
        
        /*  zwraca @amount graczy posortowanych malejaco po wyniku
            remis: alfabetycznie po nazwie
        */
        std::vector<std::pair<std::string, int>> top(std::size_t  amount) const;
        
        // oblicza i zwraca srednia i mediane (dla pustej tablicy std::nullopt)
        std::optional<double> average() const;
        std::optional<double> mediana() const;

        /* Iteracja - read-only po wszytstkich parach do range for   */
        using container_t = std::unordered_map<
            std::string, int
        >;
        
        inline container_t::const_iterator begin() const noexcept{
            return _data.begin();
        }
        inline container_t::const_iterator end() const noexcept{
            return _data.end();
        }

        //  wypisanie w formacie 1) Alice 4\n2) Bob 7\n...
        void print(std::ostream& os, std::size_t best_players_nr) const;
    
    private:
        container_t _data;
};