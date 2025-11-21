import itertools
import time
from itertools import zip_longest
from os import times

from logger import LoggerManager

LoggerManager.configure()
log = LoggerManager.logger
#------------------------------------
# Basics
# snake_case function with arguments
class BasicFunctions:
    
    @staticmethod
    def calculate_total( price, tax):
        """
            Doc string as function documentation,
            arguments and return type
        :param price:
        :param tax:
        :return:
        """
        pass


    # type hints - typowanie, czytelnośc i listing
    @staticmethod
    def sub_total( average: int, amount: int) -> int:
        """
            Małe funkcje, jedna rzecz do zrobienia
                jeśli są efekty uboczne to pisać dokumentacje o tym
        """
        return average * amount

    # domyślne wartości, tylko nie mutowalne
    @staticmethod
    def append_item(item: str, items: list = None):
        if items is None:
            items = None
        items.append(item)
        return items

    """
        -> flexible arguments - *args, **kwargs
            * - pozycjonalne argumenty dowolnej liczby
            zbiera wszystkie dodatkowe argumenty pozycyjne w krotke
                np:
                log_message("INFO", "Como", "estas")
                to msgs - ("Como", "estas")
        ** - argumenty nazwane dowolne liczby
            zbiera wszystkie dodatkowe argumenty nazwane
                key=value w słownik
            example: log_message("INFO", "Como", user="John", code=450); 
                     to extra = {"user":"John", "code": 450}
    """
    @staticmethod
    def log_messae(level, *msgs, **extra):
        print(level, *msgs, extra)

#------------------------------------
    """
    -> Keyword-only arguments 
        wymusza podanie nazwy argumentu po następnym arugmentcie
        jak dajemy * przed subject, to potem on musi być arugmentem nazwanym
    """
    @staticmethod
    def send_email(to, *, subject="No subject", receiver="user@gmail.com"):
        pass

    def execute(self):
    # send_email("fasfa", "aspfmapos") -> typeError
        self.send_email(
            "anna",
            subject="any",
            receiver="you@tube.com"
        )

#------------------------------------
from functools import wraps
from functools import lru_cache
"""
    LRU- Least Recently Used
    dekorator który pamieta wyniki wywołań funckji (cache)
    jesli cache sie zapłeni usuwa najrzadsze uzywane wyniki
    Funkcja nie musi liczyć tego samego wiele razy
    użyteczne biblioteki
        -> functools - dekoratory, cache, partial
        -> itertools - kombinatoryka, filtorwanie, mapowanie
        -> typing - typy, Union, Otional, Literal
        -> dataclasess - nowoczesny sposób na klasy 
"""

