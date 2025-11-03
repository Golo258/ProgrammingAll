defmodule WeatherService do
  @weather_client Application.get_env(:my_app, :weather_client, WeatherClient)

  @doc """
  Fetches the weather information.
  """
  def fetch_weather(city) do
    case @weather_client.get_weather(city) do
      {:ok, data} -> {:ok, data}
      {:error, reason} -> {:error, reason}
    end
  end
end
