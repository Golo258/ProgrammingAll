defmodule RockPaperScissors.PlayerRegistry do
  @module __MODULE__
  use Agent
  alias RockPaperScissors.Player, as: Player

  def start_link(init_state) do
    Agent.start_link(fn -> init_state end, name: @module)
  end

  def add_player(%Player{} = new_player) do
    Agent.update(@module, fn players_list_state ->
      players_list_state ++ [new_player]
    end)
  end

  def get_players do
    Agent.get(@module, fn current_players_state -> current_players_state end)
  end

  def update_player(player_id, updates) do
    Agent.update(
      @module,
      fn players_state ->
        Enum.map(players_state, fn
          %Player{id: ^player_id} = player ->
            struct(player, updates)

          other ->
            other
        end)
      end
    )
  end
end
