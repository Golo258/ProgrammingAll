package com.nokia.scripts

import com.nokia.scripts.Log as log

import java.util.regex.Matcher

/*
    Operacje na kolekcjach
        - each, eachWithIndex
        - collect (mapowanie)
        - find, findAll (filtrowanie)
        - any, every (warunki logiczne)
        - groupBy, countBy
        - sort, reverse, unique
        - flatten, collectMany
        - inject (reduce)
    Operacje na Stringach:
        - split, readLines
        - trim, replaceAll, replaceFirst
        - tokenize
        - toUpperCase, toLowerCase
        - substring, take, drop
    Regex w Groovim:
        Operatory: =~ (partial match), ==~ (full match)
        Matcher i group()
        replaceAll z regexem
        Kotwice ^, \$, grupy (), klasy znaków [a-z], \\d, \\s
    
    Przydatne skróty i idiomy:
       - *.property (spread operator)
       - ?. (safe navigation)
       - ?: (elvis operator)
       - with, tap
 */

class Knowledge {
    class Collections_Playground {

        Collections_Playground() {};
        /* List management */

        void listsCreations() {
            def automaticInit = [1, 2, 3, 4]
            List<Integer> ints = [51, 56, 25, 67];// typowanie generyczne
            List mixed = [1, "more", 25.67]; // mieszanie typów
            List empty = [];
            // Jawne wybieranie typu listy
            List<Integer> arrayNumbers = new ArrayList<Integer>(
                [1, 12, 516, 733]
            )
            List<String> linkedStrings = new LinkedList<String>(
                ["One", "some", "other"]
            )
            // definiowanie z zakresu
            def rangeList = (1..12).toList()
            def explusiveList = (1..<4).toList()
            def charsRangeList = ('a'..'e').toList();
            // konwersje
            def fromListToSet = [1, 2, 2, 51, 1, 6] as Set
            def fromSetToList = fromListToSet as List
            // z javy
            def javaList = Arrays.asList(1, 2, 51);// stałej długości
            def java9List = List.of(1, 2, 3); //niemutowalna
            log.debug(javaList)
        }

        void listsOperations() {
            log.info("Adding new items to list")
            def baseList = [1, 2];
            baseList << 3 // na koniec
            baseList.add(51);
            baseList += [22, 68]; // konkatenaacja Listy
            log.info("Removing items from list")
            baseList.remove(5); // po indexie
            baseList.remove((Integer) 2) // pierwsze wystapienie liczby 2
            baseList -= [51, 3]; // wystapienia liczb
        }

        void listsAccess() {
            log.info("Acess to list items")
            def base = [10, 20, 30, 40, 50]
            Integer byIndex = base[2];
            Integer lastOne = base[-1];
            List rangeNumbers = base[1..3];
            List choseIndexes = base[1, 5];
            List subList = base.subList(2, 5)
        }

