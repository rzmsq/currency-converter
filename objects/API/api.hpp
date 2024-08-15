/*
    Класс API реализван с целью взаимодействия с api курса валют
    сайта openexchangerates.org

    API класс является композицией скласса Currency.

    В нём имеется только один открытй метод, который возвращает
    текущий курс передоваемой валюты (по имени).

    Остальная реализация скрыта:
        getResponseAPI()    -  отправляет запрос api используя Curl
                               после полуения вызывает следующий метод

        writeResponseJSON() -  данный метод записывает полученные данные в
                               приватную переменную data и в файл json

*/

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <map>

#include <nlohmann/json.hpp>

class API
{
private:
    using json = nlohmann::json;
    json data;

    static size_t writeCallback(void *, size_t, size_t, void *);
    void errMsg(std::string);
    static const std::string getAPIkey();

public:
    // API(/* args */);
    void getResponseAPI();
    double getCurrency(std::string);
};