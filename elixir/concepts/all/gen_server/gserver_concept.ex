
defmodule CustomGenServer do
    use GenServer

    @doc """
    Starts the GenServer with an initial state.
    """
    def start_link(initial_state) do
        GenServer.start_link(__MODULE__, initial_state, name: __MODULE__)
    end

    @doc """
    Sends a synchronous request to get the current state.
    """
    def get_state do
        GenServer.call(__MODULE__, :get_state)
    end

    @doc """
    Sends an asynchronous request to set a new state.
    """
    def set_state(new_state) do
        GenServer.cast(__MODULE__, {:set_state, new_state})
    end

    # Callbacks

    @impl true
    def init(initial_state) do
        {:ok, initial_state}
    end

    @impl true
    def handle_call(:get_state, _from, state) do
        {:reply, state, state}
    end

    @impl true
    def handle_cast({:set_state, new_state}, _state) do
        {:noreply, new_state}
    end

    @impl true
    def handle_info(msg, state) do
        IO.puts("Received info message: #{inspect(msg)}")
        {:noreply, state}
    end
end

defmodule ServerRunner do
    def run do
        {:ok, _pid} = CustomGenServer.start_link(:initial_state)
    end
end
