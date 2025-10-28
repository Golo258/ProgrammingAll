Teoria:
    Typy plików
        .ex - kompilowany do .beam 
            kod źródłowy aplikacji
            szybkie uruchamianie 
            używany do bibliotek funkcji modułów

        .exs - interpetowany 
            do skryptów testów plików temp
            jest wolniejszy bo niekompilowany
            używany do testów migracji, uruchmienia raz

    Importowanie:
        use Something 
            wciaga logike i wykonuje kod z innego modułu
            --czyli automatycznie wywołuje co zostało zdefinowane w __using__
            - i wykonuje ten kod z using

        require Something
            wymusza kompilacje przed użyciem makr
            używać gdy chcesz użyć makr z innego modułu
             -- musza one być znane w czasie kompilacji
        
        import - importuje funckje lub makra do lokalnego scope
            gdy chcesz używać funkcji bez prefiksu modułu

        alias - tworzy skrót do nazwy modułu
            np: alias My.Super.Application.Module, as :MASM

    Zmienne stałe:
        @connection_timeout 500
        log(@connection_timeout)

    Specjalne zmienne:
        __MODULE__ - nazwa aktualnego moduiłu

    Tagi:
        Filtrowanie testów
            @tag :slow
            @tag priority: :high  -- z wartością
            @tag :skip -- pomija testy
            # z powodek
            @tag skip: "needs API access"
        # --only <tag> tylko testy z danym tagiem
        # --exclude <tag> pomija testy z danym tagiem
        # --include <tag> nadpisuje wykluczenie z ExUnit.configure
        # --trace pełniesze logi
        # --max-failures <x> przerywa testy po x błędah
        # --formatter ExUnit.CLIFormatter -- można stworzyć fajny formater z tego
        # --seed 0 - wyłącza randomową kolejność testów
        # --seed 1234 -- ustalona kolejnosc - do otworzenia poprzedniej losowej koilejnosci
  
        @moduletag
            -- dodaje ten sam tag do wszystkich testów w module
        

        @doc -- dokumentacja kodu a nie testów
            dodaje dokumentacje do konkretnej funkcji
            @doc "ta funkcja robi to"
        
        @moduledoc
            dodaje dokumentacje do całego modułu
             @moduledoc """
                Prosty moduł do działań matematycznych.
            """
        
        @spec - określa typ wejścia i wyjścia funkcji
            @spec add(integer(), integer()) :: integer()
            def add(a, b), do: a + b

        @behaviour 
            mówi że moduł musi zaimplemntować określone funkcje -- calbacki
                wymusza interfejs jak w OOP
        @derive
            pozwala automatycznie odziedziczyć funkcjonalności 
                @derive {Jason.Encoder, only: [:id, :name]}
                defstruct [:id, :name, :secret]


#-------------------------------