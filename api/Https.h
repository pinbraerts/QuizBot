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

    Https(std::string&& nurl) {
        url << nurl;
    }
    Https(const Https& other): curlHandle(curl_easy_duphandle(other.curlHandle)) {
        url << other.url.str();
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &url);
    }
    Https(Https&& other): url(std::move(other.url)),
        curlHandle(other.curlHandle) {
        other.curlHandle = nullptr;
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &url);
    }

    Https& operator=(const Https& other) {
        clear();
        url << other.url.str();
        curlHandle = curl_easy_duphandle(other.curlHandle);
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &url);
        return *this;
    }
    Https& operator=(Https&& other) {
        clear();
        url = std::move(other.url);
        curlHandle = other.curlHandle;
        other.curlHandle = nullptr;
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &url);
        return *this;
    }

    std::string makef() {
        std::ostringstream ss;
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &ss);
        curl_easy_setopt(curlHandle, CURLOPT_URL, url.str().c_str());
        auto res = curl_easy_perform(curlHandle);
        if(res != CURLE_OK)
            throw std::runtime_error((std::string)"CURL error: " + curl_easy_strerror(res));
        return ss.str();
    }

    static constexpr class Make {} make {};

    template<class T> inline Https& operator<<(const T& obj) {
        url << obj;
        return *this;
    }
    template<class T> inline Https& operator<<(T&& obj) {
        url << obj;
        return *this;
    }
    inline std::string operator<<(Make _) {
        return makef();
    }

    void clear() {
        if(curlHandle != nullptr) curl_easy_cleanup(curlHandle);
    }

    ~Https() {
        clear();
    }
};

#endif // !HTTPS_H
