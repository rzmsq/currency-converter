/*
    Класс user хранит имеющиейся валюты у пользователя,
    историю операций, а также публичный метод вывода кошелька пользователя
    добавление новой валюты в кошелек и совершение конвертации

*/

#pragma once

#include "../currency/currency.hpp"

class User
{
private:
    std::map<std::string, Currency> userCurrency;
    void changeOldCurrency(Currency &);

    using json = nlohmann::json;
    json j_map;

    void writeUserDataJSON();
    void takeUserDataJSON();

public:
    User()
    {
        takeUserDataJSON();
    };
    void addNewCurrency(Currency &);
    const void getAllUserCurrency();
    Currency *getUserCurrency(std::string);
    const bool isWalletEmpty();
    const bool findInWallet(std::string);
    void makeExchange(Currency *, Currency &, double);
};