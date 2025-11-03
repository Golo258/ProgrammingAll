defimpl Processable, for: Models.OrderModel do
    def update_status(%Models.OrderModel{} = order, changed_status_value) do
        %Models.OrderModel{order | status: changed_status_value}
    end

    def update_cost(%Models.OrderModel{} = order, changed_cost_value) do
        %Models.OrderModel{order | cost: changed_cost_value}
    end
end