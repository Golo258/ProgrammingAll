
#pragma once
#include <apps/rpg_app/base_character.hpp>
#include <map>
#include <variant>
#include <cstdint>
#include <string>
#include <optional>
#include <array>
#include <type_traits>

/*
    Class for rest of characters
*/
// <name> : <amount_of_damage>
enum class MagicWeapon : uint32_t{
    FIRE  = 200,
    WATER = 50,
    AIR   = 100,
    EARTH = 150
};

enum class ShortDistanceWeapon : uint32_t {
    KNIFE  = 15, 
    DAGGER = 25, 
    SWORD  = 70, 
    KATANA = 110,
    AXE    = 90, 
    HAMMER = 100,
    MACE   = 85, 
    SPEAR  = 60, 
    CLAWS  = 40, 
    FISTS  = 10  
};

enum class LongDistanceWeapon : uint32_t {
    BOW            = 70, 
    CROSSBOW       = 90, 
    SLINGSHOT      = 30, 
    THROWING_KNIFE = 40, 
    JAVELIN        = 80, 
    MUSKET         = 120,
    RIFLE          = 150,
    MAGIC_STAFF    = 180,
    HAND_CANNON    = 200 
};

enum class WeaponType {
    MAGIC,
    SHORT_DISTANCE,
    LONG_DISTANCE,
    NO_WEAPON
};

//  map type of weapon to weapon enum class
using Weapon = std::variant<
    MagicWeapon,
    ShortDistanceWeapon,
    LongDistanceWeapon
>;



inline WeaponType weapon_type_opf(const Weapon& wep){
    return std::visit([](auto e) -> WeaponType {
        using E = std::decay_t<decltype(e)>;
        if constexpr (std::is_same_v<E, MagicWeapon>)
            return WeaponType::MAGIC;
        else if constexpr (std::is_same_v<E, ShortDistanceWeapon>)
            return WeaponType::SHORT_DISTANCE;
        else
            return WeaponType::LONG_DISTANCE;
        }, wep);
}

// Ujednolicone obrażenia:
inline uint32_t damage_of(const Weapon& weapon) {
    return std::visit(
        [](auto e) -> uint32_t {
            using U = std::underlying_type_t<decltype(e)>;
            return static_cast<U>(e);
    }, weapon);
}

template <typename E>
constexpr auto enum_values();

template <>
constexpr auto enum_values<MagicWeapon>() {
    return std::array{ 
        MagicWeapon::FIRE,
        MagicWeapon::WATER,
        MagicWeapon::AIR,
        MagicWeapon::EARTH 
    };
}
template <>
constexpr auto enum_values<ShortDistanceWeapon>() {
    return std::array{ 
        ShortDistanceWeapon::KNIFE,
        ShortDistanceWeapon::DAGGER,
        ShortDistanceWeapon::SWORD,
        ShortDistanceWeapon::KATANA,
        ShortDistanceWeapon::AXE,
        ShortDistanceWeapon::HAMMER,
        ShortDistanceWeapon::MACE,
        ShortDistanceWeapon::SPEAR,
        ShortDistanceWeapon::CLAWS,
        ShortDistanceWeapon::FISTS 
    };
}
template <>
constexpr auto enum_values<LongDistanceWeapon>() {
    return std::array{ 
        LongDistanceWeapon::BOW,
        LongDistanceWeapon::CROSSBOW,
        LongDistanceWeapon::SLINGSHOT,
        LongDistanceWeapon::THROWING_KNIFE,
        LongDistanceWeapon::JAVELIN,
        LongDistanceWeapon::MUSKET,
        LongDistanceWeapon::RIFLE,
        LongDistanceWeapon::MAGIC_STAFF,
        LongDistanceWeapon::HAND_CANNON
    };
}

inline WeaponType deduce_type_from_choice(WeaponType t) { return t; }

// inline auto list_options(WeaponType t) {
//     switch (t) {
//         case WeaponType::MAGIC:          
//             return enum_values<MagicWeapon>();
//         case WeaponType::SHORT_DISTANCE:
//             return enum_values<ShortDistanceWeapon>();
//         case WeaponType::LONG_DISTANCE:
//             return enum_values<LongDistanceWeapon>();
//         default:  
//             return std::array<MagicWeapon,0>{}; // pusta tablica
//     }
// }


// class Warior : public  Character {
//     private:
//         WeaponType weapon;

//     public:
//         Warior() : Character() {} ; // default -> default (base)
// };