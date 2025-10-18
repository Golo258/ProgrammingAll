// =============================
// classes.cpp
// =============================
#include "classess.hpp"
#include <string>
#include <iostream>
#include <stdexcept>
/*-------------- DEFINITIONS ----------------------*/


bool Dog::_validate_age(int age) const
{
    if (age < 0 || age > 20){
        throw std::out_of_range(
            "Dog age outt of reasonable bounds (0..20)"
        );
    }
    return true;
}

Dog::Dog(std::string name)
    : _name(name), _age(0)
{
    ++_alive;
}

Dog::Dog(std::string name, int age)
{
    _name = name;
    if (_validate_age(age)) {
        ++_alive;
    }
}

Dog &Dog::set_name(const std::string &new_name)
{
    _name = new_name;
    return *this;
}

Dog &Dog::set_age(int age)
{
    if (_validate_age(age)) {
        _age = age;
    }
    return *this;
}

void Dog::bark() const
{
    std::cout << _name << " (age " << _age << "): Woof!\n";
}

void Dog::birthday()
{
    set_age(_age + 1);
}

int Dog::alive_count() 
{
    return _alive;
}


bool operator==(const Dog& a, const Dog& b)
{
    return a._name == b._name && a._age == b._age;
}

// ------------------------- Animals
void Animals::add(const Dog& new_dog)
{
    _dogs.push_back(new_dog);
}

void Animals::add(std::string name, int age)
{
    _dogs.emplace_back(
        name, age
    );
}
void Animals::list() const 
{
    if (_dogs.empty()){
        std::cout << "[Animals] are empty\n";
        return;
    }
    std::cout << "[Animals] dogs\n";
    for (const auto& dog: _dogs){
        std::cout << "  - " << dog.name() << " (age " << dog.age() << ")\n";
    }
}


bool Animals::contains_name(const std::string& name) const
{
    return std::any_of(
        _dogs.begin(), _dogs.end(),
        [&](const Dog& dog){
            return dog.name() == name;
        }
    );
}

void classes_runner(){
    std::cout << "=== Classes Playground ===\n";
    Dog rex{"Rex", 12};
    rex.bark();
    rex.birthday();
    rex.bark();

    Animals shelter;
    shelter.add(rex);
    shelter.add("Burek", 5);
    shelter.list();
    std::cout << "Contains burek: " << std::boolalpha << shelter.contains_name("Burek") << std::endl;
    std::cout << "Alive: " << Dog::alive_count() << "\n";
}