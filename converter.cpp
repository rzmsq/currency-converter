#include "main.h"

void convert(User *usr)
{
    std::cout << "\nConverter (enter 'q' for return main menu)" << std::endl
              << "here are all the available currency symbols https://docs.openexchangerates.org/reference/supported-currencies" << std::endl
              << "From: USD" << std::endl;
    std::string choose;
    do
    {
        std::cout << "To: ";
        getline(std::cin, choose);
        if (choose == "q")
            return;
        else if (choose.size() == 3)
        {
            exchg(choose, usr);
            return;
        }
    } while (choose != "q");
}

void exchg(std::string &choose, User *usr)
{
    Currency usrCurr = Currency();
    try
    {
        std::cout << "loading..." << std::endl;
        usrCurr.setName(choose);
        usrCurr.setExchangePrice();
        std::cout << "ok!" << std::endl;
    }
    catch (...)
    {
        std::cout << "Incorrect 'TO' currency" << '\n';
        return;
    }

    std::string continueStr{};
    std::cout << "Current exchange rate: " << usrCurr.getExchangePrice() << std::endl;

    while (1)
    {
        std::cout << "Continue? Y/N" << std::endl;
        getline(std::cin, continueStr);
        if (continueStr == "N" || continueStr == "n")
            return;
        else if (continueStr == "Y" || continueStr == "y")
        {
            startExchange(usr, usrCurr);
            return;
        }
        else
        {
            std::cout << "Incorrect input" << std::endl;
            continue;
        }
    }
}

void startExchange(User *usr, Currency &usrCurr)
{
    std::cout << "Enter amount for exchange: ";

    std::string amountStr{};
    getline(std::cin, amountStr);
    int amount{stoi(amountStr)};

    Currency *usdRef = usr->getUserCurrency("USD");
    Currency *usrCurrRef = &usrCurr;
    usr->makeExchange(usdRef, *usrCurrRef, amount);
}