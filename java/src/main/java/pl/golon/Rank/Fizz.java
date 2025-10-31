package pl.golon.Rank;

public class Fizz {
    public static void main(String[] args) {
        javaSyntaxStandardLib();
    }
    static void javaSyntaxStandardLib() {
        // liczby od 1 do 100, liczby podzielne przez 3 wypisz fizz, dla podzielnych przez 5 buzz
        for (int number = 1; number <= 100; number++) {
            if (number % 3 == 0 && number % 5 == 0) {
                System.out.println("FizzBuzz");
            } else if (number % 5 == 0) {
                System.out.println("Buzz");
            } else if (number % 3 == 0) {
                System.out.println("Fizz");
            } else {
                System.out.println(number);
            }
        }
    }
}
