pandas jak działa:
    pd.Series - jedna kolumna danych tabeli, wektor- lista z indeksem
        pd.Series([10,20,30], name="age")
            >>> age
                0    10
                1     3
                2     4
                Name: age, dtype: int64
            name = nazwa komulmny, dtype - typ danych 
    dostep do elementów:    
        s[0] = 10 -- po indexie
            
    pd.DataFrame - cała tabela, wiele kolumn Series połączonych razem
        df = pd.DataFrame(
            {"age": [10,20,30], "name": ["One", "Two", "Three"]}
        )
        robienei z Series df:
            s1 = pd.Series([10, 20, 30], name="wiek")
            s2 = pd.Series(["Ala", "Ola", "Ela"], name="imie")
            pd.DataFrame({"age" :s1, "name": s2})
        df.dtypes - typy kolumn 
            age: int64
            name: object
        df.shape - jakie są rozmiary (wierszy, kolumn)
        df.columns - nazwy kolumn

        wybieranie danych
            df["name"] -- cała kolumna -- Series
            df[ ["age", "name"] ] - kilka kolumn 

        filtrowanie danych:
            df[df["age"] > 15]
              -- wybierz dane z kolumny spelniajace dana rzecz
               == "marysia"


        row = {
            "timestamp": "2025-09-08 13:00:00",
            "device1": 34.6,
            "device2": 41.2
        }

        df = pd.DataFrame([row])
        print(df)
        Reprezentacja dicta to klucz = nazwy kolumn wartości do rekordy w kolumnach
        
        |   | timestamp           | device1 | device2 |
        | - | ------------------- | ------- | ------- |
        | 0 | 2025-09-08 13:00:00 | 34.6    | 41.2    |


cus_monitoring:
    ini:
        sefl.metrics = gen_all_metrics() -- all_metrics.json

        self.df = gen_metrics_df() -- 



row_df = pd.DataFrame([row]) -> tworzy jednorzedowy data frame z danych
    |   | timestamp           | device1 | device2 |
    | - | ------------------- | ------- | ------- |
    | 0 | 2025-09-08 13:00:00 | 34.6    | 41.2    |


[m["name"] for m in metrics] - tablica wszystkich wartości metryk

row_df[metric_cols].apply(pd.to_numeric, errors="coerce") -
    apply wywołuje dla każdej kolumn pd.numeric które
        zmienia wartośc na liczbe np 123.0

    row_df[metric_cols].astype("Float64") 
        wymursza dtype pandas żeby można było przyjmować NaN - nulable float 


#----------------debugowanie
# scripts/standalone_debug.py
from types import SimpleNamespace
from pathlib import Path
from taf.ul.cus_monitoring import cus_monitoring


class FakeResult:
    def __init__(self):
        pass
        # self.passed = True
        # self.status = "PASS" 

if __name__ == "__main__":
    out = Path("results_debug")
    out.mkdir(exist_ok=True, parents=True)

    lib = cus_monitoring(str(out))

    data = SimpleNamespace(
        name="ManualDebugTest",
        longname="Suite.ManualDebugTest",
        tags=["debug"],
    )
    result = FakeResult()

    if hasattr(lib, "start_test"):
        lib.start_test(data, result)


    if hasattr(lib, "end_test"):
        lib.end_test(data, result)

    print("Final status:", getattr(result, "status", "n/a"), "passed:", result.passed)
    