        void listsIteration_Transformation() {
            def numbers = [5, 6, 71];
            numbers.each { //iteracja
                log.info("Numb: ${numbers}")
            }
            /*  jesli nie zwrócisz to zostanie bez zmian wartość
                 zawsze zwróci liste tej samej długości co wykonuje .collect
                tworzy nowa liste
             */
            def mappingNumbers = numbers.collect { numb ->
                log.debug("Numb value before: ${numb}")
                if (numb % 2 == 0) {
                    return numb * 2
                } else {
                    return numb * 3
                };
            }
            log.debug("Mapped numbers: ${mappingNumbers}")
            //filtrowanie - lambda oczekuje true / false
            def filterReturnFirstOne = numbers.find { numb ->
                log.debug("Filtering ${numb}")
                return numb % 2 == 0
            }
            // wszystkie pasujące elementy (lista, może być pusta).
            def allEvens = numbers.findAll { it % 2 == 0 }
            // unique - przechodz iprzez liste i usuwa duplikaty
            def onlyUnique = numbers.unique()
            // bezpieczne wydobycie .getAt
            Integer saveValue = numbers.getAt(2)
            // bezpieczne dołożenie
            numbers.putAt(5, 10); // reszte wypełni nullami

            //1. Iteracja z indexem
            numbers.eachWithIndex { int entry, int index ->
                log.info("Index: ${index} | Entry: ${entry}")
            }
            // 2. Agregacja (reduce / fold)
            def sum = numbers.inject(0) { acc, val ->
                log.debug("Accumulator: ${acc}, Value: ${val}")
                return acc + val
            }
            // 3. Sprawdzanie logiczne
            // any - czy chociaż jeden spełnia warunek
            boolean isAnyOver3 = numbers.any { it > 30 }
            // every - czy wszystkie elementy spełniają warunek
            boolean allPositives = numbers.every { it > 0 }

            // 4. Grupowanie danych - zwraca Mape
            // mapa której klcuzem jest wynik closure a wartością lista elementów
            def groupedByOddEven = numbers.groupBy {
                it % 2 == 0 ? "Parzyste" : "Nieparzyste "
            }
            // Wynik: [Nieparzyste:[5, 33], Parzyste:[12, 18, 40]]

            // 5. Operacje strukturalne
            // flatten - spłaszcza zagnieżdżone listy do jednego poziomu

            // collate - dzieli listę na mniejsze podlisty (chunki)
            def chunks = numbers.collate(2)
            // Wynik: [[5, 12], [18, 33], [40]]

            // sort() - UWAGA: domyślnie mutuje listę!
            // Użyj sort(false), aby zwrócić nową posortowaną listę bez zmiany oryginału.
            def sortedDesc = numbers.sort(false) { a, b -> b <=> a }

            // --- 7. Inne przydatne skróty ---
            def countOver10 = numbers.count { it > 10 } // zlicza pasujące
            String joined = numbers.join(" | ") // łączy elementy w Stringa

            // take / drop - bezpieczniejsze niż subList (nie rzucają błędów przy indeksach)
            def firstTwo = numbers.take(2)
            def withoutFirstTwo = numbers.drop(2)
        }
    }

    void show_collections() {
        Collections_Playground collections = new Collections_Playground();
        /* List management */
        log.info("List management Playground")
        collections.listsCreations();
        collections.listsOperations();
        collections.listsAccess();
        collections.listsIteration_Transformation();
    }

    void stringAndTextOperation() {
/*
    1. Stringi i operacje tekstowe
        '''
            CLOUD_R4BN9_CUS
            CLOUD_R4E12_CUS
        '''.stripIndent().trim()
        Opis:
            stripIndent() usuwa wspólne wcięcia (np. taby/spacje) na początku każdej linii.
            trim() usuwa białe znaki z początku i końca tekstu.
            Idealne do czyszczenia multiline stringów.

    #-----------------------
        def word = "Zażółć gęślą jaźń"
        echo word.toUpperCase()   // "ZAŻÓŁĆ GĘŚLĄ JAŹŃ"
        echo word.toLowerCase()   // "zażółć gęślą jaźń"

        Opis:
            Proste konwersje na duże/małe litery (toUpperCase, toLowerCase).
*/
    }

    void logicAndCondition() {
/*
    #operator trójargumentowy
    def usedToken = (env.SOME == "other") ? "jakis string" : "some diff string"
    Opis:
        Operator trójargumentowy (warunek ? jeśli_true : jeśli_false) — jak w C/Pythonie.

    def value = (phaseState ?: "NO_STATE")
    Opis:
        Operator Elvisa (?:) – jeśli phaseState jest null lub pusty, użyje "NO_STATE".
        To krótsza forma phaseState ? phaseState : "NO_STATE".
*/
    }

    void typeAndIntrospection() {
/*
    println x.getClass()
    println x.getClass().name
    println x.getClass().simpleName
    Opis:
        Wypisuje typ zmiennej (Class, pełna nazwa, uproszczona nazwa).
*/
    }

