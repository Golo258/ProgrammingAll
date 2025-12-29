
Etap 1: Komunikacja ze światem (Networking)
    
Nauka komunikacji przez protokół HTTP
Standardowa biblioteka to libcurl
Koncept do zgłębienia:
    działanie "Callback Function" w C/C++?
    libcurl nie zwraca danych po prostu jako std::string.
        On potrzebuje, żebyś podał mu funkcję, którą on będzie wywoływał za
        każdym razem, gdy "doleci" do niego kawałek danych z internetu.

Twoje zadania:
    Jak inicjalizować sesje curl 'curl_easy_init'
    Znajdź, jak ustawić opcję CURLOPT_WRITEFUNCTION,
        aby przekierować strumień danych do Twojej zmiennej (np. std::string).

Spróbuj skompilować program,
    linkując bibliotekę w CMake (szukaj: find_package(CURL) i target_link_libraries).

Sukces:
    Wypisujesz w terminalu surowy tekst (JSON)
    pobrany z adresu: http://api.nbp.pl/api/exchangerates/rates/a/usd/?format=json.
