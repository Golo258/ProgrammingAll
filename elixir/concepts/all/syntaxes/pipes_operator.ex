defmodule PipeOperator do
  def parse_string do
    result = "   Example, Content  "
    # remove spaces start/end | uppercase | split into string list
    parsed_result = result |> String.trim() |> String.upcase() |> String.split(" ")
    IO.inspect(parsed_result, label: "Parsed text")
  end

  def list_operation do
    list = [1, 2, 3, 4, 5]

    parsed_list =
      list
      |> Enum.map(fn numb -> numb * 2 end)
      |> Enum.filter(fn numb -> numb > 5 end)
      |> Enum.sum()

    IO.inspect(parsed_list, label: "Parsed list ")
  end

  def file_operation do
    path = "files/static/names_list.txt"

    parsed_file =
      path
      |> File.read!()
      |> String.split("\n")
      |> Enum.filter(fn line -> String.contains?(line, "Elixir") end)
  IO.inspect(parsed_file, label: "Parsed file lines")

  end

end

