#include <doctest.h>
#include <stdexcept>
#include <apps/rpg_app/base_character.hpp>

TEST_SUITE("Character Class Check"){
    TEST_CASE("Default constructor"){
        // given
        Character c_default;
        // when
        int base_level = c_default.get_level();
        int base_health = c_default.get_health();
        //then
        CHECK(base_level == 1);
        CHECK(base_health == 100);
    }

    TEST_CASE("Regular Constructor"){
        Character c_regular(
            "Anivia", 15, 15
        );
        
        CHECK_EQ(c_regular.get_nick_name(), "Anivia");
        CHECK_EQ(c_regular.get_level(), 1);
        c_regular.set_health(105);
        c_regular.set_level(2);
        CHECK_EQ(c_regular.get_health(), 105);
        CHECK_EQ(c_regular.get_defense(), 15);
        CHECK_EQ(c_regular.get_level(), 2);
    }
    TEST_CASE("Check parameters beyond thresholds"){
        Character c_regular("Maria", 15, 30);
        CHECK_THROWS_AS(
            c_regular.set_level(112),
            std::invalid_argument
        );
        
        CHECK_THROWS_AS(
            c_regular.set_attack_power(600),
            std::invalid_argument
        );
    }
    TEST_CASE("Check parameters below thresholds "){
        Character c_regular("Maria", 15, 30);
        CHECK_THROWS_AS(
            c_regular.set_level(-12),
            std::invalid_argument
        );
        
        CHECK_THROWS_AS(
            c_regular.set_health(-51),
            std::invalid_argument
        );
    }

}