    void workingWithJson() {
/*
    # czytanie i używanie jsona w groovim
    def tokens = readJSON file: TOKENS_FILE
    echo "GitLab token: ${tokens.gitlab}"
    echo "Jira token: ${tokens['jira']}"
    Opis:
        readJSON w Jenkinsie parsuje JSON z pliku do struktury Groovy (Map / List).
        Możesz się odwoływać przez tokens.key albo tokens['key']
        import groovy.json.JsonOutput
        import groovy.json.JsonSlurperClassic

        def data = [foo: 1, bar: [x: 2, y: 3]]
        def jsonString = JsonOutput.toJson(data)
        def pretty = JsonOutput.prettyPrint(jsonString)
        def parsed = new JsonSlurper().parseText(jsonString
        Opis:
            JsonSlurper().parseText() → zamienia JSON string na Mapę/Listę.
            JsonSlurperClassic.toJson() → obiekt → JSON string.
            prettyPrint() → formatuje JSON czytelnie.

*/
    }

    void collections() {
/*
    #  dict | iteracja po mapie
    tokens.services.each { key, val ->
        echo "Service ${key} -> token=${val}"
    }
    Opis: Iteruje po parach klucz–wartość.

    # iteracja po liście
    parsed.data.items.each { item ->
        echo "Item ${item}"
    }

    # eachWithIndex — iteracja z indexem elementu
    tokens.list.eachWithIndex { item, idx ->
        echo "Element ${idx}: ${item}"
}
*/
    }
    // już jest ale w innym miejscu
    void filteringCOllection() {
/*
    def match = parsed.data.items.find { it.name == "bar" }     // pierwszy znaleziony
    def matches = parsed.data.items.findAll { it.value > 150 }  // wszystkie znalezione
    def names = parsed.data.items.collect { it.name }           // nowa lista z nazwami
    def hasBig = parsed.data.items.any { it.value > 500 }       // czy jakikolwiek spełnia warunek
    Opis:
        .each {}    - iteracja po wszystkich
        .find {}    -	zwraca pierwszy pasujący
        .findAll {} -	zwraca listę pasujących
        .collect {}	- przekształca elementy
        .any {}/.every{}  - sprawdza warunek logiczny
*/
    }

    void conversions() {
/*
    7. Konwersje list/map
    def list = ["A", "B", "C"]
    def map = list.collectEntries { item -> [(item): 1] }

    Opis: collectEntries zamienia listę w mapę.
*/
    }

    void filesOperaions() {
/*
    if (!fileExists("envs")) {
        echo "Brak katalogu envs"
    }

    def files = findFiles(glob: "*.json")
    Opis:
        fileExists(path) - sprawdza istnienie pliku/katalogu.
        findFiles(glob: "*.txt") - zwraca listę plików pasujących do wzorca.
    this.class.getResource(".")
    def dummy = this.class.getResourceAsStream("../resources/dummy_artifacts.json")
    Opis: Używane w testach, by znaleźć zasoby (.json, .txt) w folderach resources.

*/
    }

    void envUsage() {
/*
    10. Używanie zmiennych środowiskowych
    withEnv(["DISPATCHER_VERSION=${env.DISPATCHER_VERSION}"]) {
        def output = sh(
            script: '''
                echo $DISPATCHER_VERSION
            '''
    }
    Opis:
        withEnv([...]) tymczasowo ustawia zmienne środowiskowe w bloku.
        Wewnątrz bloku sh widzi te zmienne

*/
    }

    class RegexMatching {

        void qualificators() {
            /*  1. Kwantyfikatory (Ile razy coś ma wystąpić?)
                +  -> 1 lub więcej (np. \d+ to "przynajmniej jedna cyfra")
                * -> 0 lub więcej (może nie być nic, albo dużo)
                ?  -> 0 lub 1 (opcjonalne, np. colou?r pasuje do color i colour)
                {3} -> dokładnie 3 razy
                {2,5} -> od 2 do 5 razy
            */
            def idCode = "ID-123"
            def noId = "ID-"
            boolean isIdMatching = idCode ==~ /ID-\d+/
            boolean isNoIdMatching = idCode ==~ /ID-\d+/
            log.debug(
                "Test 1 (+): 'ID-123' pasuje do /ID-\\d+/? -> " +
                    isIdMatching
            )
            log.debug(
                "Test 2 (+): 'ID-'    pasuje do /ID-\\d+/? -> " +
                    isNoIdMatching
            )
        }

