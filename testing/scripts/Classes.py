

class Car:
    def __init__(self, make, model):
        self.make = make
        self.model = model

    def display_info(self):
        print(f"{self.make} {self.model}")
        

car1 = Car("Toyota", "Camry")
car1.display_info()  # Wywołanie metody obiektu


# inheritance

class ElectricCar(Car):
    def __init__(self, make, model, battery_capacity):
        super().__init__(make, model)
        self.battery_capacity = battery_capacity
        
    def display_info(self):
        print(f"{self.make} {self.model} - Battery: {self.battery_capacity} kWh")
        
car2 = ElectricCar("Toyota", "Camry", 125)
car2.display_info()  # Wywołanie metody obiektu


# encapsulation

class Person():
    def __init__(self, name, age) :
        self._name = name
        self._age = age

    @property
    def name(self):
        return self._name
    
    @property
    def age(self):
        return self._age

    @age.setter
    def age(self, value):
        if value > 0:
            self._age = value
            
person = Person("Alice", 30)
print(person.name)  # Odczytanie zmiennej prywatnej za pomocą właściwości
person.age = 31 

# Polimorfizm różne klasy a te same metody albo operacje

class Animal:
    def make_sound(self):
        pass

class Dog(Animal):
    def make_sound(self):
        return "Woof!"

class Cat(Animal):
    def make_sound(self):
        return "Meow!"

def make_animal_sound(animal):
    print(animal.make_sound())

dog = Dog()
cat = Cat()

make_animal_sound(dog)  # Wywołanie metody make_sound() dla obiektu Dog
make_animal_sound(cat) 