import functools
class FuncToolsExample(object):

    """
        Dekoratory:
            funkcja która opakowuje inne funkcje
            dodając do niej dodatkowe zachowanie
            bez zmieniania jej kodu
        -> prepare_multiply() zwraca funkcje z ustawionym paramerem
            (12) od razu wywołuje metode z ostatnim atrbutem
            
        -> partial przygotowuje poczatek funckji
            z jakimś poczatkowym agumentem 
            Oczekuje funkcji, i po przecinku argumentów
        -> reduce(function, iterable, initalizer=None)
                bierze liste elementów i składa je do jednej wartości
            Działąnie:
                - bierze poprzednik i następnik
                - wykonuje na nich scalanie (funkcja) 
                - leci dalej  po kolekcji
    """
    def log(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            print(f"Calling @{func.__name__}")
            return func(*args, **kwargs)
        return wrapper

    def timer(func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            start = time.time()
            result = func(*args, **kwargs)
            end = time.time()
            log.info(f"{func.__name__} took {end - start:.4f} seconds")
            return result
        return wrapper

    @log
    @timer
    def greet(self, name):
        log.info(f"Hello {name}")

    @functools.lru_cache(maxsize=32)
    @timer
    def get_users_data(self, user_id: int):
        print(f"Fetching data for {user_id}")
        return {"id": user_id, "name": f"User{user_id}"}

    def multiply(self, axis_x, axis_y):
        return axis_x * axis_y

    def prepare_multiply(self):
        return functools.partial(self.multiply, 5)

    def prepare_named_multiply(self):
        named_multiply_axis_y = functools.partial(self.multiply, axis_y=12)
        return named_multiply_axis_y

    def count_example(self, previous_obj, next_obj):
        numbers = list()
        add_new_number = lambda word: {
            "name": word[:-1],
            "value": int(word[-1:])
        }
        if isinstance(previous_obj, str):
            numbers.append(add_new_number(previous_obj))
        else:
            numbers = previous_obj
        numbers.append(add_new_number(next_obj))
        return numbers

    def reduce_explanation(self):
        numbers = list(range(0,12))
        total = functools.reduce(
            lambda previous_nr, next_nr: previous_nr + next_nr,
            numbers,
            1
        )
        log.info(total)
        # list of string explanation # liczenie
        words = ["one1", "two2", "three3", "four4"]
        words_dir = functools.reduce(self.count_example, words)
        log.info(f"Words dir: {words_dir}")
        
 
#-----------------------------------
#-----------------------------------

func_tools = FuncToolsExample()
func_tools.greet("Manny")
func_tools.get_users_data(1)  # Fetching data for 1
func_tools.get_users_data(1)  # z cache, już nic nie fetchuje
log.debug(func_tools.prepare_multiply()(12))
named_partial = func_tools.prepare_named_multiply()
log.debug(named_partial(1))
func_tools.reduce_explanation()        

#-----------------------------------
#-----------------------------------
"""
ITERATOR -
    obiekt którego elementy można pobierać po kolei
    musi miec dwie metody:
        __iter__ - zwraca samego siebie (jest iterowalny)
        --next__ - zwraca kolejny element, rzuca StopIteration
"""
def iterator_example():
    numbers = iter([10, 20, 30])
    log.debug(next(numbers))
    log.debug(next(numbers))
    log.debug(next(numbers))
    try:
        log.debug(next(numbers))
    except StopIteration as si:
        log.error(si)
        
iterator_example()
#-----------------------------------
"""
    GENERATOR - to iterator, któy pisze sie za pomocą yield w funckji
        to rodzaj iterator, prostrszy to stworzenia
        nie trzeba implementować funkcji iter i next
    Każdy generator jest iteratorem
"""
def generator_example():

    def simple_gen():
        yield 1
        yield "abc"
        yield True

    gen = simple_gen()
    log.info(next(gen))
    log.info(next(gen))
    log.info(next(gen))
    # log.info(next(gen)) Stop Iteration
generator_example()
#-----------------------------------

"""
    ITERABLE - to obiekt po którym można iterować
        taki który potrafi utworzydc iteratora
            żeby coś było iterable musi mieć metode __iter__
        nie posiada __next - jest źródłem danych 
    Na przykłąd listy stringi słowniki tuple itp
"""
def iterable_example():
    listy= [1, 2, 3]
    stringi= "hello"
    tuple= (1, 2)
    dict= {"a": 1, "b": 2}
    sety= {1, 2, 3}

iterable_example()

import itertools
class IterToolsLibExplanation(object):
    """
        Praca z listami, generatorami,iterowalnymi rzeczami
        itertools działa leniwie - generuje dane na bieżaco
            3 grupy funkcji:
            - nieskończone iteratory, lecą aż je zatrezymasz
            - skonczone iteratory - biorą coś i robią z tym dane rzecz
            - kombinatoryka - tworzyą permutacje, kombinacje itp
    """
    def infinity_iterator(self):
        for index in itertools.count(10, 2):# count
            log.info(index)
            if index > 20:
                break

        for color in itertools.cycle(["red", "green", "blue"]):# cicle - zapelta sekwencje
            log.debug(color)
            if color == "blue":
                break
        """
            repeat - potwarza wiele razy daną sekwencje
                jesli nie podamy times to bedzie potwarzał w nieskonczoność
        """
        for sequence in itertools.repeat("---", times=5):
            log.debug(sequence)

    def finite_iterator(self):
        """
            -> chain(*iterables) - łączy kilka kolekcji - iterowalnych obiektów
                działa też na generatorach
            -> islice (iterable, start, stop, step)
                - lazy slice
                wycinanie jak w list[start:stop:step] 
                tylko że działa na dowolnym iteratorze
            ->startmap(func, iterable_of_tuples)
                mapowanie argumentów wzgledem funkcji:
            -> map(), rozpakowuje krotki argumentów jako argumenty funkcji
                każdy argument musi byc krotką /listą
            -> tee(itearble, n=2)
                tworzy n niezależnych iteratorów
                które czytają te same dane z jednego źródła (iterable)
            -> zip_longest - jak zipowanie danych
                tylko nie konczy sie po krótszej liście
        """
        for iter_obj in itertools.chain([1, 2], ['a', 'b'], [True]):
            log.info(f"{iter_obj},Type: {type(iter_obj)}")
        #--------------------------------------------
        for obj in itertools.islice(itertools.count(), 5, 10):
            log.debug(obj)
        #--------------------------------------------
        def multiply(a, b, c=None):
            if c:
                return a * b * c
            else:
                return a * b
        data = [(2, 3), (4, 5, 12), (6, 7)]
        log.info(list(itertools.starmap(multiply, data)))
        #--------------------------------------------
        def format_price(name, price): # lepszy przykład
            return f"{name}: {price:.2f} zł"
        products = [("apple", 1.99), ("Banan", 3.49), ("Kiwi", 4.25)]
        for line in itertools.starmap(format_price, products):
            log.debug(line)
        #--------------------------------------------
        data = [1, 2, 3]
        a, b = itertools.tee(data)
        log.info(list(a))
        log.info(list(b))
        #--------------------------------------------
        longest, shortest  = [1, 2 ,3], ["a", "b"]
        log.debug(list(itertools.zip_longest(
            longest, shortest, fillvalue='?#')
        ))

    def combinatorics_example(self):
        """
            -> produkt - wszystkie możliwe kobinacje elementów
               iloczyn kartezjański
            -> permutations(iterable, r=None)
               permutacje - wszystkie możliwe ułożenia elemnentów
        """
        log.info(list(itertools.product([1, 2], ['a', 'b'])))
        log.info(list(itertools.permutations("abc", 2)))

#--------------------------------------------
iter_tool_Lib = IterToolsLibExplanation()
iter_tool_Lib.infinity_iterator()
iter_tool_Lib.finite_iterator()
iter_tool_Lib.combinatorics_example()
#--------------------------------------------


# Operacje na plikach:
from pathlib import Path
class FilesOperation:
    pass