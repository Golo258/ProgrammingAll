
// modules/apps/rpg_app/base_character.cpp

#include <apps/rpg_app/base_character.hpp>

/* ------------------------- /
    CHARCTER SETTERS
/  ------------------------*/
void Character::set_level(int new_level){
    bool level_below_zero = new_level < 0;
    bool level_beyond_max = new_level > MAX_LEVEL;
    if (level_below_zero){
        throw std::invalid_argument("New level cannot be negative\n");
    }
    if (level_beyond_max){
        throw std::invalid_argument("New level has to be lower than "  + std::to_string(MAX_LEVEL) + "\n");
    }
    _level = new_level;
    logger.info() << "Upgrading " << get_nick_name() 
        << " level with " << new_level << ".\n";  
}
void Character::set_health(int new_health){
    if (new_health < 0) {
        is_death = true;
        throw std::invalid_argument("Cannot set a health to death character\n");
    }
    else{
        _health = new_health;
    }
}
void Character::set_attack_power(int new_attack_power){
    if (new_attack_power > MAX_ATTACH_POWER){
        throw std::invalid_argument("Attach power has to be below " + MAX_ATTACH_POWER + '\n');
    }
    _attack_power = new_attack_power;
    logger.info() << "Setting new power to " << get_nick_name()
        << "with value " << new_attack_power << ".\n";
}
void Character::set_defense(int new_defense){
    _defense = new_defense;
}
/* ------------------------- /
    CHARCTER GETTERS
/  ------------------------*/
/*
    additional requirement 
        if the user is kicked to the name 
        will be replaced by kicked_<nick_name>
*/
std::string Character::get_nick_name(){
    if (!_nick_name.empty() &&
        _nick_name.find_first_of("kicked") != std::string::npos
    ){
        return _nick_name;
    }
    else{
        throw std::invalid_argument("Nick name cannot be empty\n");
    }
}

int Character::get_level()       { return _level;       }
int Character::get_health()      { return _health;      } 
int Character::get_attach_power(){ return _attack_power;}
int Character::get_defense()     { return _defense;     } 