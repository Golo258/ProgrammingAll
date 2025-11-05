#include <iostream>
#include "namespaces.hpp"
#include "structures.hpp"
#include "classess.hpp"
#include "collections.hpp"
#include "logger.hpp"
/* 
    Main function to execute notes functions and classes methods
*/


void structures_runner(){
    Person person{"John", 24};
    person.introduce();
    print_person(person);
    //  zabawa ze wskaźnikami i referencjami
    
    Person* john_pointer = &person;
    Person& john_reference = person;

    std::cout << "Piter pointer introduce\n";
    john_pointer->name = "Piter";
    john_pointer->introduce();
    
    std::cout << "Piter reference introduce\n";
    john_reference.age = 15;
    john_reference.introduce();
    print_person(john_reference);


    // Nested structures
    Address piterAddress{"Cracow", "Maki"};
    Citizen citizen{person, piterAddress, false};
    citizen.show_citizen();
    citizen.isInTown = true;
    citizen.show_citizen();
    // tymczasowe struktury /anonimowe
    struct {
        std::string name;
        int score;
    } player{"Bob", 51};

    std::cout << player.name << std::endl;

    Product car{"Audi", 5};
    Product second{"BMW", 12};
    show_by_value(car);
    show_by_reference(car);
    show_by_pointer(&car);
    second = change_object_by_reference(car);
    show_by_reference(second);
}

void memory_runner(){
    std::cout<< "\nMemory operation\n";
    Group group{"C++", "Many"};
}

void streaming(){
    greet(std::cout);
    //  funkcja zwracająca 
    label(std::cout, "INFO") << "Program started" << endl;
    log_info(std::cout) << "Program started successfully" << endl;
}

void logger_settings(){
    Logger log;
    log.set_min_level(LogLevel::Debug);
    log.info() << "Start programu" << std::endl;
    log.debug() << "Debuging program";

    //  to file
    std::ofstream file("app.log");
    Logger fileLog(file, LogLevel::Debug);
    fileLog.warn() << "Warning in file \n";
    fileLog.error() << "Error occured in file" << std::endl;
}

int main(){
    // structures_runner();
    // memory_runner();
    // playing_with_vector();
    // playing_with_map();
    // playing_with_set();
    // streaming();
    // logger_settings();
    classes_runner();
    return 0;
}

