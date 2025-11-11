Projekt: RPG Character Builder

Celem jest stworzenie prostego systemu postaci RPG (tekstowego, bez grafiki) z klasami reprezentującymi różne typy bohaterów, ich statystyki, ataki i rozwój.


Cel projektu

    Napisz system pozwalający:
        Tworzyć różne typy postaci 
            (np. Wojownik, Mag, Łucznik)
        Atakować inne postacie i zadawać obrażenia
        Ulepszać postacie (level up, regeneracja)
        Przechowywać i wypisywać ich statystyki w czytelny sposób


Struktura klas:
    Klasa bazowa Character
        To będzie abstrakcyjna klasa (interfejs ogólny) dla wszystkich postaci.
            Właściwości (protected lub private + gettery):
                - std::string name
                - int level
                - int health
                - int attackPower
                - int defense

        Metody wirtualne:
            void attack(Character& target) 
                – wykonuje atak (różnie implementowany w podklasach)
            void takeDamage(int amount) 
                – zmniejsza HP po otrzymaniu obrażeń
            void levelUp() 
                – zwiększa level i statystyki
            virtual void printStats() const 
                – wypisuje statystyki postaci
            virtual ~Character() 
                – destruktor wirtualny obowiązkowo

⚔️ Etap 2 – Klasy pochodne
    🛡️ Warrior
    Silny, wysoki atak, niska mana (jeśli dodasz w przyszłości)
    attack() może zadawać więcej obrażeń, ale czasem pudłować (np. 80% szansy na trafienie)
    levelUp() zwiększa głównie attackPower i defense

🔮 Mage
    Słaby fizycznie, ale potężne czary
    Możesz dodać dodatkowe pole mana
    attack() zadaje obrażenia zależne od mana (np. czar zużywa manę)
    levelUp() zwiększa mana i attackPower, ale mniej health

🏹 Archer
    Zrównoważony, szybki
    Możesz dodać np. accuracy jako procent trafienia
    attack() bazuje na szansie trafienia (np. 90%) i zadanych obrażeniach
    levelUp() zwiększa precyzję i atak

🧩 Etap 3 – Interakcje między postaciami
    Zrób prostą funkcję / klasę, np. BattleSimulator, która:
    Przyjmuje dwie postacie (Character& a, Character& b)
    W pętli wykonuje rundy ataków aż jedna z nich zginie (health <= 0)
    Wypisuje raport: kto kogo atakuje, ile obrażeń, kto wygrał

⚠️ Etap 4 – Obsługa błędów
    Gdy próbujesz zaatakować postać martwą — rzuć wyjątek (std::runtime_error("Target is already dead!"))
    Gdy attackPower <= 0 — rzuć logic_error
    Gdy mana się skończy — runtime_error("Not enough mana!")

📋 Etap 5 – Dodatkowe funkcje
    Jak już zrobisz core, możesz dodać:
    enum class CharacterType { Warrior, Mage, Archer };
    Fabrykę: std::unique_ptr<Character> createCharacter(CharacterType, std::string name);
    Testy doctest do funkcji attack, levelUp, takeDamage
    Zapisywanie postaci do pliku (save_to_file() / load_from_file())

🧠 Koncepcje, które tu przećwiczysz
    ✅ Dziedziczenie
    ✅ Wirtualne metody i polimorfizm
    ✅ Konstruktory i inicjalizacja pól
    ✅ Zasady enkapsulacji
    ✅ Obsługa wyjątków
    ✅ Smart pointers (unique_ptr, shared_ptr)
    ✅ Testowanie logiki (doctest lub inny framework)


🧩 Bonus (dla chętnych na Level 2)
    Jak już działa walka i leveling:
        dodaj Inventory z klasami Item, Weapon, Potion
        dodaj equip() i useItem()
        dodaj BattleArena – walka wielu postaci (np. 3v3)
        dodaj serialize() – zapis i odczyt postaci do JSON (np. z nlohmann::json)

🧭 Sugerowany plan działania
    Stwórz klasę Character i trzy pochodne
    Zaimplementuj logikę ataku i otrzymywania obrażeń
    Dodaj levelUp()
    Stwórz prosty symulator walki (main.cpp lub osobna klasa)
    Dodaj wyjątki
    Zrób testy dla kilku funkcji
    Rozbuduj o własne pomysły (np. inventory, mana, losowość)