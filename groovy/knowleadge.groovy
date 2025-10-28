
#--------------------------------------------
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

#--------------------------------------------
2. Operatory logiczne i warunkowe

    #operator trójargumentowy 
    def usedToken = (env.SOME == "other") ? "jakis string" : "some diff string"
    Opis:
        Operator trójargumentowy (warunek ? jeśli_true : jeśli_false) — jak w C/Pythonie.

    def value = (phaseState ?: "NO_STATE")
    Opis:
        Operator Elvisa (?:) – jeśli phaseState jest null lub pusty, użyje "NO_STATE".
        To krótsza forma phaseState ? phaseState : "NO_STATE".

#--------------------------------------------
3. Typy i introspekcja
    println x.getClass()
    println x.getClass().name
    println x.getClass().simpleName
    Opis:
        Wypisuje typ zmiennej (Class, pełna nazwa, uproszczona nazwa).

#--------------------------------------------
4. Praca z JSON
    # czytanie i używanie jsona w groovim
    def tokens = readJSON file: TOKENS_FILE
    echo "GitLab token: ${tokens.gitlab}"
    echo "Jira token: ${tokens['jira']}" 
    Opis:
        readJSON w Jenkinsie parsuje JSON z pliku do struktury Groovy (Map / List).
        Możesz się odwoływać przez tokens.key albo tokens['key']


#-------------------------
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

#--------------------------------------------
5. Iteracje po kolekcjach
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
#--------------------------------------------
6. Filtrowanie list/map

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

#--------------------------------------------
7. Konwersje list/map
    def list = ["A", "B", "C"]
    def map = list.collectEntries { item -> [(item): 1] }

    Opis: collectEntries zamienia listę w mapę.

#--------------------------------------------
8. Sprawdzanie warunków
    if (tokens.gitlab) {
        echo "GitLab token istnieje"
    }
    if (tokens.services.containsKey("api2")) {
        echo "Mam token do api2: ${tokens.services.api2}"
    }
    Opis: Groovy interpretuje null i puste struktury jako false.


#--------------------------------------------
9. Operacje na plikach
    if (!fileExists("envs")) {
        echo "Brak katalogu envs"
    }

    def files = findFiles(glob: "*.json")
    Opis:
        fileExists(path) - sprawdza istnienie pliku/katalogu.
        findFiles(glob: "*.txt") - zwraca listę plików pasujących do wzorca.

#--------------------------------------------
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

#--------------------------------------------
11. Regex w Groovy
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
#--------------------------------------------
12. Testowanie I Jenkins Unit Pipeline
    class MyPipelineTest extends BasePipelineTest {
        void setUp() {
            super.setUp()
            binding.env.WORKSPACE = "/tmp"
            helper.registerAllowedMethod('echo', [String]) { msg -> println msg }
        }
    }
    Opis:
        BasePipelineTest - baza testów z biblioteki jenkins-pipeline-unit.
        binding - symuluje środowisko Jenkins (env, params, currentBuild itp.).
        helper - rejestruje mocki i śledzi wywołania (helper.callStack).
    #--------------------------------------------
    BasePipelineTest:
        setUp() - przygotowanie testu
            Binding - zmienne i kroki pipelinu
            helper - PipelineTestHelper  callstackiem

        binding - tu mamy standardowe rzeczy jenkinsa:
            env - mapa zmiennych środowiskowych
            params - parametry joba
            currentBuild, scm itp
            można je mockować i ustawiać 
            np: binding.env.WORSKSPACE = "/tmp/"

       loadScript("vars/") - ładuje shared libs z vars albo dowolny skrypt 

        helper.CallStack - pełny stack wszystkich kroków 
            (method name += args)

    #--------------------------------------------
    Mockowanie stepów i funkcji:
        helper.registeralowedMethod(name, argsTypes, impl) - podstawowe narzedzie do moków
        np:
            helper.registerAllowedMethod('sh', [String], { cmd -> 
                if (cmd.contains('git rev-parse')) 
                    return 'abcdef'
                else
                    return 0
            })
        
        Bloki/wrappers (withCredentials, timestamps, ansiColor, stage, timeout):
            zwykle rejestrujesz wersję z Closure i po prostu wołasz body():
            np: helper.registerAllowedMethod('withCredentials', [List, Closure]) { _, body -> body() }

    #--------------------------------------------
    Asercje na wywołaniach:
        assertTrue(helper.callStack.any { it.methodName == 'echo' && it.args[0].toString().contains('Hello') })

    #--------------------------------------------
    Testowanie Shared Libraries (Global Libraries):
        Jeśli Twój kod woła inne kroki z biblioteki (np. @Library('my-lib') _ albo library 'my-lib'), możesz zarejestrować wirtualną bibliotekę:
        import com.lesfurets.jenkins.unit.global.lib.*

        def lib = library()
        .name('my-lib')
        .defaultVersion('main')
        .allowOverride(true)
        .retriever(localSource('path/do/twojej/libki'))   // lub scmSource(...)
        .targetPath('libs')                                // gdzie ma być załadowana
        .build()

#----------------------------
13. Diagnostyka i ścieżki
    this.class.getResource(".")
    def dummy = this.class.getResourceAsStream("../resources/dummy_artifacts.json")
    Opis: Używane w testach, by znaleźć zasoby (.json, .txt) w folderach resources.

14. Ubijanie jobów na Jenkinsie
    def q = Jenkins.instance.queue
    q.items.findAll.each { q.cancel(it.task) }

15. Sprawdzanie zmienynch środwiskowych jenkins
env.getEnvironment().each { k, v ->
    println "${k} = ${v}"
}

16. Hakowanie jenkinsa jak chcesz sie dostać do zmiennej z credentaiala
    withCredentials([string(credentialsId: 'IHT_UTE_TOKEN', variable: 'UTE_TOKEN')]){
        debug_issue_only(UTE_TOKEN)
    }
    def debug_issue_only(token){
        sh "echo '${token}' | ssh ute@10-7-UTE4G5SK333.p05.ska-lab.nsn-rdnet.net  'cat > /tmp/to PGW-8: [PDN=8;Dir=DL] Destination unreachable for received SGi packet: 1 packets. Print
    }
