defmodule MacroExample do
    defmacro create_function(name) do
        quote do
            def hello(unquote(name)) do
                IO.puts("Welcome #{unquote(name)}")
            end
        end
    end
end

defmodule MacroUse do
    require MacroExample

    MacroExample.create_function(:alice)
    MacroExample.create_function(:bob)
end
