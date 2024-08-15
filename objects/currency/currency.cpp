#include "../exchange/exchange.hpp"

void Currency::setName(std::string name)
{
    this->name = name;
}

void Currency::setExchangePrice()
{
    this->exchangePrice = api.getCurrency(this->name);
}

std::string Currency::getName()
{
    return name;
}

double Currency::getExchangePrice()
{
    return exchangePrice;
}

void Currency::setAmount(double amount)
{
    this->amount = amount;
}

double Currency::getAmount()
{
    return amount;
}

void Currency::convertFromTo(Currency *cOrg, Currency &cRes, double amount)
{
    Exchange exchange = Exchange();
    exchange.convert(cOrg, cRes, this, amount);
}