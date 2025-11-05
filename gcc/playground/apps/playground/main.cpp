// ---------EXTERNAL----------------
#include <string>
//----------INTERNAL----------------
#include <utils/logger.hpp>
#include <utils/parse.hpp>
#include <docs/knowledge.hpp>


void logger_example(){
    Logger log{std::clog, LogLevel::Debug, true};
    log.debug() << "Start aplikacji\n";
    log.info()  << "Siema, działa logowanie\n";
    log.warn()  << "Uwaga  to tylko demo\n";
    log.error() << "Błąd testowy\n";
}
int main() {
    Logger log{std::clog, LogLevel::Debug, true};
    // Strumienie, zabawa
    log.info() << "\n<======================================>\n";
    // Knowledge::StreamsManagement::standard_stream();
    Knowledge::StreamsManagement::show_file_stream();
    log.info() << "\n<======================================>\n";
    return 0;
}