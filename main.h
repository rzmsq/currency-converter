#pragma once

#include "./objects/user/user.hpp"

void startExchange(User *usr, Currency &usrCurr);

void exchg(std::string &choose, User *usr);

void convert(User *usr);