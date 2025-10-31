#Protocols
defprotocol Shape do
    @doc """
        Counting_figure_square
    """
    def area(square)
end

defmodule Rectangle do
    defstruct [:width, :height]
end

defimpl Shape, for: Rectangle do
    def area( %Rectangle{width: width, height: height}) do
        width * height
    end
end

defmodule Circle do
    defstruct [:radius]
end

defimpl Shape, for: Circle do
    def area(%Circle{radius: radius}) do
        :math.pi() * radius * radius
    end
end