

#pragma once
#include <variables.hpp>
#include <json.hpp>
#include <curl/curl.h>

using json = nlohmann::json;

void example_curl_get();
void example_curl_post(CURL* curl);
void example_curl_get(CURL* curl);

size_t WriteCallback(
    void* contents,
    size_t size,
    size_t nmemb,
    std::string* userp
);