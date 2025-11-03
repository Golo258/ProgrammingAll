defmodule Models.OrderModel do
  @order_status_types [:not_accepted, :accepted, :pending, :in_progress, :completed]

  defstruct [:id, :client_name, :car_model, :cost, :status]

  alias OrderExceptions.StringLengthException, as: LengthException
  alias OrderExceptions.NotAppropriateStatusTypeException, as: StatusTypeException
  alias OrderExceptions.IncorrectTypeException, as: TypeException
  alias OrderExceptions.UndesirableSignsInvolvedException, as: UndesirableSignsException

  def new(id, client_name, car_model, cost \\ 0.0, status \\ :pending) do
    if valid_client_name?(client_name) and valid_status?(status) and valid_order_cost?(cost) do
      %Models.OrderModel{
        id: id,
        client_name: client_name,
        car_model: car_model,
        cost: cost,
        status: status
      }
    else
      nil
    end
  end

  defp valid_client_name?(client_name) do
    if is_binary(client_name) do
      if String.length(client_name) > 3 do
        if Regex.match?(~r/^[a-zA-Z\s]+$/, client_name) do
          true
        else
          raise UndesirableSignsException
        end
      else
        raise LengthException
      end
    end
  end

  defp valid_status?(status) do
    if status in @order_status_types do
      true
    else
      raise StatusTypeException
    end
  end

  defp valid_order_cost?(cost) do
    if is_integer(cost) or is_float(cost) do
      true
    else
      raise TypeException
    end
  end
end
