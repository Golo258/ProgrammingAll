class FirstOne:
    def __init__(self, brand, model):
        self.brand = brand
        self.model = model
        self.age = 12

    def show_info(self):
        print(f"{self.brand} {self.model}. age: {self.age}")


my_first = FirstOne("Scoda", model="AV2")
my_first.age = 51
my_first.show_info()


# Identity and mutable

class BankAccount:
    def __init__(self, balance):
        self.balance = balance

    def put_money(self, money):
        self.balance += money

    def take_money(self, money):
        self.balance -= money

    def show_balance(self):
        print(f"{self.balance= }")


account = BankAccount(balance=51)
account2 = BankAccount(balance=1000)

account.put_money(51)
account.show_balance()
# mutable of object -> operation on object have only impact on this object but not class and other objects
account.balance = 12
print("Balances: " + str(account.balance) + str(account2.balance))
from first_slides import CatchingException


# checking identity of object
def check_identity(accounts: list[BankAccount]) -> bool:
    return True if accounts[0] is account[1] else False


# multi inheritance
class Aclass:
    def method_a(self):
        print("Method a")


class Bclass:
    def method_b(self):
        print("Method b")


class CClass(Aclass, Bclass):
    pass


# mixin
class JsonMixin:
    def to_json(self):
        import json
        return json.dumps(self.__dict__)


class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age


class JsonPerson(JsonMixin, Person):
    pass


# Polimorfizm

class Kot:
    def dzwiek(self):
        return "Miau!"


class Pies:
    def dzwiek(self):
        return "Hau!"


# abstract
from abc import ABC, abstractmethod


class Figure(ABC):
    @abstractmethod
    def count_square(self): pass


class Rectangle(Figure):
    def __init__(self, site):
        self.site = site

    def count_square(self):
        return self.site ** 2;


if __name__ == '__main__':
    try:
        check_identity([account, account2])
    except Exception as e:
        print(e)

    cclas = CClass()
    cclas.method_a()
    cclas.method_b()
    person = JsonPerson("Johny", 30)  # to_string is delivered to Person class by mixin
    print(person.to_json())

    class_list = [Kot, Pies]
    for class_arg in class_list:
        animal = class_arg()
        print(animal.dzwiek()
              )
    rect = Rectangle(5)
    print(rect.count_square())

