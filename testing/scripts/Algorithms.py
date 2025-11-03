

# Wyszukiwanie elementu w liscie

def linear_search(array, target):
    for index in range(len(array)):
        if array[index] == target:
            return index

    return -1

arr = [4, 2, 7, 1, 9, 5]
target = 7
print(f"{target} is list {arr} is on position {linear_search(arr, target)}")

def find_min(array):
    if len(array) == 0:
        return None
    
    min_value = array[0]
    for index in range(1, len(array)):
        if array[index] < min_value:
            min_value = array[index]
    
    return min_value

arr = [4, 2, 7, 1, 9, 5]
print(find_min(arr))  # Wynik: 1

def find_max(array):
    max_value = array[0]
    for index in range(1, len(array)):
        if array[index] > max_value:
            max_value = array[index]
            
    return max_value

print(find_max(arr))
        
def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]

# Przykład użycia
arr = [4, 2, 7, 1, 9, 5]
bubble_sort(arr)
print(arr)  # Wynik: [1, 2, 4, 5, 7, 9]

def insertion_sort(arr):
    n = len(arr)
    for i in range(1, n):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

# Przykład użycia
arr = [12, 11, 13, 5, 6]
insertion_sort(arr)
print("Posortowana lista:", arr)

#----------------------------------
#EXceptions
def this_fails():
    x = 1 /0
    
try:
    result = 10/2
    print(result)
except ZeroDivisionError as err:
    print(err)
else: # tylko wtedy gdy nie został wywołany wyjatek
    print("If there is no exception I will print it ")
finally: # zawsze sie wykona nie wazne czy jest cz nie ma wyjatku
    print("I will always occur not matter of exception")