

# zakładamy
# mamy moduł verification.py

def get_robot_variable(name: str) -> Optional[str]:
    try:
        value = BuiltIn().get_variable_value(name)
        return value if value not in (None, "") else None
    except Exception:
        LoggerManager.log_msg(f"Variable {name} not set in test", lvl="WARNING", to_console=True)
        return None

"""
    Unit testy sprawdzają pojedyncze funkcji
        małe kawałki logiki w izolacji
        bez odpalania wszystkich modułów 
        
    Integracyjne sprawdzają wiekszy przpływ razem
    1.Najpierw bierzemy pod lupe jakąs funkcje:
        Tu mamy get_robot_variable(name).

    2) Zależności SUT
        BuiltIn().get_variable_value(name) – zewnętrzny świat (Robot).
        LoggerManager.log_msg(...) – efekt uboczny
        Podmieniamy je
    
    3) Kontrakt funkcji (specyfikacja)
        - zwraca pusta wartosc, ta sama wartosc
        - pusta - None
        = wyjatek z- log warning / none
        zmienna nie isnieje /.none
        itd
    4) Sterowalne “szwy”
        Podmieniamy verification.BuiltIn na prosty FakeBuiltIn.
        Podmieniamy verification.LoggerManager.log_msg na funkcję-szpiega.

Gdy będziesz testować listener (wątek, zapisy CSV/HTML, eval progów), zrób to świadomie i lekko:
    Wyeliminuj IO i zewnętrzności:
        get_dev_conns, check_dev_conns, gather_metrics_row → podmień na fakes, które zwrócą kontrolowane dane (np. stały wiersz z metrykami).
        create_fig i eval_and_disp → podmień na “no-op” (żeby nie generowały plików/HTML).
        close_dev_conns → no-op.

    Przyspiesz pętlę:
        monkeypatch interval = 0 (lub 0.01) po utworzeniu listenera.
    Ustaw tymczasowy katalog:
        tmp_path jako output_dir, żeby CSV/HTML lądowały w sandboxie.
    Zatrzymanie kontrolowane:
        uruchom, poczekaj chwilę (krótko), stop_listener(), potem asercje:
            pliki CSV istnieją,
            w CSV są kolumny/metki jak trzeba,
            zawołało się eval_and_disp z właściwą nazwą zestawu (“OVERALL_METRICS”, “PROCESSES_METRICS”).

    To będą osobne testy integracyjne (mniej liczne), nie mieszaj tego do unitów get_robot_variable.
    Nazwij SUT (1 funkcja).

- Wypisz przypadki użycia (wejścia/wyjścia + błędy).
- Narysuj zależności (co trzeba podmienić).
- Zacznij od happy path (najprostszy test).
- Dodaj “puste/weird” dane (parametrize).
- Dodaj obsługę błędu (wyjątek + log).

"""
"""

    Plan:
        Krok 0: myślenie testerskie: co to ma robić?
            Spisanie zachowania (to jest specyfikacja, nie kod)
    1. gdy zmienna istnieje i ma niepusta wartośc, zwracamy ją
    2. gdy isnieje, ale jest pusta "" albo None, zwracamy None
    3. Gdy BuildIn().get_variable_value, rzuci wyjątek
        zaloguj WARNING i zwróć None
    4. Gdy zmienna nie istnieje, zwrócimy None
        5. Edge case - co gdy wartośc to nie string
        
"""

"""
    Krok 1: setup 
        Importowanie modułów, nie samej funkcji
        Dzieki temu podmieniamy w nim BuildIn / LoggerManger
"""
import pytest
import moduł.verification as verification

"""
    Krok 2: pierwszy test: positive case
        Gdy są jakieś zewnętrzne zalężnosci to je mockujemy
            np RobotFramework, to robimy Fake
            
"""
class FakeBuildIn:
    
    def __init__(self, mapping=None, should_raise=False):
        self.mapping = mapping or {}
        self.should_raise = should_raise
    
    def get_variable_value(self, name):
        if self.should_raise:
            raise Exception("RF error simulated")
        return self.mapping.get(name, None)
    
"""
   Krok 3: pierwszy test, najprostrzy przypadek: positive case
    Cel:
        upewnienie sie że gdy BuildIn zwraca warość, to funkcja ją oddaje
        
"""

def test_returns_value_when_present(monkeypatch):
    # setup 
    fake = FakeBuildIn(mapping = {
        "${test_path}" : "/tmp/ini.log"
    })
    monkeypatch.setattr(verification, "BuiltIn", lambda: fake)
    # test function
    result = verification.get_robot_variable("${test_path}")
    # assert result
    assert result = "/tmp/ini.log"
    
"""
    Krok 4:
        przypadek: istnieje zmienan ale jest pusta lub None
"""

def test_empty_or_none(monkeypatch, value):
    fake = FakeBuiltIn(mapping={"${X}": val})
    monkeypatch.setattr(verification, "BuiltIn", lambda: fake)

    assert verification.get_robot_variable("${X}") is None
    

"""
    Krok 5:
        zmienna nie istnieje
"""
def test_missing_variable_returns_none(monkeypatch):
    fake = FakeBuiltIn(mapping={})  # brak klucza
    monkeypatch.setattr(verification, "BuiltIn", lambda: fake)

    assert verification.get_robot_variable("${UNKNOWN}") is None
    
"""
    Krok 6:
        Przypadek c: wyjatek + log warning
        
"""
def test_exception_logs_warning_and_returns_none(monkeypatch):
    # 1) BuiltIn wywali wyjątek
    fake = FakeBuiltIn(should_raise=True)
    monkeypatch.setattr(verification, "BuiltIn", lambda: fake)
    calls = []
    def fake_log_msg(msg, lvl="INFO", to_console=False):
        calls.append({"msg": msg, "lvl": lvl, "to_console": to_console})

    monkeypatch.setattr(verification.LoggerManager, "log_msg", fake_log_msg)
    result = verification.get_robot_variable("${ANY}")
    
    assert result is None
     assert any(
        c["lvl"] == "WARNING" and "Variable ${ANY} not set in test" in c["msg"]
        for c in calls
    ), f"Expected WARNING log with variable name, got: {calls}"
     
"""
    Edge cases: rózne wartości, nie stringowe
        czy akceptujemy value != str
"""

@pytest.mark.parametrize("val", [42, True, 0, [], ["x"], {"a": 1}])
def test_non_string_values_are_returned_as_is(monkeypatch, val):
    fake = FakeBuiltIn(mapping={"${VAR}": val})
    monkeypatch.setattr(verification, "BuiltIn", lambda: fake)

    assert verification.get_robot_variable("${VAR}") == val
    
    
"""
    Łapanie wyjątków
        używamy 
            with pytest.raises(Exception) as e_info:
                instrukcje
            
            assert info.
"""
  def test_load_thresholds_argument_type(self):
        incopatibile = 123
        with pytest.raises(TypeError) as argument_error:
            verification.load_thresholds_json(incopatibile)
            
        assert argument_error.type is TypeError
        assert argument_error.value.args[0] == "expected str, bytes or os.PathLike object, not int"
        
        
        
"""
    Łapanie logów z logging:
        fixture caplog
        with caplog.at_level("WARNING"):
            result = load_thresholds_json(bad_file)
        tymczasowo ustawia poziom logowania na logging
        zbiera wszystkie komunikaty logów w bloku
        udostepnai je w caplog.records ( lsita obektów logów) 
        i caplog.text - surowy text
        
"""