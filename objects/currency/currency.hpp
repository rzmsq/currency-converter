/*
    Класс Currency реализован для работы с валютой.
*/

#pragma once

#include "../API/api.hpp"

class Currency
{
private:
    std::string name;
    double exchangePrice;
    double amount;
    API api = API();

public:
    void setName(std::string);
    void setExchangePrice();
    void setAmount(double);
    std::string getName();
    double getExchangePrice();
    double getAmount();
    void convertFromTo(Currency *, Currency &, double);
};