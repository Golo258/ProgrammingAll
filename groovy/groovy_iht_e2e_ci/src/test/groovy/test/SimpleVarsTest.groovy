package test

import com.lesfurets.jenkins.unit.BasePipelineTest
import org.junit.jupiter.api.BeforeEach
import org.junit.jupiter.api.Test

import static org.junit.jupiter.api.Assertions.assertFalse
import static org.junit.jupiter.api.Assertions.assertTrue

class SimpleVarsTest extends BasePipelineTest {

    @BeforeEach
    void setup() {
        super.setUp()

        helper.registerAllowedMethod("echo", [String]) { msg ->
            // możesz logować albo zbierać do asercji
        }
        helper.registerAllowedMethod("sh", [String]) { cmd ->
            return 0
        }

        binding.setVariable('env', [:])
        def myStep = loadScript("vars/example.groovy")
        binding.setVariable('myStep', myStep)
    }

    @Test
    void runs_step() {
        def myStep = loadScript("vars/example.groovy")
        myStep.call([foo: "bar"])

        def shCalls = helper
            .callStack
            .findAll { it.methodName == "sh" }
        assertFalse(shCalls.isEmpty(), "Expected 'sh' to be called")

        def echoCalls = helper
            .callStack
            .findAll { it.methodName == "echo" }
        assertTrue(
            echoCalls.any {
                it.args[0].contains("Hello from myStep!")
            }
        )
    }
}
