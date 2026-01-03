

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

void example_curl() {
    CURL* curl;
    CURLcode response;
    std::string read_buffer;
    long int curl_timeout = 100L;
    curl = curl_easy_init();
    if (curl){
        curl_easy_setopt(
            curl,
            CURLOPT_URL,
            "https://jsonplaceholder.typicode.com/posts/1"
        );
        curl_easy_setopt(
            curl,
            CURLOPT_WRITEFUNCTION,
            WriteCallback
        );
        curl_easy_setopt(
            curl,
            CURLOPT_WRITEDATA,
            &read_buffer
        );
        curl_easy_setopt(
            curl,
            CURLOPT_TIMEOUT,
            curl_timeout
        );
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
    }
    else {
        logger.error() << "Cannot initalize CURL" << ENDL;
    }
}