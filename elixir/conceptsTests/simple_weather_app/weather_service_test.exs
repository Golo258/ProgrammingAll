defmodule WeatherServiceTest do
    use ExUnit.Case, async: true
    import Mox

    setup :verify_on_exit!

    test "fetches weather successfully" do
        WeatherClientMock
        |> expect(:get_weather, fn _city -> {:ok, %{temperature: 20}} end)

        Application.put_env(:my_app, :weather_client, WeatherClientMock)

        assert {:ok, %{temperature: 20}} = WeatherService.fetch_weather("city")
    end

    test "handles error in weather fetching" do
        WeatherClientMock
        |> expect(:get_weather, fn _city -> {:error, "Not found"} end)

        Application.put_env(:my_app, :weather_client, WeatherClientMock)

        assert {:error, "Not found"} = WeatherService.fetch_weather("city")
    end
end