        void anchors() {
            /*  2. Kotwice (Gdzie szukać?)
               ^   -> Początek linii / stringa
               $   -> Koniec linii / stringa
               Ważne w logach Jenkinsa, żeby nie łapać śmieci ze środka zdania.
            */
            def logLine = "ERROR: Connection failed"
            def midLine = "Warning: ERROR occurred"
            // ^ERROR = musi zaczynać się od ERROR
            boolean startsWithError = logLine ==~ /^ERROR.*/
            boolean containsError = midLine ==~ /^ERROR.*/
            log.debug("Test 3 (^): '${logLine}' zaczyna się od ERROR? -> ${startsWithError}")
            log.debug("Test 4 (^): '${midLine}' zaczyna się od ERROR? -> ${containsError}")
        }

        void sign_classes() {
            /*  3. Klasy znaków (Szybkie skróty)
               \d  -> Cyfra [0-9]
               \w  -> Znak słowny (litera, cyfra, podkreślnik)
               \s  -> Biały znak (spacja, tabulator)
               .   -> Dowolny znak (oprócz nowej linii)
            */
            def date = "2025-12-12"
            // \d{4} = cztery cyfry (rok), \d{2} = dwie cyfry
            boolean isDate = date ==~ /\d{4}-\d{2}-\d{2}/
            log.debug("Test 5 (klasy): '${date}' to format YYYY-MM-DD? -> ${isDate}")

        }

        void greedy_lazy() {
            /*  4. Zachłanność (Greedy vs Lazy) - NAJWAŻNIEJSZE W PARSOWANIU!
               .* -> Greedy (Zachłanny):
                    Zjada ile wlezie, aż do OSTATNIEGO pasującego znaku.
               .*? -> Lazy (Leniwy):
                    Zjada jak najmniej, zatrzymuje się przy PIERWSZYM pasującym.
            */
            def greedyMatcher = (jenkinsLog =~ /\[(.*)\]/)
            def lazyMatcher = (jenkinsLog =~ /\[(.*?)\]/)
            if (greedyMatcher.find() && lazyMatcher.find()) {
                log.debug("Test 6 (Greedy .* ): Wyciągnął -> '${greedyMatcher[0][1]}' (ZA DUŻO!)")
                log.debug("Test 7 (Lazy .*? ): Wyciągnął -> '${lazyMatcher[0][1]}' (IDEALNIE)")
            }

        }

        void flags() {
            /*  5. Flagi (Opcje dodatkowe)
               (?i) -> Ignoruj wielkość liter (Case Insensitive)
            */
            def mix = "eRrOr"
            boolean caseSensitive = mix ==~ /error/
            boolean caseInsensitive = mix ==~ /(?i)error/
            log.debug("Test 8 (bez flagi): '${mix}' == error? -> ${caseSensitive}")
            log.debug("Test 9 (z flagą ?i): '${mix}' == error? -> ${caseInsensitive}")
        }

        void matching() {
            /* Teoria:
               1. ==~ - exact matching - dopasowanie ścisłe
                - zwraca boolean
                - Sprawdza czy cały string pasuje do zorca
                - Jak String.matches()
               2. =~ - find /matcher
                    zwraca obiekt matcher
                szuka wzorca wewnątrz tekst, nie musi pasowac całośc
                wyciaganie danych grup - szukanie fragmentów

               () w regexach - grupy przechwytujące
               jak mamy na przykład tekst SOME_VM-1
               to jeśli chcemy wyciągnąć VM-1
               to robimy /SOME_(VM-\d+)/
               coś jak zmienne według regexie
            Używamy /../ - i można pisać \d normalnie
             */
            // 1. ==~
            def text = "CLOUD_R4BN9_CUS_VM-1"
            if (text ==~ /CLOUD_.*VM-\d+/) {
                log.debug("Text matches")
            } else {
                log.error("Text not matches")
            }
            // 2. =~
            Matcher matcher = (text =~ /CLOUD_(.*)+_CUS_(VM-\d+)/)
            if (matcher) {
                def wholeWord = matcher[0]
                String vmVariant = matcher[0][1] // pierwsza grupa
                String vmVersion = matcher[0][2] // druga grupa
                log.debug("Collected groups from ${wholeWord}:\n" +
                    "1. Variant: ${vmVariant}\n" +
                    "2. Version: ${vmVersion}")
            }
        }
    }

