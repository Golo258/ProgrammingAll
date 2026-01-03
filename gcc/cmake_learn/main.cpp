
#include <iostream>
#include "message.hpp"
#include "math_lib.hpp" // biblioteka 
#include <curl/curl.h> // nagłówke biblioteki zewnętrznej
#include <nlohmann/json.hpp> // external library header

using json = nlohmann::json;

int main(){
    std::cout << get_message() << std::endl;
    std::cout << "Math 4,4: " << add_numb(5,5) << std::endl;

    curl_global_init(CURL_GLOBAL_ALL);
    curl_version_info_data* data = curl_version_info(CURLVERSION_NOW);
    std::cout << "Installed curl version " << data->version << std::endl;
    curl_global_cleanup();
    // json external header library
    json j;
    j["name"] = "Johny";
    j["status"] = "unemployed";
    std::cout << "Json data: " << j.dump(4) << std::endl;
    return 0;
}