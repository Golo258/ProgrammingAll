defmodule Tests.OrderModelTest do
  use ExUnit.Case
  alias Models.OrderModel

  # exceptions
  alias OrderExceptions.StringLengthException
  alias OrderExceptions.UndesirableSignsInvolvedException
  alias OrderExceptions.NotAppropriateStatusTypeException
  alias OrderExceptions.IncorrectTypeException

  test "Check oder model creating with all arguments" do
    order_model = OrderModel.new(12, "John", "Dacia", 125.5, :accepted)
    assert order_model !== nil
    assert order_model.id == 12
    assert order_model.client_name == "John"
    assert order_model.car_model == "Dacia"
    assert order_model.cost == 125.5
    assert order_model.status == :accepted
  end

  test "Check order model client_name field validation" do
    assert_raise StringLengthException, fn ->
      OrderModel.new(12, "", "Dacia", 125.5, :accepted)
    end

    assert_raise UndesirableSignsInvolvedException, fn ->
      OrderModel.new(12, "Mat#123", "Dacia", 125.5, :accepted)
    end
  end

  test "Check order model status and cost fields validation" do
    try do
      OrderModel.new(12, "Tomas", "Dacia", 125.5, :random_status)
    rescue
      error in NotAppropriateStatusTypeException ->
        assert error.message == "Given status type incorrect"
    end

    try do
      OrderModel.new(12, "Tomas", "Dacia", "written_prize", :accepted)
    rescue
      error in IncorrectTypeException ->
        assert error.message == "Given type of variable is  incorrect"
    end
  end
end
