defmodule Order do
  defstruct [:order_id, :status]
end

defmodule OrderManager do
  def start do
    initial_state = %Order{order_id: 1234, status: "pending"}
    updates_receiver = spawn(fn -> loop(initial_state) end)

    changing_states_processes = [
      accepted_order_process(updates_receiver),
      pending_order_process(updates_receiver),
      complete_order_process(updates_receiver),
      send(updates_receiver, :stop)
    ]

    Enum.each(changing_states_processes, fn process ->
      process
    end)
  end

  defp complete_order_process(receiver_process_id) do
    :timer.sleep(200)
    IO.puts("Order status changed to completed" )
    send(receiver_process_id, {:status, :completed})
  end

  defp accepted_order_process(receiver_process_id) do
    :timer.sleep(200)
    IO.puts("Order status changed to accepted")
    send(receiver_process_id, {:status, :accepted})
  end

  defp pending_order_process(receiver_process_id) do
    :timer.sleep(200)
    IO.puts("Order status changed to pending")
    send(receiver_process_id, {:status, :pending})
  end

  defp loop(state) do
    receive do
      {:status, new_status} ->
        updated_state = %Order{state | status: new_status}
        IO.inspect(updated_state, label: "Change order to: ")
        loop(updated_state)

      :stop ->
        IO.puts("Process stopping. Final state: #{inspect(state)}")

      _other ->
        loop(state)
    end
  end
end

