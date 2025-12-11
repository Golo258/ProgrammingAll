package test

import org.junit.jupiter.api.Test

import static org.junit.jupiter.api.Assertions.assertEquals

class SimpleGroovyTest {
    @Test
    void adds_two_numbers() {
        def sum = 2 + 3
        assertEquals(5, sum)
    }
}
