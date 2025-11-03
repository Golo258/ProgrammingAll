      
def functions_revise():
    "argumenty pozycyjne"
    def greet(name):
        print("Hello", name)
    
    greet("Zbyszku")
    
    def positional_with_no_length(*many_numbers): # zmienna długość / argumenty pozycyjne
        total = 0
        for num in many_numbers:
            if isinstance(num, int):
                total += num
            else:
                print("Its not a number")
        print(total)
        
    positional_with_no_length(1, 2, 3)  # Wynik: 6
    
    def key_value_with_no_length(**dictionaries_args): 
        ''' argumenty słownikowe ( klucz , value)
            przekazujesz nazwe klucza i potem wartość // zmienna długość
        '''
        for key, value in dictionaries_args.items():
            print(f"{key}: {value}")
    
    key_value_with_no_length(name="Alice", age=12) 
    
    add_numbers = lambda x, y: x ** y + 2
    print(add_numbers(2,3))
    
    numbers = [1, 2, 3, 4, 5]
    def mapowanie(number_list): # przechodzi po elementach i wykonuje na nich operacje
        squared_numbers = list(
            map(lambda numb: numb**2, number_list)
        )
        print(squared_numbers)
    
    mapowanie(numbers)
    
    def filtrowanie(number_list):
        filter_even_numbers = list(
            filter(lambda numb: numb % 2 == 0, number_list)
        )     
        print(filter_even_numbers)
          
    filtrowanie(numbers)
     
    def sortowanie():
        students = [('Alice', 25), ('Bob', 20), ('Charlie', 30)]
        students.sort(
            key= lambda tup: tup[1]
        )
        print(students)
    sortowanie()


if __name__ == "__main__":
    functions_revise()