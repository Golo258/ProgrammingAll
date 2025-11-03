// =============================
// classes.cpp
// =============================
#include "classess.hpp"
#include "logger.hpp"
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
    using namespace std;
    Logger log;
    log.set_min_level(LogLevel::Debug);

    log.info() << "=== Classes Playground ===\n";
    Dog rex{"Rex", 12};
    rex.bark();
    rex.birthday();
    rex.bark();

    Animals shelter;
    shelter.add(rex);
    shelter.add("Burek", 5);
    shelter.list();
    log.debug() << "Contains burek: " << boolalpha << shelter.contains_name("Burek") << endl;
    log.debug() << "Alive: " << Dog::alive_count() << "\n";
    //  enum usage
    TaskStatus status = TaskStatus::InProgress;
    string status_name = get_string_from_status(status);
    log.debug() << "Status name: " << status_name << endl;
    optional<TaskStatus> from_string_status = get_task_from_string("Done");
    if (from_string_status){
        log.debug() << "Status from string by value "
            << get_string_from_status(from_string_status.value())
            << endl;
        log.debug() << "Status from string by derefence "
            << get_string_from_status(from_string_status.value())
            << endl;
    
    }
    else{
        log.error() << "Unknown type provided \n";
    }

    // Task in class 
    Task create_fun("Create function with nullptr");
    create_fun.show_task();
    create_fun.start_task();
    create_fun.show_task();
    // create_fun.cancel_task();
    create_fun.finish_task();
    create_fun.show_task();
    if (create_fun.is_done()){
        log.info() << "Task finished successfully\n";
    }

    // Dziedziczenie
    Employee stared("Adam", 2000);
    stared.info();
    stared.work();

    Manager highest("Kasia", 7000, 5);
    highest.info();
    highest.work();
}


void greet(std::ostream& os){
    os << "Whats up\n"; 
}

//  funkcja zwracająca ostream
std::ostream& label(std::ostream& os, const char* text)
{
    os << "[" << text  << "]\n";
    return os;
}
// logger
std::ostream& log_info(std::ostream& os)
{
    return os << "[INFO] ";
}