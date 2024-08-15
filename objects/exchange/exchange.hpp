/*
    Класс реализующий логику конвертации валют
    Имеется один публичный метод convert принимающий 3 аргумента
    исходную валюту, валюта на которую происходит обмен и
    адресс, где будет храниться новая валюта
*/

#pragma once

#include "../currency/currency.hpp"

class Exchange
{
private:
    Currency *curOrig;
    Currency *curResult;
    void setCurrency(Currency *, Currency &);

public:
    void convert(Currency *, Currency &, Currency *, double);
};