#include <curl/curl.h>

#include "api.hpp"

const std::string API::getAPIkey()
{
    std::string api_key;
    std::ifstream file("./objects/API/api.key");

    if (file.is_open())
    {
        std::getline(file, api_key); // Считываем первую строку файла
        file.close();
    }
    return api_key;
}

size_t API::writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

void API::errMsg(std::string err)
{
    std::cerr << "Oops! Error " << err << std::endl;
}

void API::getResponseAPI()
{
    CURL *curl;
    CURLcode res;
    std::string url = "https://openexchangerates.org/api/latest.json?app_id=" + getAPIkey(); // your api
    curl = curl_easy_init();

    if (curl)
    {
        std::string response;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (res != CURLE_OK)
        {
            errMsg("curl_easy_perform()");
            return;
        }
        data = json::parse(response);
    }
    else
        errMsg("curl init");
}

double API::getCurrency(std::string name)
{
    getResponseAPI();
    return data["rates"].at(name);
}