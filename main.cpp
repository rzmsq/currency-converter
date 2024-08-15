#include "main.h"

int main(int argc, char const *argv[])
{
    static User usr = User();
    std::cout << "Welcome" << std::endl;
    while (1)
    {
        std::cout << "Please choose the option: " << std::endl
                  << "\t 1: Check my wallet" << std::endl
                  << "\t 2: Convert currency" << std::endl
                  << "\t 3: Exit" << std::endl;
        std::string choose;
        getline(std::cin, choose);
        if (choose != "1" && choose != "2" && choose != "3")
        {
            std::cout << "Error, please repeat" << std::endl;
            continue;
        }

        switch (stoi(choose))
        {
        case 1:
            usr.getAllUserCurrency();
            break;
        case 2:
            convert(&usr);
            break;
        case 3:
            return EXIT_SUCCESS;
        default:
            std::cout << "Error, please repeat" << std::endl;
            break;
        }
    }
}
