
#include "doctest.h"
#include <stdexcept>

// kod startowy, zazwyczaj z biblioteki

int add(int a, int b) {
    return a + b;
}

bool is_even(int x) {
     return x % 2 == 0;
}

double div(double a, double b) {
    if (b == 0.0) throw std::runtime_error("division by zero");
    return a / b;
}

/*
    Pisanie testów:
Podstawowe:
    TEST_CASE("nazwa") { ... } 
        – pojedynczy przypadek testowy
    CHECK(expr) 
        – asercja „miękka” (po błędzie test jedzie dalej)

    REQUIRE(expr) 
        – asercja „twarda” (przerywa dany test-case)

    Porównania:
        - CHECK_EQ(a, b)
        - CHECK_NE
        - CHECK_LT
        - CHECK_GT
        - CHECK_LE
        - CHECK_GE 
    Wyjątki:
        CHECK_THROWS(expr),
        CHECK_THROWS_AS(expr, TypWyjątku)
        CHECK_NOTHROW(expr)

    doctest::Approx(x)
        porównania float/double

*/
TEST_CASE("add: simple addition"){
    CHECK(
        add(2,2) == 4
    );
    CHECK(
        add(-3, 5) == 2
    );
}

TEST_CASE("is_even") {
    CHECK(is_even(2));
    CHECK_FALSE(is_even(3));
}

TEST_CASE("div: deviding and exception ") {
    CHECK(
        div(9.0, 3.0) == doctest::Approx(3.0)
    );
    CHECK_THROWS_AS(
        div(1.0, 0.0), std::runtime_error
    );
}

TEST_CASE("Assertion example") {
    CHECK_EQ(2 + 2, 4);
    REQUIRE(10 > 0);

    double pi = 3.14159;
    CHECK(pi == doctest::Approx(3.1416).epsilon(1e-4));

    CHECK_THROWS_AS(throw std::logic_error("boom"), std::logic_error);
    CHECK_NOTHROW((void)0);
}

// Dane pomocnicze na wydrukach:
TEST_CASE("CAPTURE/INFO demo") {
    int x = 5, y = 7;
    CAPTURE(x);         // pokaże x=5, y=7 przy błędzie
    CAPTURE(y);         // pokaże x=5, y=7 przy błędzie
    INFO("sprawdzam sumę"); 
    CHECK_EQ(x + y, 12);
}

// subcasy - sub testy w ramach jednego
TEST_CASE("Subcase: different variants") {
    int a = 0, b = 0;

    SUBCASE("variant A") { a = 2; b = 2; }
    SUBCASE("variant B") { a = -3; b = 5; }

    CHECK_EQ(add(a, b), a + b);
}

// fibxtury - test z setupem
struct MathFixture {
    int base = 10;
    int mul(int x) const { 
        return base * x;
    }
};

TEST_CASE_FIXTURE(MathFixture, "fixture demo") {
    CHECK_EQ(mul(3), 30);
    CHECK_EQ(mul(-1), -10);
}

/*
    FIltrowanie iuruchamianie testów
    ./tests --test-case="parzystość"
    ./tests --test-suite="MathSuite"
    ./tests --list-test-cases
    ./tests --dt-help
*/