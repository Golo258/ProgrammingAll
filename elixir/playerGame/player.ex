defmodule RockPaperScissors.Player do
  @game_options [:rock, :paper, :scissors]
  alias RockPaperScissors.Game, as: Game
  alias GivenIdNotAvailableException
  alias GivenOptionNotFoundException
  alias IncorrectIndexException

  defstruct [:id, :name, :choice, :score]

  def new(id, name, choice \\ nil, score \\ 0) do
    option = choice || get_random_options_choice(0..2)

    if validate_player_id?(id) and validate_player_choice?(option) do
      %RockPaperScissors.Player{
        id: id,
        name: name,
        choice: option,
        score: score
      }
    end
  end

  defp validate_player_id?(current_player_id) do
    player_ids = Game.get_current_players_id()

    if current_player_id not in player_ids do
      true
    else
      raise GivenIdNotAvailableException
    end
  end

  defp validate_player_choice?(player_choice) do
    if player_choice in @game_options, do: true, else: raise(GivenOptionNotFoundException)
  end

  defimpl Inspect do
    def inspect(%RockPaperScissors.Player{id: id, name: name, choice: choice, score: score}, _opts) do
      "Player(#{id} | #{name} | #{choice} | #{score})"
    end
  end

  def get_random_options_choice(threshold) do
    random_number = Enum.random(threshold)
    if random_number < length(@game_options) do
      Enum.at(@game_options, random_number)
    else
      raise IncorrectIndexException
    end
  end
end
