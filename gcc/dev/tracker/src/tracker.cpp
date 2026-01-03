

#include <tracker.hpp>
#include <httplib.h>

void example_curl2() {
    httplib::Client client("api.nbp.pl");
    client.set_proxy("", 0);
    auto res = client.Get("/api/exchangerates/rates/a/usd/?format=json");
    if (res) {
        if (res->status == 200) {
            logger.debug() 
                << "Kurs dolara: " 
                << res->body << std::endl;
        }
        else {
            logger.debug() 
                << "Serwer odpowiedział, ale kodem: "
                << res->status << std::endl;
        }
    }
    // else {
    //     auto err = res.error();
    //     logger.debug() 
    //         << "Błąd połączenia! Kod błędu httplib: " 
    //         << (int)err << std::endl;
    // }
}