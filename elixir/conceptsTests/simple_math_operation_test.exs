
defmodule MathOperation do
    def add(a, b), do: a + b
    def subtract(a, b), do: a - b
end

defmodule ExampleTest do
    use ExUnit.Case
    import MathOperation, only: [add: 2, subtract: 2]

    test "add two numbers" do
        numbers_addition_value = add(1,2)
        assert numbers_addition_value == 3
    end

    test "subtract two numbers" do
        numbers_subtraction_value = subtract(5, 3)
        assert numbers_subtraction_value == 2
    end
end