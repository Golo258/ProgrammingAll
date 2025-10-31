defmodule OrderExceptions.StringLengthException do
    defexception message: "Given string length incorrect"
end

defmodule OrderExceptions.NotAppropriateStatusTypeException do
    defexception message: "Given status type incorrect"
end

defmodule OrderExceptions.IncorrectTypeException do
    defexception message: "Given type of variable is  incorrect"
end
defmodule OrderExceptions.UndesirableSignsInvolvedException do
    defexception message: "Given string contains undesirable signs"
end
