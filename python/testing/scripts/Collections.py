
def clear(name_of_collection):
    print("------------------------------------------------------------\n")
    print(name_of_collection)
    
'''
    Obsługa:
        list 
        krotek
        słowników
        zbiorów
        slicing i string
'''

def list_revise():
    '''
        Listy są mutowalne - można je modyfikować 
        Elementy uporządkowane / indexowane
        Mogą zawierać różne typu danych
    '''
    simple_list = [ 1, 2, 3]
    simple_list.append(6)
    simple_list.remove(2)
    sliced_list = simple_list[1:3] 
    print(simple_list, sliced_list)
    # składane
    even_numbers = [
        numb for numb in range(12) if numb % 2 == 0
    ]
    print(f"{even_numbers=}")
    
def tuple_revise():
    '''
        Krotki są niemutowalne, nie można ich zmieniać
        Uporzadkowane /indexowane
        Różne typu
        tworzenie - ()    
    '''
    simple_tuple = (5, 12, 63)
    a,b,c = simple_tuple
    print(simple_tuple[1])
    
def dict_revise():
    '''
        Przechowują pary: klucz-wartosc
        Nie są uporządkowane, dostęp za pomocą kluczy 
        Klucze muszą być unikalne, a wartości dowolne
        tworzenie - {} / dict
    '''
    simple_dict = {
        "a" : 12, "b" : 31
    }
    print(simple_dict)
    simple_dict['c'] = 63
    simple_dict['b'] = 123
    for key, value in simple_dict.items():
        print(key, value)
        
    # skladanie słowników
    squared_numbers = {
        numb: numb ** 2 + 1 for numb in range(10)
    }
    print(f"{squared_numbers=}")
    
def set_revise():
    '''
        Są mutowalne, ale elementy muszą być niemutowalne ( liczby, krotki, stringi)
        Niie mogą zawierać duplikatów
        Nie są uporządkowane, dostęp poprzez iteracje
    '''
    simple_set = {5, 6, 12, (5, "Siemano", 'k')}
    simple_set.add(74)
    simple_set.discard(6310) # if not exist its ok
    simple_set.remove(5) # if not exist error
    second_set = {2,7,5}
    print(simple_set)
    union_set =  simple_set | second_set # unia
    intersection_set = simple_set & second_set # przeciecie
    difference_set = simple_set - second_set # różnica
    print(union_set, intersection_set, difference_set)
    
    # zbiory skladane
    odd_numbers = {
        num for num in range(10) if num % 2 == 1
    }
    print(odd_numbers)

def string_revise():
    simple_string = "Siemano, Kolano {}"
    size = len(simple_string)
    indexing_from0to = simple_string[:5]
    indexing_from_toEnd = simple_string[5:]
    indexing_end_of_string = simple_string[:-1]
    operation_dict = {
        "BigFirst" : simple_string.capitalize(),
        "BigAll" : simple_string.upper(),
        "ReplaceWith" : simple_string.replace("e", "a"),
        "RemoveWhitespaces" : simple_string.strip(),
        "RemoveFromRight" : simple_string.rstrip(),
        "RemovingFromLeft" : simple_string.lstrip(),
        "SplittingBasedOn" : simple_string.split(","),
        "FormatingOne" : f"{simple_string} and after it its {12}",
        "Second format" : simple_string.format("and its for last")
    }
    for key,value in operation_dict.items():
        print(key, value, sep="--> ")
    
    # operatory
    x = [1,2,3]; y =[1,2,3]; z = x
    if x == y: #  czy sa one równe
        print("eqals")
    if x is z: # czy sa tymi samymi obiektami
        print("The same objects")
    
    # skladanie stringow (listy i słowniki)
    strings_list = ["apple", "banana", "orange", "kiwi"]
    len_of_strings = {
        string : len([f"{size}" for  size in range(1, len(string))]) for string in strings_list
    }
    print(f"{len_of_strings}")
  

if __name__ == "__main__":
    clear("list")
    list_revise()
    clear("tuple")
    tuple_revise()
    clear("dict")
    dict_revise()
    clear(set.__name__)
    set_revise()
    clear(str.__name__)
    string_revise()