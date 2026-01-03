

#pragma once
#include <variables.hpp>
#include <json.hpp>
#include <curl/curl.h>

using json = nlohmann::json;

void example_curl();

size_t WriteCallback(
    void* contents,
    size_t size,
    size_t nmemb,
     std::string* userp
);