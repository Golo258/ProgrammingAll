
'''
BDD (Behavior Driven Development):
    rodzja oprogramowania ktore skupia sie na zachowaniu systemu
    zamiast koncentrować się na technicznych detalach 
    kladzie nacisk na opisywanie zachowania systemu w sposob zrozumiały
    ulepsza to komunikacje pomiedzy programistami 
    
'''

'''
    Jezyk Gherkin:
        Jezyk do opisywania zachowania systemu w sposob czytelny dla wszystkich
        opisy testów, prosty i zrozumiały

'''
gherkin_example = """
    Feature: User Login         # Określa funkcjonalność którą testujemy
        To get access to system, user has to login
    
    Scenario: User login with correct data      # okresla pojedynczy przypadek testowya
        Given User is on login website          # określa stan poczatkowy/ warunki poczatkowe 
        When User enter his login and password  # okresla akcje zrobione do przetestować funkcjonalność
        Then User is logged in the system       # okresla oczekiwany rezultat / zachowanie po akcji

"""

#Definiowanie kroków
from behave import given, when, then
from random import randint

@given('User typed a number {number}')
def step_impl(context, number):
    context.number = int(number)
    context.number2 = randint(1, 10)
    
@when('User sums this two numbers ')
def step_impl(context):
    context.result = context.number + context.number2

@then('The result should be equal {expected_result}')
def step_impl(context, expected_result):
    assert context.result == int(expected_result)