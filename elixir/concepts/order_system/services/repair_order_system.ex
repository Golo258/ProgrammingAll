


defmodule Services.RepairOrderSystem do
  @moduledoc """
      Simple system of repair orders for car workshop
      Orders collected in maps, processed  and returned with report
  """

  alias Models.OrderModel
  alias Processable


  def init_example_orders do
    bmw_order = OrderModel.new(1, "Piotr", "BMW")
    audi_order = OrderModel.new(2, "Marcin", "Audi", 1.5)
    ford_order = OrderModel.new(3, "Rafal", "Ford", 5.1, :accepted)
    #      [bmw_order, audi_order, ford_order]
    Agent.start_link(fn -> [bmw_order, audi_order, ford_order] end, name: __MODULE__)
  end

  def get_order_list do
    Agent.get(__MODULE__, & &1)
  end

  def add_order(new_order) do
    Agent.update(__MODULE__, fn order_list -> order_list ++ [new_order] end)
  end

  def process_order_change(order_id, attribute_map_to_change) do
    order_list = get_order_list()

    order_to_process =
      Enum.find(
        order_list,
        fn order -> order.id == order_id end
      )

    if order_to_process do
      updated_order =
        cond do
          Map.has_key?(attribute_map_to_change, :status) ->
            Processable.update_status(order_to_process, attribute_map_to_change[:status])

          Map.has_key?(attribute_map_to_change, :cost) ->
            Processable.update_cost(order_to_process, attribute_map_to_change[:cost])

          true ->
            order_to_process
        end

      index_of_order = Enum.find_index(order_list, fn order -> order.id == order_id end)
      updated_list = List.replace_at(order_list, index_of_order, updated_order)
      Agent.update(__MODULE__, fn _ -> updated_list end)
      true
    else
      IO.puts("Order with id #{order_id} not found")
      false
    end
  end

  def generate_order_report do
    order_list = get_order_list()
    completed_orders = for order <- order_list, order.status == :completed, do: order
    Enum.each(completed_orders, fn order ->
      IO.inspect({order.id, order.client_name, order.cost}, label: "Completed order raport ")
    end)
  end

  def run_system do
    {:ok, _pid} = init_example_orders()
    IO.inspect(get_order_list(), label: "List order after init: ")
    add_order(OrderModel.new(4, "Maciek", "Mazda", 125.0))
    IO.inspect(get_order_list(), label: "List after adding new order: ")
    is_updated = process_order_change(3, %{status: :completed})
    if is_updated do
        IO.inspect(get_order_list(), label: "List after order status update: ")
    else
        IO.puts("Items not updated")
    end
    generate_order_report()
  end
end
