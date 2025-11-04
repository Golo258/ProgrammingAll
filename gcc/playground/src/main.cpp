#include <logger.hpp>
#include <string>

int main() {
    Logger log{std::clog, LogLevel::Debug, true};

    log.debug() << "Start aplikacji\n";
    log.info()  << "Siema, działa logowanie\n";
    log.warn()  << "Uwaga – to tylko demo\n";
    log.error() << "Błąd testowy\n";

    log.set_min_level(LogLevel::Warn);
    log.info()  << "Tego nie zobaczysz\n";
    log.error() << "To zobaczysz\n";

    return 0;
}