



"""
1. Podstawy BaseModel
    -Pola defniujesz adnotacjami typów
    -wartości domyslne po prostu np name: str = "Antony"

2.  Input /output / parsing
    - Wejście tworzenia obiektu:
        surowe dane np dict Jsonowy
    - Pydantic parsuje (konwertuje jesli może) i waliduje typy danych
    - wyjście: 
        obiekt z poprawnie ztypowanymi polami albo wyjątek z lista błędów

3.  Konwersja vs strict mode
    Jeśli mamy określony typ argumentu a podamy inny
        to pydantic sam próbuje skonwertować go na docelowy
    Jeśli nie chcesz tego to można ustawić pole na
    strict = True
        To jest ścisła kontrola typowania 
        bez defaultowej konwersji "123" na 123 
        albo "False" na False
        
        
    tak też można tworzyć
    threshold = Threshold(value=10.5)

"""
import re
import math

from enum import Enum
from datetime import datetime
from logger import logger
from pydantic import (
    BaseModel,
    ValidationError,
    Field,
    field_validator,
    model_validator
)

class User(BaseModel):
    id: int
    name: str
    age: int = 18
    sex: str = Field(..., strict=True)
    
user = User.model_validate(
    {
        "id" : "123",
        "name" : "John",
        "sex" : "male"
    }
)
    
logger.debug(f"User id: {user.id} , Type: {type(user.id)}")
logger.debug(user.model_dump())

try:
    user = User.model_validate(
    {
        "id" : "ab",
        "name" : "Eugeniusz",
        "sex" : "male"
    }
)
except ValidationError as e:
    logger.error(e)

# strict bardziej
class Event(BaseModel):
    seats: int
    seats_strict: int = Field(..., strict=True)
    
Event.model_validate({
    "seats": "42",        # OK — Pydantic przekonwertuje
    "seats_strict": 42    # OK — to już int
})

# Event.model_validate({
#     "seats": "42",        # OK — przekonwertuje
#     "seats_strict": "42"  # ❌ Błąd — bo to string, nie int
# })

"""
    Field daje możliwość walidacji
        ... - oznaczają że pole jest wymagane
        gt - wieksze
        ge - wieksze równe
        le - mniejsze równe
        min_length - itp
    Inne przydatne:
        default         = wartośc domyslna | np age: int = Field(18)
        default_factory = dynamicznie tworzy wartośc domyślna | created_at: datetime = Field(default_factory=datetime.utcnow)
        title:   krótki opis | np: Field(..., title="User ID") 
        description: dłuższy opis 
        gt, ge, lt, le  | Porównania liczbowe (>, >=, <, <=)
        pattern - regex dla stringó np: Field(pattern=r"^[a-z0-9_]+$")
        alias = umożliwia używanie innej nazwy np: Field(alias="user_id")
        exclude=True = nie pojawi sie w model_dump 
        repr=False = nie pojawi sie w __rep__ / print
"""

class Account(BaseModel):
    id: int = Field(
        gt=0,
        strict=True,
        description="Account identifier"
    )
    username: str = Field(
        min_length=3,
        max_length=15,
        pattern=r"^[a-z0-9_]+$"
    )
    balance: float = Field(default=0.0, ge=0)
    password: str = Field(min_length=8, repr=False)
    created_at: datetime = Field(default_factory=datetime.utcnow)

tom_account = Account.model_validate({
    "id": 5,
    "username": "tom_123",
    "password": "supersecret"
})
logger.debug(tom_account)


"""
    Enum - enumeration - wyliczenie możliwych wartości
        tworzenie zamknietego zbioru nazwanych stałych
        wartosci które mogą przyjąć określone opcje 
        
"""


class MetricGroup(Enum):
    OVERALL_METRICS = "OVERALL_METRICS"
    PROCESSES_METRICS = "PROCESSES_METRICS"
    
    
logger.info(MetricGroup.OVERALL_METRICS) # tykieta 
# MetricGroup.OVERALL_METRICS

logger.info(MetricGroup.OVERALL_METRICS.value)
# OVERALL_METRICS

class Entry(BaseModel):
    name: MetricGroup

e = Entry.model_validate({"name": "OVERALL_METRICS"})
# e = Entry.model_validate({"name": "LOL"})  # błąd: nie jest w Enum


"""
    Walidatory pól @field_validator
        post - domyślny - działa po wstępnej konwersji
        pre  - działa zanim pydantic spróbuje przekonwertować
        
    Co robi:
        definiuje metode w klasie modelu, która sprawdza/modyfikuje pojedyncze pole
        metoda sprawdza / modyfikuje czy zmienna 
            w defincji model_validate spełnia założenia
    Schemat:
        @field_validator("nazwa_pola", mode="post")  # albo mode="before" (czyli pre)
        @classmethod
        def nazwa_funkcji(cls, value):
            ...
            return value
"""

class Threshold(BaseModel):
    value: float = Field(...)
    name: str
    # sprawdzenie pola
    @field_validator("value", mode="after")
    @classmethod
    def must_be_finite(cls, check_value: float):
        if not math.isfinite(check_value):
            raise ValueError("Value must be a finite number")
        return check_value
    
    # sprawdzenie i zmiana
    @field_validator("name", mode="before")
    @classmethod
    def normalize_name(cls, v):
        # działa przed konwersją — np. obetnij spacje, popraw format
        if not isinstance(v, str):
            raise TypeError("Name must be a string")
        return v.strip().capitalize()
    
    
logger.info(Threshold.model_validate({"value": 12, "name": "    tom "}))     # ✅ OK
logger.info(Threshold.model_validate({"value": "12", "name": "co tam   "}))   # ✅ OK (zostało skonwertowane)
# Threshold.model_validate({"value": float("inf")})  # 💥 ValidationError

"""
    @model_validator
        walidacja wielu pól
        Gdy chcemy sprawdzić zależności miedzy polami
"""
class Range(BaseModel):
    min: int
    max: int
    
    @model_validator(mode="after")
    def check_range(self):
        if self.min > self.max:
            raise ValueError("Min cannot be greater then max")
        return self


range_model = Range.model_validate({"min": 12, "max" : 15})
logger.info(range_model)

"""
    Type unii:
        czyli albo to albo to
    mean: float | int = Field(default=0)

    Można też definować config 
    w pydantic v1
    extra - forbid  - zabrania dodawania kolejnych pól
    class Config:
        extra = "allow" // Określa, co zrobić z dodatkowymi polami: "allow", "ignore", "forbid"
        str_strip_whitespace: Czy automatycznie usuwać spacje z początku/końca stringów
        str_to_lower auitomatyncize zmienia na małe litery
        str_to_upeper - to samo tylko duze litery
        json_schema = dodatkowe informacje do schematu JSON
        
                     
"""
