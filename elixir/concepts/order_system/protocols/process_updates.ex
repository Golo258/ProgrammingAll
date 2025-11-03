
defprotocol Processable do
    @doc """
        Update status of process type
        Returns %Type{...status: change}

      ## Example
        Process.update_status(value)
    """
    def update_status(model, changed_status_value)

    def update_cost(model, changed_cost_value \\ Enum.random(100..1000))
end