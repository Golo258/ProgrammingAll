package com.nokia.scripts

class ToDoBuildBase {

    // czyli
    void stringAndTextOperation(){
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
    void logicAndCondition(){
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
    void typeAndIntrospection(){
    /*
        println x.getClass()
    println x.getClass().name
    println x.getClass().simpleName
    Opis:
        Wypisuje typ zmiennej (Class, pełna nazwa, uproszczona nazwa).

    */
    }
     void workingWithJson(){
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
     void collections(){
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
     void filteringCOllection(){
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
    void conversions(){
        /*
        7. Konwersje list/map
        def list = ["A", "B", "C"]
        def map = list.collectEntries { item -> [(item): 1] }

        Opis: collectEntries zamienia listę w mapę.
        */
    }

    void filesOperaions(){
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

    void envUsage(){
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

    void regexMatching(){
        /*
         "commonNazwa_123.env" ==~ /commonNazwa_\d+(\.env)?/   // true'
        Opis:
            =~ — dopasowanie częściowe (czy występuje wzorzec).
            ==~ — dopasowanie całego stringa.
            / ... / — notacja regexa.
            | Wzorzec   | Znaczenie            |
            | --------- | -------------------- |
            | `\d`      | cyfra                |
            | `\w`      | litera/cyfra (ASCII) |
            | `\s`      | biały znak           |
            | `.`       | dowolny znak         |
            | `+`       | ≥1 raz               |
            | `*`       | ≥0 razy              |
            | `?`       | 0–1 raz              |
            | `^` / `$` | początek / koniec    |
            | `\b`      | granica słowa        |
            |----------------------------------|'
        */
    }

    void hackingJenkins(){
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

void creatinClasses(){
/*
    Tworzenie, typowanie itd 
    generwowanie, konstruktorów, dziedzieczenie itp
*/
}
// Z twojerzanie commonowego lokalnego ssh
    void interfacesAndPolimorhpism(){
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
   void patternDTO(){
/*
Plik ShResult.groovy  to klasyczny DTO
co to jest:
    to pudełko na dane, zamiast zwracać surowy string albo jakąs tablice
    zwracasz elegancki obiekt, który ma dane paramety
    jest niezmienny czyli final
*/
   }

    void resourceManagementInClasses(){
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

    void securityAndConcurrency(){
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
    void closured(){
    /*
    NodeSessionManager-- używane Closure<SshNodeSssion>
    - fajna funkcjonalnośc grooviego pozwalająca przekazywać kawałek kodu
    jako parametr

    String interpolation GString - 
        różnica pomiedzy tekstem - java String
        a tekstem z ${zmienna} - G string

    */
    }

    void streamy(){
/*
    Jak działają streamy
        InputStream errorStream i inene
*/
    }
}