    void hackingJenkins() {
/*
    16. Hakowanie jenkinsa jak chcesz sie dostać do zmiennej z credentaiala
    withCredentials([string(credentialsId: 'IHT_UTE_TOKEN', variable: 'UTE_TOKEN')]){
        debug_issue_only(UTE_TOKEN)
    }
    def debug_issue_only(token){
        sh "echo '${token}' | ssh ute@10-7-UTE4G5SK333.p05.ska-lab.nsn-rdnet.net  'cat > /tmp/to PGW-8: [PDN=8;Dir=DL] Destination unreachable for received SGi packet: 1 packets. Print
    }
*/
    }

    void creatinClasses() {
/*
    Tworzenie, typowanie itd
    generwowanie, konstruktorów, dziedzieczenie itp
*/
    }

    void interfacesAndPolimorhpism() {
/*
    W pliku ShExecutor.groovy masz definicję interfejsu. To jest kontrakt.
    Co to daje: Twój kod (np. NodeRegistry ) nie musi wiedzieć,
    czy łączy się po SSH,
    czy działa lokalnie na Windowsie.
    On wie tylko, że dostanie coś, co ma metodę run().

    Przykład z kodu: Klasa LocalShExecutor i SshShExecutor
    robią zupełnie inne rzeczy pod spodem, ale z zewnątrz wyglądają tak samo.

    Do notatnika:
    Co to jest Interface vs Implementation?
    Dlaczego programujemy "do interfejsu",
    a nie do konkretnej klasy?
    (Hasło: Dependency Injection / Inversion of Control).
*/
    }

    void patternDTO() {
/*
    Plik ShResult.groovy  to klasyczny DTO
    co to jest:
        to pudełko na dane, zamiast zwracać surowy string albo jakąs tablice
        zwracasz elegancki obiekt, który ma dane paramety
        jest niezmienny czyli final
*/
    }

    void resourceManagementInClasses() {
/*
    Zarządzanie zasobami (AutoCloseable i Try-with-resources)
    To jest kluczowe w NodeSessionManager.groovy i SshNodeSession.groovy
    Ssh tworzy otwarte połączenie sieciowe - socket
    jesli go nie zamknimy, to zablkoujemy porty i pamiec
    interface AutoCloseable sprawia że java/groovy sam sprząta po sobie połączenia

    Trzeba zdefinować / nadpisać metode close
    Do zrobienia:
    - Interfejs AutoCloseable w Javie/Groovy.
    - Konstrukcja try-with-resources (np. try (Session s = ...) { }).
    - Blok finally – dlaczego zamykanie zasobów zawsze musi być w bloku finally?
*/
    }

    void securityAndConcurrency() {
/*
    W pliku SshNodeSession.groovy
        synchronized, przy metodach open exec close
    tylko jeden wątek na raz może używać tej metody
    bez tego gdy dwa testy naraz wymierzałyby dane

        AtomicaBoolean - użyte w open
    bezpieczny przełącznik flagi, działa poprawnie nawet przy wielu wyjąkach
    zwykły boolean sobie nie radzi przy wielowątkowości

    ConcurrentHashMap - mapa która przechowuje wątki
        zarzadza nimi i można jednocześnie do niej wrzucać wiele wątków
*/
    }

    void designPatterns() {
/*
    Factory - fabryka, klasa NodeRegistry
        daje nazwe linux-vm, i decyduje którego obiektu użyć i jak go skonfigurować

    Caching/object pool- NodeSessionManager
        sprawdza czy mam już sesje do tego noda
        jeśli tak to daj starą, jak nie to stwóz nową
            -- computeIfAbsent,
        zaoszczdza czas na łączenie sie po Ssh za każdym razem
*/
    }

    void closured() {
/*
NodeSessionManager-- używane Closure<SshNodeSssion>
- fajna funkcjonalnośc grooviego pozwalająca przekazywać kawałek kodu
jako parametr

String interpolation GString -
    różnica pomiedzy tekstem - java String
    a tekstem z ${zmienna} - G string

*/
    }

    void streamy() {
/*
    Jak działają streamy
        InputStream errorStream i inene
*/
    }
}