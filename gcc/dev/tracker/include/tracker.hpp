

#pragma once
#include <httplib.h>
#include <variables.hpp>
#include <json.hpp>

using json = nlohmann::json;

void example_curl() {
    std::string base_url = "http://api.nbp.pl";
    httplib::Client client(base_url);

    auto response = client.Get("/api/exchangerates/rates/c/usd/2016-04-04/?format=json");
    if (response != NULL){
       
        if (response->status == 200){
            logger.info() 
                << "[RESPONSE DATA]"
                << "STATUS: " << response->status << ENDL
                << "BODY: "   << response->body   << ENDL; 
            
            auto json_body = json::parse(response->body);
            logger.debug() << "JSON BODY: " << json_body  << ENDL; 

        }
        else {
            logger.error() << "INCORRECT STATUS CODE" << ENDL;
        }
    }
    else {
        logger.error() 
            << "Error occured while getting response " << ENDL
            << "RETURN CODE" << response.error()       << ENDL;
    }  

}
