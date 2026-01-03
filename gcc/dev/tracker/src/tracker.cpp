

#include <tracker.hpp>

size_t WriteCallback(
    void* contents,
    size_t size,
    size_t nmemb,
     std::string* userp
) {
    size_t totalSize = size * nmemb;
    userp->append(
        (char*)contents, 
        totalSize
    );
    return totalSize;
}

void example_curl_get() {
    CURL* curl;
    CURLcode response;
    std::string read_buffer;
    /* nagłówi trzyma sie w liście curl_slist*/
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    long int curl_timeout = 100L;
    curl = curl_easy_init();
    if (curl){
        curl_easy_setopt(
            curl,
            CURLOPT_URL,
            "https://jsonplaceholder.typicode.com/posts/1"
        );
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA,     &read_buffer);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT,       curl_timeout);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER,    headers);

        response = curl_easy_perform(curl);

        if (response != CURLE_OK){
            logger.error()
                << "Error during curl: " 
                << curl_easy_strerror(response) << ENDL;
        }
        else {
            logger.info()
                << "Received data: "
                << read_buffer << ENDL;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    else {
        logger.error() << "Cannot initalize CURL" << ENDL;
    }
}

void example_curl_post(CURL* curl){
    CURLcode response;
    json body = {
        {"name", "Johny"},
        {"score", 100}
    };
    std::string request_body = body.dump();
    curl_easy_setopt(curl, CURLOPT_URL,        "https://api.example.com/score");
    curl_easy_setopt(curl, CURLOPT_POST,       1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request_body.c_str());

    response = curl_easy_perform(curl);
    if (response != CURLE_OK){
        logger.error()
            << "Error during posting data: "
            << curl_easy_strerror(response) << ENDL;
    }
    else {
        logger.info() << "Manage to post data: " << request_body.c_str() << ENDL;
    }

}

void example_curl_delete(CURL* curl){
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.example.com/score/1");
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
}