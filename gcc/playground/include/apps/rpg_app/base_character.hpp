
// include/apps/rpg_app/i_character
/*
    Base interface for character class
*/
#pragma once
#include <string>
#include <utils/logger.hpp>
#include <utils/variables.hpp>

#define MAX_LEVEL  100
#define MAX_ATTACH_POWER 500

class Character {
    private:
        std::string _nick_name;
        // std::string type; // Klasa potem może enum
        int _level = 1;
        int _health = 100;
        int _attack_power;
        int _defense;
        bool is_death = false;

    public:
        Character() = default;
        Character(
            std::string nick_name,
            int attack_power, 
            int defense
        ):  _nick_name(nick_name),
            _attack_power(attack_power),
            _defense(defense){}

        void set_level(int new_level);
        void set_health(int new_health);
        void set_attack_power(int new_attack_power);
        void set_defense(int new_defense);

        std::string get_nick_name();
        int get_level();
        int get_health();
        int get_attach_power();
        int get_defense();
        
        // virtuals
        // TODO: revise later
        // virtual void attack(Character& target) = 0;
        // virtual void take_damage(int amount)   = 0;
        // virtual void level_up() = 0;
        // virtual void print_stats() const = 0;
        // virtual ~Character() = default;
};