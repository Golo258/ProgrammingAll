defmodule WeatherClient do
  @callback get_weather(String.t()) :: {:ok, map()} | {:error, String.t()}
end
