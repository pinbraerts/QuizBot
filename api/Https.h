#ifndef HTTPS_H
#define HTTPS_H

#include <curl/curl.h>

class Https {
private:
    static size_t writeFunction(char* str, size_t size, size_t nsize, void* p) {
        *reinterpret_cast<std::ostream*>(p) << str;
        return nsize;
    }

    static CURL* newHandle() {
        CURL* res = curl_easy_init();
        if(res == nullptr) throw std::runtime_error("CURL init error!");
        curl_easy_setopt(res, CURLOPT_WRITEFUNCTION, writeFunction);
        return res;
    }

    CURL* curlHandle = newHandle();

public:
    std::ostringstream url;

    Https(std::string&& nurl): url(nurl) {}

    std::string make() {
        std::ostringstream ss;
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &ss);
        curl_easy_setopt(curlHandle, CURLOPT_URL, url.str().c_str());
        auto res = curl_easy_perform(curlHandle);
        if(res != CURLE_OK)
            throw std::runtime_error((std::string)"CURL error: " + curl_easy_strerror(res));
        return ss.str();
    }

    ~Https() {
        curl_easy_cleanup(curlHandle);
    }
};

#endif // !HTTPS_H
