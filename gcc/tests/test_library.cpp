

#include <third_party/doctest/doctest.h>
#include <dev/leaderboard/include/parse.hpp>

#include <stdexcept>
#include <vector>
#include <string>

namespace u_parser = board::parser;

/*
    Testowanie modudłów
        kompilujemy moduł do biblioteki core
    
    Testy linkujemy z tą biblioteką i
        zaciagamy nagłówki
    Jak podpiąć:
        moduł w modules/*.cpp budują biblioteke core
        Testy to osobny moduł tests/*.cpp
        W pliku testowym includujemy nagłowek danego modułu
            #include <utils/parse.hpp>
            i wołamy funckcje
    Komendy:
        ./build/tests --list-test-cases 
            pokazuje dostępne testcasy
            
        ./build/tests --test-case="nazwa"
            uruchamia pojedynczy kase
            albo samo -tc="nazwa"

        ./build/tests --test-suite="Parser"
            uruchamia całą suite testów

        ./build/tests --order-by=name --success=1
            pokazuje posegregowane testy

    ./build/tests --test-case="Trim single string, BOTH SIDE"


    Budowanie projektu
        # wszystko
        cmake --build build -j

        # tylko lib + testy
        cmake --build build --target core tests -j
        
        # podgląd dostępnych targetów
        cmake --build build --target help

*/
TEST_CASE("Trim single string, BOTH SIDE") {
    // given
    std::string string_to_parse = "  SOME   ";
    // when
    u_parser::trim_string(string_to_parse, u_parser::Trim::BOTH);
    // then 
    CHECK_EQ(string_to_parse, "SOME");
}

/*utils*/
static const char* side_to_string(u_parser::Trim side) {
    switch(side) {
        case u_parser::Trim::LEFT:  return "LEFT";
        case u_parser::Trim::RIGHT: return "RIGHT";
        case u_parser::Trim::BOTH:  return "BOTH";
    }
    return "?";
}
/*
    W jednym TEST_CASE ogarniamy kilka przypadków
        Sposoby:
            1. Tabela przypadków
            -tabela/wektor z przypadkami i lecimy w pętli 
            -każdy wiersz inne wejście i oczekiwany wynik

        Konteksty do debugowania dla doctestu:
            CAPTURE(zmienna ) - pojedyncza zmienna !
            INFO(msg) 
            Pokazuje sie gdy assercia sie nie powiedzie
            CAPTURE zapisuje nazwe i wartosc zmiennej
                cur_input := "wartosc"
            
        
*/
TEST_CASE("Tim string: Testcase table") {
    struct Case {
        std::string input;
        u_parser::Trim side;
        std::string exp_output;
    };
    
    std::vector<Case> cases {
        {"   SOME  ",  u_parser::Trim::BOTH,  "SOME"  },
        {"\tSOME   ",  u_parser::Trim::RIGHT, "\tSOME"},
        {"    SOME",   u_parser::Trim::LEFT,  "SOME"  },
        {"SOME",       u_parser::Trim::LEFT,  "SOME"  },
        {"      ",     u_parser::Trim::BOTH,  ""      },
        {"\n\t X \r",  u_parser::Trim::BOTH,  "X"     },
    };

    for (const auto& t_case: cases) {
        std::string cur_input = t_case.input;
        u_parser::trim_string(cur_input, t_case.side);

        INFO("side= ", side_to_string(t_case.side));
        CAPTURE(t_case.input);
        CAPTURE(t_case.exp_output);
        CAPTURE(cur_input);
        CHECK_EQ(cur_input, t_case.exp_output);
    }
}
/*
    Drugi sposób:
    SUBCASE - każdy wariant w osobny SUBCASE
*/

TEST_CASE("Trim string: SUBCASES") {
    auto check = [](
        std::string input,
        u_parser::Trim side,
        std::string expected
    ) {
        u_parser::trim_string(input, side);
        CHECK_EQ(input, expected);
    };

    SUBCASE("Both side") {
        check("    SOME   ", u_parser::Trim::BOTH,"SOME");
    }
    SUBCASE("left only") {
        check("   SOME",u_parser::Trim::LEFT, "SOME");
    }
    SUBCASE("right only") {
        check("\tSOME  ", u_parser::Trim::RIGHT, "\tSOME");
    }
    SUBCASE("all spaces") {
        check("   ", u_parser::Trim::BOTH, ""); 
    }
}


/*  
    TEST_SUITE
        grupowanie różnych testów logcznie razem
        Każdy test_case bedzie miał prefix nazwy test_suity
        
    Lista suite:
        ./build/tests --list-test-suites

    Uruchamianie
        ./build/tests -ts="Parser" --test-suite
*/
TEST_SUITE("Parser") {

    TEST_CASE("trim both sides") {
        std::string text = "   ABC   ";
        u_parser::trim_string(text, u_parser::Trim::BOTH);
        CHECK_EQ(text, "ABC");
    }

    TEST_CASE("trim left only") {
        std::string text = "   ABC";
        u_parser::trim_string(text, u_parser::Trim::LEFT);
        CHECK_EQ(text, "ABC");
    }

    TEST_CASE("trim right only") {
        std::string text = "ABC   ";
        u_parser::trim_string(text, u_parser::Trim::RIGHT);
        CHECK_EQ(text, "ABC");
    }

}