
defmodule GivenIdNotAvailableException do
    defexception message: "Given id already used"
end
defmodule GivenOptionNotFoundException do
    defexception message: "Given options not match to possible options"
end

defmodule IncorrectIndexException do
    defexception message: "Given list index to large for list length"
end

defmodule NotAppropriateNumberOfPlayers do
  defexception message: "Given length of players list is not appropriate"
end