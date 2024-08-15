#include "./user.hpp"

void User::changeOldCurrency(Currency &oldCurr)
{
    // Изменение значения количества исходной валюты
    // Удаляем валюту, если её не осталось в кошельке
    double getAmount = oldCurr.getAmount();
    if (getAmount > 0)
        userCurrency[oldCurr.getName()].setAmount(getAmount);
    else
        userCurrency.erase(oldCurr.getName());
}

void User::addNewCurrency(Currency &newCurr)
{
    // добавление в кошелек пользователя новую валюту
    // только если её не существует в кошельке
    userCurrency[newCurr.getName()] = newCurr;
}

const void User::getAllUserCurrency()
{
    std::cerr << "Your wallet: " << std::endl;
    for (auto &&i : userCurrency)
    {
        std::cerr << "\t-- " << i.second.getAmount() << ' ' << i.first << std::endl;
    }
}

void User::makeExchange(Currency *cOrg, Currency &cResult, double amount)
{
    // Совершени конвертации валюты
    // если в кошельке нет валюты, котору имы хотим получить, то добавляем её
    // в противном случае изменяем атрибуты заправшиваемой валюты
    // после каждой конвертации сохраняется все в data.json
    if (!userCurrency.count(cResult.getName()))
    {
        Currency newCurrency = Currency();
        newCurrency.setName(cOrg->getName());
        newCurrency.convertFromTo(cOrg, cResult, amount);
        this->addNewCurrency(newCurrency);
    }
    else
        cResult.convertFromTo(cOrg, cResult, amount);

    changeOldCurrency(*cOrg);
    writeUserDataJSON();
}

void User::writeUserDataJSON()
{
    j_map["Currency"];
    for (auto &&i : userCurrency)
        j_map["Currency"][i.first] = i.second.getAmount();

    std::ofstream file;
    file.open("data.json");
    file << j_map;
    file.close();
}

void User::takeUserDataJSON()
{
    std::ifstream file;
    try
    {

        file.open("data.json");
        j_map = json::parse(file);
        file.close();

        std::map<std::string, int> tmp = j_map.at("Currency").get<std::map<std::string, int>>();

        Currency cur = Currency();
        for (auto &&i : tmp)
        {
            cur.setName(i.first);
            cur.setAmount(i.second);
            cur.setExchangePrice();
            userCurrency[i.first] = cur;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Your wallet is empty! " << std::endl
                  << "100k dollars have been credited to your balance" << std::endl;
        file.close();

        Currency usd = Currency();
        usd.setName("USD");
        usd.setAmount(100000);
        this->addNewCurrency(usd);
    }
}

Currency *User::getUserCurrency(std::string nameq)
{
    return &userCurrency[nameq];
}

const bool User::isWalletEmpty()
{
    if (userCurrency.size() == 0)
        return true;
    else
        return false;
}

const bool User::findInWallet(std::string name)
{
    if (userCurrency.find(name) != userCurrency.end())
        return true;
    else
        return false;
}