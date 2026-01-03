

#pragma once
#include <httplib.h>
#include <variables.hpp>
#include <json.hpp>

using json = nlohmann::json;

inline void example_curl() {
    httplib::Client client("api.nbp.pl");
    client.set_proxy("", 0);

    if (auto res = client.Get("/api/exchangerates/rates/a/usd/?format=json")) {
        if (res->status == 200) {
            logger.debug() 
                << "Kurs dolara: " 
                << res->body << std::endl;
        } else {
            logger.debug() 
                << "Serwer odpowiedział, ale kodem: "
                << res->status << std::endl;
        }
    } 
    else {
        auto err = res.error();
        logger.debug() 
            << "Błąd połączenia! Kod błędu httplib: " 
            << (int)err << std::endl;
    }
    client.Delete()
}

void example_curl2();