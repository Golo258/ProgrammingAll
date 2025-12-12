package test

import com.lesfurets.jenkins.unit.BasePipelineTest
import com.nokia.scripts.Log as log
import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Test

class knowledgeTest extends BasePipelineTest {

    @BeforeEach
    void setup() {
        super.setUp()
        /*Gdzie szukać skryptów do przetestowania*/
        helper.scriptRoots = [".", "vars", "src/main/com/nokia/scripts"]
        helper.scriptExtension = 'groovy' // jakie pliki testujemy
        /* mockowanie funkcji
            registerAllowedMethod(
                jaka_metoda,
                [jakiTyp_przyjmuje_w_funkcji], np [TypArg1, TypArg2, ...])
                {arg1, arg2, ... ->  } {
                    // closure, która ma się wykonać zamiast prawdziwego kroku
                }
            )
        * */
        helper.registerAllowedMethod(
            "echo", [String]
        ) { echoMessage -> log.debug(echoMessage) }

        helper.registerAllowedMethod(
            "sh", [String]
        ) { cmd -> return 0; }

        helper.registerAllowedMethod(
            "sh", [Map]
        ) { shMap ->
            if (shMap.returnStdout) return "output\n"
            else if (shMap.returnStatus) return 0
            else return null
        }

        helper.registerAllowedMethod(
            "error", [String]
        ) { String message ->
            throw new RuntimeException("Jenkins error cause of: ${message}")
        }

        helper.registerAllowedMethod(
            "stage", [String, Closure]
        ) { name, body ->
            log.info("CALLING STAGE: ${name}")
            body.call()
        }

        helper.registerAllowedMethod(
            "withEnv", [List, Closure]
        ) { List envList, Closure envBody ->
            log.debug("[MOCK WITHENV] Zmienne: ${envList}")
            envBody.call()
        }
        /* Binding - to obiekt kontekstu skryptu
            miejsce gdzie trzymamy zmienne dostepne dla skryptu
                na przykład env albo params
             zmienne które nie są dostępne w lokalnym zakresie
        */ // ustawianie zmiennych
        binding.setVariable("env",
            [PROJECT_VERSION: 3, PATH: "/home/user/artifacts"]
        )
        // odczyt wartości
        String path = binding.getVariable("env")
    }

    @Test
    void should_return_output() {
        // ładujemy skrypt i zwracamy obiekt skryptu z jego metodami
        def step = loadScript("vars/example.groovy")
        // runScript("Jenkinsfile") - ładuje i uruchamia
        step.call()
        /* callStack  - rejestr wywołań kroków i metod
            Jest lista zdarzń wywołania kroków DSL
            w czasie wykonywania skryptu pipelien z vars

            Nie śledzi on przypisań do zmiennych ,an iwywołąń metod
            Rejstruje on wywołania kroków Jenkins Pipeline i zmockowany metod
                - methodName - nazwa kroku
                args - lista argumentó do kroków
                base/object - kontekst
                closure - gdy step przyjmuje closure
            [
              [methodName: "echo", args: ["text"], ...],
              [methodName: "sh", args: [[script: "...", returnStdout: true]], ...]
            ]

        */

        def gitCall = helper
            .callStack
            .find { call ->
                call.methodName == 'sh' &&
                    call.args.first().toString().contains('git status')
            }
        assert gitCall != null: "Script should call git status"

        assert helper
            .callStack
            .findAll { it.methodName == 'withEnv' }.size() == 1

        def buildStage = helper
            .callStack
            .find { call ->
                call.methodName == "stage" && call.args[0] == "build"
            }
        assert buildStage != null: "There is not build stage "
    }
}
