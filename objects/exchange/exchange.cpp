#include "exchange.hpp"

void Exchange::setCurrency(Currency *cOrg, Currency &cRes)
{
    this->curOrig = cOrg;
    this->curResult = &cRes;
}

void Exchange::convert(Currency *cOrg, Currency &cRes, Currency *newCurrency, double amount)
{
    try
    {
        setCurrency(cOrg, cRes);

        if (amount > curOrig->getAmount())
        {
            std::cerr << "Insufficient funds on the balance sheet" << std::endl;
            return;
        }

        double convertPrice = curResult->getExchangePrice();
        double amountResult = convertPrice * amount;

        cOrg->setAmount(curOrig->getAmount() - amount);
        newCurrency->setName(curResult->getName());
        newCurrency->setAmount(newCurrency->getAmount() + amountResult);
        newCurrency->setExchangePrice();
        std::cout << "Success!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "in Exchange cls convert mthd Error: " << e.what() << std::endl;
        return;
    }
}