defmodule Concepts.ElixirSyntax do
  @moduledoc """
  Explaining Elixir Syntax Concepts
   Proper module name: Katalog.ModuleName
  """
  # Tworzenie modułów:
  defmodule SimpleModule do
    @doc """
        Creating function with normal and default parameters (\\)
    """
    def present_args(text, number \\ 12) do
      IO.puts(text)
      do_private_thing()
      value = number
      # return this value
      value
      Enum.
    end

    @doc """
        Arits its a number of arguments
      Functions can have the same name but with diffrenet amount of args
    """
    def present_args(text, numb, atom) do
      args = [text, numb, atom]
      IO.inspect(args, label: "List of args: ")
    end

    # Private function which can be used only in inner module
    defp do_private_thing() do
      IO.puts("its a simple private function")
    end

    def pattern_matching() do
      simple_assign = 120
      {one, two, three} = {1, 2, 3}
      {_, middle, _} = {3, 5, 7}
      [head | rest] = [:head, 12, 5, 5.6]

      IO.inspect([simple_assign, one, two, three, middle, head, rest],
        label: "All pattern matching "
      )
    end

    def conditional_construction do
      x = 12
      # simple if statement
      if x > 12 do
        IO.puts("#{x} is }bigger than 12")
      end

      unless x > 5 do
        x = x * x
        IO.puts("Multiplying #{x}")
      end

      # many pattenrs
      case x do
        1 -> IO.puts("Its #{x}")
        5 -> IO.puts("Its 5")
        _ -> IO.puts("not match any case")
      end

      # many condition
      cond do
        x == 1 -> IO.inspect(x)
        x == 10 -> IO.inspect(10)
        true -> IO.puts("Default")
      end
    end

    @doc """
        Anonymous funs in practise
    """
    def lambdas_func do
      add = fn prev, next -> prev + next end
      divide = &(&1 / &2)
      _result_add = add.(2, 3)
      _result_divide = divide.(25, 5)
    end

    @doc """
        Use of pipes
      Passing result to next function of argument
    From left to right
    """
    def pipes_usage do
      numbs = [12, 2, 3, 4, 5]

      piped_list =
        numbs
        |> Enum.map(fn num -> num + 1 end)
        |> Enum.filter(fn num -> num > 2 end)
        |> Enum.sort()

      IO.inspect(piped_list, label: "Piped list: ")

      # text loading
      text = "   Hello World!   Elixir is great!   "

      converted_text =
        text
        |> String.trim()
        |> String.downcase()
        |> String.split()
        |> Enum.filter(fn word -> String.length(word) > 5 end)

      IO.inspect(converted_text, label: "Seperated words:  ")
    end

    defmodule Comprehensions do
      #  creating, filtering, and processing elements in collection
      # syntax for element <- collection, do: expression
      def simple_squares() do
        squares = for numb <- 1..5, do: numb * numb
        IO.inspect(squares, label: "Squares by comprehensions: ")
      end

      def all_pairs do
        positives = Enum.to_list(1..5)
        negatives = Enum.to_list(-5..-1)
        list_combination = for pos <- positives, neg <- negatives, do: {pos, neg}
        IO.inspect(list_combination, label: "List combinations : ")
      end

      def map_comprehension do
        simple_map = %{
          "a" => 1,
          "b" => 2,
          "c" => 3
        }

        doubled_values = for {key, value} <- simple_map, do: {key <> Integer.to_string(value), value + 2}
        IO.inspect(doubled_values, label: "List combinations : ")
      end

      def with_filters do
        filtered_squares =
          for numb <- 1..20,
              rem(numb, 2) == 0, numb * numb < 100,
              do: numb * numb
        IO.inspect(filtered_squares, label: "Filtered numbers : ")

      end
    end

    def execute_comprehensions do
        Comprehensions.simple_squares()
        Comprehensions.all_pairs()
        Comprehensions.map_comprehension()
        Comprehensions.with_filters()
    end
  end
end
