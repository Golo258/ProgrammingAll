# asynchronous
# spawn/1 - running function in a new process

defmodule SpawnExample do
  def start do
    spawn(fn -> IO.puts("New process is running") end)
  end
end

# spawn/3 - running function in a new process and passing argument to its function
defmodule SpawnWithArg do
  def start do
    spawn(fn -> show_argument(42) end)
  end

  def show_argument(arg) do
    IO.puts("Received: #{arg}")
  end
end

# Asynchronous running example

defmodule RunAsync do
  def run_task do
    task = Task.async(fn -> do_something() end)
    result = Task.await(task)
    IO.puts("Task completed with result: #{result}")
  end

  def do_something do
    :timer.sleep(1000)
    "Its the task"
  end
end

# Communication between tasks - send/2
defmodule Messenger do
  def start do
    pid = spawn(fn -> loop() end)
    send(pid, {:hello, "world"})
    wrong_pattern(pid)
    stop_process(pid)
  end

  def stop_process(process_pid) do
    send(process_pid, :stop)
  end

  def wrong_pattern(process_pid) do
    send(process_pid, :wrong_pattern_send)
  end

  def loop do
    receive do
      {:hello, message} ->
        IO.puts("Received message #{message}")
        loop()

      :stop ->
        IO.puts("Stopped process")

      _other ->
        IO.puts("Unknown message received")
        loop()
    end
  end
end
