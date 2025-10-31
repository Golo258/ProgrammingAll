defmodule RockPaperScissors.Game do
  alias RockPaperScissors.Player, as: Player
  alias RockPaperScissors.PlayerRegistry, as: GRegistry
  alias NotAppropriateNumberOfPlayers
  @default_number_of_players 6
  @winning_combinations [
    {:rock, :scissors},
    {:scissors, :paper},
    {:paper, :rock}
  ]

  def run_game do
    GRegistry.start_link([])
    init_possible_players()
    for iteration <- 0..5 do
      IO.puts("Round #{iteration} let's start: \n")
      play_round()
    end
    top_player = Enum.max_by(GRegistry.get_players(), fn player -> player.score end)
    IO.inspect(top_player, label: "Winner is: ")
  end

  def get_names_from_file(players_amount) do
    names_file_path = "lib/Static/PlayerNames.txt"
    try do
      File.exists?(names_file_path) ||
        raise File.Error, "File on path #{names_file_path} not exists}"

      names_list = File.read!(names_file_path) |> String.split(["\r\n", "\n"], trim: true)
      init_value = Enum.random(0..(length(names_list) - players_amount))
      players_names_list =
        Enum.slice(
          names_list,
          init_value,
          init_value + players_amount
        )
        |> Enum.shuffle()

      players_names_list
    rescue
      error -> {:error, "An error occurred #{Exception.message(error)} during parsing file"}
    end
  end

  def init_possible_players do
    names = get_names_from_file(@default_number_of_players)
    for numb <- 1..@default_number_of_players do
      GRegistry.add_player(Player.new(numb, Enum.at(names, numb - 1)))
    end

  end

  def add_scores_to_winner(player, enemy) do
    if {player.choice, enemy.choice} in @winning_combinations do
      [%{player | score: player.score + 1}, enemy]
    else
      [player, %{enemy | score: enemy.score + 1}]
    end
  end

  def create_random_pairs(players) do
    mixed_players = Enum.shuffle(players)
    if rem(length(mixed_players), 2) == 0 do
      pairs = Enum.chunk_every(players, 2)
      pairs
    else
      raise NotAppropriateNumberOfPlayers
    end
  end

  def test_player_update do
    players = GRegistry.get_players()
    IO.puts("Players: #{inspect(players)}")
    first_one = Enum.at(players, 1)
    IO.puts("First one : #{inspect(first_one)}")
    GRegistry.update_player(first_one.id, %{choice: :paper, score: 1.2})
    IO.puts("After change: #{inspect(GRegistry.get_players())}")
  end


  def play_round() do
    players = GRegistry.get_players()
    IO.puts("players before round: #{inspect(players)}")
    paired_players = create_random_pairs(GRegistry.get_players())
    changed_pairs =
      Enum.map(paired_players, fn [player, enemy] ->
        add_scores_to_winner(player, enemy)
      end)
    changed_players = List.flatten(changed_pairs) |> Enum.sort_by(fn player -> player.id end)
    change_player_choices(changed_players)
  end

  def change_player_choices(players) do
    for player <- players do
      random_choice = Player.get_random_options_choice(0..2)
      GRegistry.update_player(player.id, %{choice: random_choice, score: player.score})
    end
    IO.puts("Updated_players: #{inspect(GRegistry.get_players())}")
  end


  def get_current_players_id() do
    created_players = GRegistry.get_players()

    if created_players != nil and length(created_players) > 0 do
      players_ids = Enum.map(created_players, fn player -> player.id end)
      players_ids
    else
      []
    end
  end
end
