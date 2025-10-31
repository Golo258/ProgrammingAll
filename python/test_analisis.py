

def load_thresholds_json(env_file_path: Union[str, Path]) -> Union[List[DevicesTresholds], DevicesTresholds]:
    """
    Load thresholds JSON from file path
    Expected JSON structure:
    {
        "threshold_type" : // OVERALL_METRICS | PROCESSES_METRICS
        {
            "device_name" : {
                "mean" : 12.5, // float value
                "max : 51.5 // float value
            }, ... // next devices
        }
    }
    :param env_file_path: Path to a JSON file with test thresholds ovverides
    :return: Parsed dict (possible empty if file is empty or invalid)
    :raises FileNotFoundError: if the file path doesn't exist or isn't a file.
    """
    file_path = Path(env_file_path)
    if not file_path.is_file():
        raise FileNotFoundError(f"Thresholds env file does not exist: {file_path}")

    try:
        with file_path.open("r", encoding="utf-8") as json_file:
            thresholds_data = json.load(json_file)
    except json.JSONDecodeError as e:
        LoggerManager.log_msg(
            f"Failed to parse JSON content in {file_path}: {e}",
            to_console=True
        )
        return {}

    if not isinstance(thresholds_data, (dict, list)):
        LoggerManager.log_msg(
            f"Expected top-level JSON object in {file_path}, got {type(thresholds_data)}. Using empty.",
            to_console=True,
        )
        return {}

    return thresholds_data


Dobra testujemy tego skurwysyna:
1.  Co ta funkcja dokładnie robi w jednym zdaniu?
    na podstawie podanego pliku env_file_path
        sprawdza plik, wczytuje zniefgo dane i sprawdza typ otrzymanego obiektu z wcztanego pliku

2. Wejścia i wyjścia:
    na poczatku dostajemy na wejściu albo stringa albo Path
        czyli ścieżke do pliku
            sprawdzenie czy jak podamy inny typ to wtedy nam rzuci coś
            sprawdzenie jak podamy poprawny jeden z typów 
            oba jak zareaguja na jeden i na drugi
    
    na wyjściu dostajemy:
    Przypadki:
        gdy pliknie nie istnieje 
            wyjątek FileNotFoundError z messagem
        gdy istnieje:
            gdy w środku jest:
                nie poprawny json:
                    to wiadomośc że nie można zdekodować jsona
                    i zwracmy {} - pusty słownik
                poprawny json:
                    sprawdzamy czy jest odpowiedniego typu
                    jesli tak to zwracamy ten obiekt 
                    w innym przypadku
                        wiadomośc i {}
        
    Co dotyka świata i trzeba podmienić w testach:
        Logger, trzeba znowu go zapezpieczyć i zebrać odpowiednie wiadomości
        Sam pliczek: i jego zawartośc żeby przetestować różne scenariusze:
            Pliczek nie istnieje
            PLiczek istnieje:
                - jest na przykłąd pusty // można dać zabezpieczenie
                - jest nie odpowiedni json
                - czy obiekt zaladowany jest albo dictem albo lista
                - i też że nie jest, ale w sumie chyba, to jest niemożliwe
                    bo wtedy nam nie sparsuje go, ale to do przemyślenia
        
    Unit testy:
        Po kolei sprawdzamy ewentualnośici te co wypisałem
    BUildIn nie musimy maskować bo go nie używamy 
    
        
        