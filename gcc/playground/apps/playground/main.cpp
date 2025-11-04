// ---------EXTERNAL----------------
#include <string>
//----------INTERNAL----------------
#include <logger.hpp>
#include <utils/parse.hpp>


int main() {
    Logger log{std::clog, LogLevel::Debug, true};

    log.debug() << "Start aplikacji\n";
    log.info()  << "Siema, działa logowanie\n";
    log.warn()  << "Uwaga  to tylko demo\n";
    log.error() << "Błąd testowy\n";
    log.info()  << add(5, 12) << std::endl;

    return 0;
}