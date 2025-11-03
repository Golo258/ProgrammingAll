defmodule ScheduleUser do
    defstruct [:id, :name, :email]
end

defmodule UserScheduleManager do
    use GenServer
    alias Jason, as: JSON
    @module __MODULE__

    @doc """
        API
    """
    def start_link(file_path) do
        GenServer.start_link(@module, file_path, name: @module)
    end

    def get_user(id) do
        GenServer.call(@module, {:get_user, id})
    end

    def add_user(user_model) do
        GenServer.cast(@module, {:add_user, user_model})
    end

    def update_user(user_id, update_model) do
        GenServer.cast(@module, {:update_user, user_id, update_model})
    end

    @doc """
        Callbacks for requests
    """
    @impl true
    def init(file_path) do
        state = load_users_from_file(file_path)
        {:ok, state}
    end

    @impl true
    def handle_cast({:add_user, user_model}, state) do
        updated_state = Map.put(state, user_model.id, user_model)
        {:noreply, updated_state}
    end

    @impl true
    def handle_cast({:update_user, id, update_model}, state) do
        case Map.get(state, id) do
            nil ->
                IO.puts("User with id #{id} not found")
                {:noreply, state}

            user ->
                updated_user = struct(user, update_model)
                updated_state = Map.put(state, id, updated_user)
                IO.puts("User with id #{id} updated successfully")
                {:noreply, updated_state}
        end
    end

    defp read_file(file_path) do
        expanded_path = Path.expand(file_path)
        IO.puts("Trying to read file from: #{expanded_path}")

        if File.exists?(expanded_path) do
            {:ok, content} = File.read(expanded_path)
            IO.inspect(content, label: "Json file content: ")
            {:ok, content}
        else
            {:error, "Json File doesn't exist"}
        end
    end

    defp decode_json(file_content) do
        case JSON.decode(file_content) do
            {:ok, json_data} -> {:ok, json_data}
            {:error, reason} -> {:error, "Failed to decode JSON file: #{reason}"}
        end
    end

    defp process_users(data) do
        data
        |> Enum.map(fn %{"id" => id, "name" => name, "email" => email} ->
            %ScheduleUser{id: id, name: name, email: email}
        end)
        |> Enum.into(%{}, &{&1.id, &1})
    end

    defp load_users_from_file(file_path) do
        with {:ok, content} <- read_file(file_path),
             {:ok, data} <- decode_json(content) do
            process_users(data)
        else
            {:error, reason} -> IO.puts("Error: #{reason}")
                                %{} # Return an empty map in case of error
        end
    end
end
